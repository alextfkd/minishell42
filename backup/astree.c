#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

//----------------------------------------
// ASTノード定義
//----------------------------------------
typedef enum {
    NODE_CMD,
    NODE_REDIR,
    NODE_PIPE,
    NODE_AND,
    NODE_OR
} NodeType;

typedef struct Node {
    NodeType type;
    char *argv[8];
    char *redir_target;
    char *redir_op;
    struct Node *left;
    struct Node *right;
} Node;

//----------------------------------------
// トークン管理
//----------------------------------------
char *tokens[128];
int pos = 0, ntokens = 0;

char *peek() { return (pos < ntokens) ? tokens[pos] : NULL; }
char *next() { return (pos < ntokens) ? tokens[pos++] : NULL; }
int is_op(const char *s, const char *op) { return s && strcmp(s, op) == 0; }

//----------------------------------------
// パーサ前方宣言
//----------------------------------------
Node *parse_command();
Node *parse_redir();
Node *parse_pipeline();
Node *parse_and_or();

//----------------------------------------
// コマンド
//----------------------------------------
Node *parse_command() {
    if (!peek()) return NULL;
    Node *n = calloc(1, sizeof(Node));
    n->type = NODE_CMD;

    int argc = 0;
    while (peek() && !strchr("|&<>;", peek()[0])) {
        n->argv[argc++] = next();
    }
    n->argv[argc] = NULL;
    return n;
}

//----------------------------------------
// リダイレクト
//----------------------------------------
Node *parse_redir() {
    Node *cmd = parse_command();
    while (peek() && (is_op(peek(), ">") || is_op(peek(), "<") || is_op(peek(), ">>"))) {
        char *op = next();
        char *target = next();
        Node *redir = calloc(1, sizeof(Node));
        redir->type = NODE_REDIR;
        redir->redir_op = op;
        redir->redir_target = target;
        redir->left = cmd;
        cmd = redir;
    }
    return cmd;
}

//----------------------------------------
// パイプ
//----------------------------------------
Node *parse_pipeline() {
    Node *left = parse_redir();
    while (is_op(peek(), "|")) {
        next();
        Node *right = parse_redir();
        Node *pipe = calloc(1, sizeof(Node));
        pipe->type = NODE_PIPE;
        pipe->left = left;
        pipe->right = right;
        left = pipe;
    }
    return left;
}

//----------------------------------------
// AND / OR
//----------------------------------------
Node *parse_and_or() {
    Node *left = parse_pipeline();
    while (is_op(peek(), "&&") || is_op(peek(), "||")) {
        char *op = next();
        Node *right = parse_pipeline();
        Node *node = calloc(1, sizeof(Node));
        node->type = is_op(op, "&&") ? NODE_AND : NODE_OR;
        node->left = left;
        node->right = right;
        left = node;
    }
    return left;
}

//----------------------------------------
// トークナイザ
//----------------------------------------
void tokenize(char *input) {
    ntokens = pos = 0;
    char *p = input;
    while (*p) {
        while (isspace(*p)) p++;
        if (!*p) break;

        if (strncmp(p, "&&", 2) == 0 || strncmp(p, "||", 2) == 0 || strncmp(p, ">>", 2) == 0) {
            tokens[ntokens++] = strndup(p, 2);
            p += 2;
        } else if (strchr("|<>", *p)) {
            tokens[ntokens++] = strndup(p++, 1);
        } else {
            char *start = p;
            while (*p && !isspace(*p) && !strchr("|&<>;", *p)) p++;
            tokens[ntokens++] = strndup(start, p - start);
        }
    }
}

//----------------------------------------
// 実行部
//----------------------------------------
int exec_node(Node *n);

int exec_command(Node *n) {
    if (!n->argv[0]) return 0;
    pid_t pid = fork();
    if (pid == 0) {
        execvp(n->argv[0], n->argv);
        perror("execvp");
        exit(127);
    }
    int status;
    waitpid(pid, &status, 0);
    return WEXITSTATUS(status);
}

int exec_redir(Node *n) {
    int fd;
    if (strcmp(n->redir_op, ">") == 0)
        fd = open(n->redir_target, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    else if (strcmp(n->redir_op, ">>") == 0)
        fd = open(n->redir_target, O_WRONLY | O_CREAT | O_APPEND, 0666);
    else if (strcmp(n->redir_op, "<") == 0)
        fd = open(n->redir_target, O_RDONLY);
    else {
        fprintf(stderr, "unknown redir: %s\n", n->redir_op);
        return 1;
    }
    if (fd < 0) { perror("open"); return 1; }

    pid_t pid = fork();
    if (pid == 0) {
        if (strcmp(n->redir_op, "<") == 0)
            dup2(fd, STDIN_FILENO);
        else
            dup2(fd, STDOUT_FILENO);
        close(fd);
        exec_node(n->left);
        exit(0);
    }
    close(fd);
    int status;
    waitpid(pid, &status, 0);
    return WEXITSTATUS(status);
}

int exec_pipe(Node *n) {
    int pipefd[2];
    pipe(pipefd);

    pid_t pid1 = fork();
    if (pid1 == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        exit(exec_node(n->left));
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        exit(exec_node(n->right));
    }

    close(pipefd[0]);
    close(pipefd[1]);
    int status;
    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);
    return WEXITSTATUS(status);
}

int exec_node(Node *n) {
    if (!n) return 0;
    switch (n->type) {
        case NODE_CMD:   return exec_command(n);
        case NODE_REDIR: return exec_redir(n);
        case NODE_PIPE:  return exec_pipe(n);
        case NODE_AND: {
            int s = exec_node(n->left);
            return (s == 0) ? exec_node(n->right) : s;
        }
        case NODE_OR: {
            int s = exec_node(n->left);
            return (s != 0) ? exec_node(n->right) : s;
        }
    }
    return 0;
}

//----------------------------------------
// main
//----------------------------------------
int main() {
    char line[256];
    printf("mini-shell> ");
    while (fgets(line, sizeof(line), stdin)) {
        tokenize(line);
        Node *root = parse_and_or();
        exec_node(root);
        printf("mini-shell> ");
    }
    return 0;
}

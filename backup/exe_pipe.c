#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

// Node構造体の例
typedef enum {
    NODE_COMMAND,
    NODE_PIPE,
    NODE_AND,
    NODE_OR
} NodeType;

typedef struct Node {
    NodeType type;
    char **argv;
    struct Node *left;
    struct Node *right;
} Node;

int exec_node(Node *n);  // 前方宣言

// -------------------------------
// 多段パイプ対応版 exec_pipe()
// -------------------------------
int exec_pipe(Node *n) {
    // パイプ列を展開して、全コマンドノードを配列に格納
    Node *cmds[256];  // 256段まで対応（必要なら増やせる）
    int ncmd = 0;

    // 左再帰的にpipeを展開して左→右順に格納
    Node *cur = n;
    while (cur->type == NODE_PIPE) {
        cmds[ncmd++] = cur->left;
        cur = cur->right;
    }
    cmds[ncmd++] = cur; // 最後のコマンドを追加

    // パイプを必要数だけ作成
    int pipes[255][2];
    for (int i = 0; i < ncmd - 1; i++) {
        if (pipe(pipes[i]) < 0) {
            perror("pipe");
            return 1;
        }
    }

    // 各コマンドをforkして入出力を設定
    for (int i = 0; i < ncmd; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
            // 標準入力を前パイプの読み端に接続
            if (i > 0)
                dup2(pipes[i - 1][0], STDIN_FILENO);

            // 標準出力を次パイプの書き端に接続
            if (i < ncmd - 1)
                dup2(pipes[i][1], STDOUT_FILENO);

            // すべてのパイプ端を閉じる
            for (int j = 0; j < ncmd - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            // コマンドを実行
            exit(exec_node(cmds[i]));
        }
    }

    // 親プロセス：全パイプを閉じて子を待機
    for (int i = 0; i < ncmd - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    int status = 0;
    for (int i = 0; i < ncmd; i++) {
        int s;
        wait(&s);
        if (WIFEXITED(s))
            status = WEXITSTATUS(s);
    }
    return status;
}

#!/bin/bash


# Must to set DEBUGLEVEL 1

GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"
MINISHELL="./minishell"

OUT_BASH="bash.txt"
OUT_MINISHELL="minishell.txt"

input_sequence() {
    echo "notfoundcmd"
    echo "cat << EOF"
    echo '$?'
    echo 'abc$USER'
    echo 'abc$USERabc'
    echo '$USERabc'
    echo '$USER=$USER'
    echo '$USER='
    echo '=$USER'
    echo '$USER'
    echo "Hello World"
    echo "This is a heredoc test"
    echo "EOF"
}

# input_sequence | bash
# input_sequence | ./minishell

run_test()
{
    local INPUT_CONTENT="$1"

    filter_bash(){
        grep -v "command not found"
    }

    filter_minishell(){
        sed '1,/^EOF$/d' | grep -v "^exit$"
    }

    echo "$INPUT_CONTENT" | bash 2>&1 | filter_bash > "$OUT_BASH"
    echo "$INPUT_CONTENT" | $MINISHELL 2>&1 | filter_minishell > "$OUT_MINISHELL"

    diff "$OUT_BASH" "$OUT_MINISHELL" > /dev/null

    if [ $? -eq 0 ]; then
        echo -e "${GREEN}[OK] Matches!${RESET}"
    else
        echo -e "${RED}[KO] Differs!${RESET}"
        echo "--- Bash (Expected) ---"
        cat "$OUT_BASH"
        echo "--- Minishell (Actual) ---"
        cat "$OUT_MINISHELL"
        echo "-----------------------"
        echo "Difference:"
        diff "$OUT_BASH" "$OUT_MINISHELL"
    fi
    rm -rf $OUT_BASH $OUT_MINISHELL
}

INPUT_CONTENT=$(input_sequence)
run_test "$INPUT_CONTENT"


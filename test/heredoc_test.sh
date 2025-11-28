#!/bin/bash

GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"
MINISHELL="./minishell"

OUT_EXPECTED="expected.txt"
OUT_ACTUAL="actual.txt"
OUT_RAW="actual_raw.txt"

input_sequence() {
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

INPUT_CONTENT=$(input_sequence)
INPUT_LINES=$(echo "$INPUT_CONTENT" | wc -l | xargs)

echo "$INPUT_CONTENT" | bash > "$OUT_EXPECTED" 2>&1

echo "$INPUT_CONTENT" | $MINISHELL > "$OUT_RAW" 2>&1

sed "1,${INPUT_LINES}d" "$OUT_RAW" > "$OUT_ACTUAL"

grep -v "^exit$" "$OUT_ACTUAL" > "${OUT_ACTUAL}.tmp" && mv "${OUT_ACTUAL}.tmp" "$OUT_ACTUAL"

echo "--- Input Sequence ---"
echo "$INPUT_CONTENT"
echo "----------------------"

diff "$OUT_EXPECTED" "$OUT_ACTUAL" > /dev/null

if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK] Test Passed${RESET}"
    echo "Expected (Bash):"
    cat "$OUT_EXPECTED"
    echo "Actual (Minishell - filtered):"
    cat "$OUT_ACTUAL"
    echo "Actual (Minishell - raw dat)"
    cat "$OUT_RAW"
else
    echo -e "${RED}[KO] Test Failed${RESET}"
    echo "Expected (Bash):"
    cat "$OUT_EXPECTED"
    echo "Actual (Minishell - filtered):"
    cat "$OUT_ACTUAL"
    echo "Actual (Minishell - raw dat)"
    cat "$OUT_RAW"
fi

rm -f "$OUT_EXPECTED" "$OUT_ACTUAL" "$OUT_RAW" "${OUT_ACTUAL}.tmp"

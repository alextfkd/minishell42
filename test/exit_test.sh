#!/bin/bash

GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"
MINISHELL="./minishell"

assert_exit() {
    local cmd="$1"
    local expected="$2"

    echo "$cmd" | $MINISHELL > /dev/null 2>&1

    local actual=$?

    if [ "$actual" -eq "$expected" ]; then
        echo -e "${GREEN}[OK]${RESET} '$cmd' -> Expected: $expected, Got: $actual"
    else
        echo -e "${RED}[KO]${RESET} '$cmd' -> Expected: $expected, Got: $actual"
    fi
}

echo "=== Minishell Exit Tests ==="

assert_exit "exit 0" 0
assert_exit "exit 42" 42
assert_exit "exit 256" 0
assert_exit "exit 257" 1
assert_exit "exit -1" 255
assert_exit "exit -42" 214
assert_exit "exit +10" 10
assert_exit "exit a" 2
assert_exit "exit a b" 2
assert_exit "exit a 1" 2
assert_exit "exit hello" 2
assert_exit "exit -" 2
assert_exit "exit 1 2" 1
assert_exit "exit 2 a" 1 
assert_exit "exit 999999999999999999" 2
assert_exit "exit -999999999999999999" 2

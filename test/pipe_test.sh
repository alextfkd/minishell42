#!/bin/bash

GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
NC="\033[0m"
PIPE_TEST="./pipe_test"

EXECUTABLE=./test/files/executable.sh
NONEXECUTABLE=./test/files/nonexecutable.sh
READ_WRITE=./test/files/read_write.txt
OWNER_ONLY=./test/files/owner_only.txt
READ_ONLY=./test/files/readonly.txt
WRITE_ONLY=./test/files/writeonly.txt
PUBLIC=./test/files/public_file.txt
NOEXIST_INFILE=./test/files/doesnotexist_infile

chmod 700 $EXECUTABLE
chmod 666 $READ_WRITE
chmod 777 $PUBLIC
chmod 644 $OWNER_ONLY
chmod 444 $READ_ONLY
chmod 222 $WRITE_ONLY

NOEXIST_OUT=./test/files/outfile
NOEXIST_OUT_TEST=./test/files/outfile_test

chmod 666 $NOEXIST_OUT
chmod 666 $NOEXIST_OUT_TEST

rm -f $NOEXIST_OUT $NOEXIST_OUT_TEST

run_simple_test() {
    local command="$2"
    local expected="$3"
    local actual

    echo $1
    $PIPE_TEST "$command" > /dev/null 2>&1
    actual=$?
    if [ "$actual" -eq "$expected" ]; then
        echo -e "   ${GREEN}[OK] PASSED${NC}"
    else
        echo -e "   ${RED}[NG] FAILD${NC} (The completion status differs from the expected value.)"
    fi
}

run_comparison_test() {
    local command="$2"
    local bash_status
    local minishell_status

    echo $1
    (eval "$command") > /dev/null 2>&1
    bash_status=$?

    $PIPE_TEST "$command" > /dev/null 2>&1
    minishell_status=$?

    printf "   -> Bash status: %d\n" "$bash_status"
    printf "   -> Mini status: %d\n" "$minishell_status"

    if [ "$minishell_status" -eq "$bash_status" ]; then
        echo -e "   ${GREEN}[OK] PASSED${NC}"
    else
        echo -e "   ${RED}[NG] FAILD${NC} (Bash: ${bash_status}, Mini: ${minishell_status})"
    fi
}

echo -e "\n${YELLOW}=== expected test ===${NC}"

run_simple_test 01 "echo Hello from Script" 0
run_simple_test 02 "commandnotfound" 127
run_simple_test 03 "/bin/ls -l" 0

sleep 5

echo -e "\n${YELLOW}=== comparison test ====${NC}"
run_comparison_test 01 "echo Test A"
run_comparison_test 02 "cat non_existent_file_xyz"
run_comparison_test 03 "pwd"
run_comparison_test 04 "commandnotfound12345"
run_comparison_test 05 "cd /tmp"
run_comparison_test 06 "env HOME=/home /bin/ls"
run_comparison_test 07 "/bin/ls --non-existent-option"
run_comparison_test 08 "ls | wc -l"
run_comparison_test 09 \"\"
run_comparison_test 10 "exit 42"
run_comparison_test 11 "$NONEXECUTABLE"
run_comparison_test 12 "./pipe_test ./pipe_test hoge"

sleep 5

run_minipipe_test() {
	rm -f $5 $6
	echo $1
    eval "< $2 $3 | $4 > $6"
	bash_status=$?
	./pipe_test "< $2 $3 | $4 > $5"
	minishell_status=$?

    printf "   -> Bash status: %d\n" "$bash_status"
    printf "   -> Mini status: %d\n" "$minishell_status"

    if [ "$minishell_status" -eq "$bash_status" ]; then
        echo -e "   ${GREEN}[OK] PASSED${NC}"
    else
        echo -e "   ${RED}[NG] FAILD${NC} (Bash: ${bash_status}, Mini: ${minishell_status})"
    fi
	echo;
}


echo -e "\n${YELLOW}=== easy pipe test ====${NC}"


echo " ---NOEXIST OUT TEST--"

CMD1=cat
CMD2=cat

run_minipipe_test test1 $EXECUTABLE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test2 $READ_WRITE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test3 $READ_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test4 $WRITE_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test5 $PUBLIC $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test6 $OWNER_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test7 $NOEXIST_INFILE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST

CMD1=cat
CMD2=ls

run_minipipe_test test8 $EXECUTABLE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test9 $READ_WRITE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test10 $READ_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test11 $WRITE_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test12 $PUBLIC $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test13 $OWNER_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test14 $NOEXIST_INFILE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST

CMD1=ls
CMD2=cat

run_minipipe_test test15 $EXECUTABLE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test16 $READ_WRITE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test17 $READ_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test18 $WRITE_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test19 $PUBLIC $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test20 $OWNER_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test21 $NOEXIST_INFILE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST

CMD1=ls
CMD2=ls

run_minipipe_test test22 $EXECUTABLE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test23 $READ_WRITE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test24 $READ_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test25 $WRITE_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test26 $PUBLIC $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test27 $OWNER_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test28 $NOEXIST_INFILE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST

CMD1=cat
CMD2=ls

run_minipipe_test test8 $EXECUTABLE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test9 $READ_WRITE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test10 $READ_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test11 $WRITE_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test12 $PUBLIC $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test13 $OWNER_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test14 $NOEXIST_INFILE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST

CMD1=ls
CMD2=cat

run_minipipe_test test15 $EXECUTABLE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test16 $READ_WRITE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test17 $READ_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test18 $WRITE_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test19 $PUBLIC $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test20 $OWNER_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test21 $NOEXIST_INFILE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST

CMD1=ls
CMD2=ls

run_minipipe_test test22 $EXECUTABLE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test23 $READ_WRITE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test24 $READ_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test25 $WRITE_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test26 $PUBLIC $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test27 $OWNER_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test28 $NOEXIST_INFILE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST

echo
echo "--EXIST OUT TEST--"

EXIST_OUT=./test/files/outfile_exist
EXIST_OUT_TEST=./test/files/outfile_test_exist
BASE_OUT=./test/files/base_outfile


run_minipipe_test2() {
	rm -f $5 $6
    cp -f $7 $5
    cp -f $7 $6
	echo $1
    eval "< $2 $3 | $4 > $6"
	bash_status=$?
	./pipe_test "< $2 $3 | $4 > $5"
	minishell_status=$?

    printf "   -> Bash status: %d\n" "$bash_status"
    printf "   -> Mini status: %d\n" "$minishell_status"

    if [ "$minishell_status" -eq "$bash_status" ]; then
        echo -e "   ${GREEN}[OK] PASSED${NC}"
    else
        echo -e "   ${RED}[NG] FAILD${NC} (Bash: ${bash_status}, Mini: ${minishell_status})"
    fi
	echo;
}
CMD1=cat
CMD2=cat

run_minipipe_test2 test29 $EXECUTABLE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test30 $READ_WRITE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test31 $READ_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test32 $WRITE_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test33 $PUBLIC $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test34 $OWNER_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test35 $NOEXIST_INFILE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT

CMD1=ls
CMD2=cat

run_minipipe_test2 test36 $EXECUTABLE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test37 $READ_WRITE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test38 $READ_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test39 $WRITE_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test40 $PUBLIC $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test41 $OWNER_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test42 $NOEXIST_INFILE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT

CMD1=cat
CMD2=ls

run_minipipe_test2 test43 $EXECUTABLE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test44 $READ_WRITE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test45 $READ_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test46 $WRITE_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test47 $PUBLIC $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test48 $OWNER_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test49 $NOEXIST_INFILE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT

CMD1=ls
CMD2=ls

run_minipipe_test2 test50 $EXECUTABLE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test51 $READ_WRITE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test52 $READ_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test53 $WRITE_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test54 $PUBLIC $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test55 $OWNER_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test2 test56 $NOEXIST_INFILE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT

echo
echo "---NOPERMIT EXIST OUT TEST---"

EXIST_OUT=./test/files/outfile_exist_nopermit
EXIST_OUT_TEST=./test/files/outfile_test_exist_nopermit
BASE_OUT=./test/files/base_outfile


run_minipipe_test3() {
	rm -f $5 $6
    cp -f $7 $5
    cp -f $7 $6
    chmod 0 $5
    chmod 0 $6
	printf "%s\n" "$1"
    eval "< $2 $3 | $4 > $6"
	bash_status=$?
	./pipe_test "< $2 $3 | $4 > $5"
	minishell_status=$?

    printf "   -> Bash status: %d\n" "$bash_status"
    printf "   -> Mini status: %d\n" "$minishell_status"

    if [ "$minishell_status" -eq "$bash_status" ]; then
        echo -e "   ${GREEN}[OK] PASSED${NC}"
    else
        echo -e "   ${RED}[NG] FAILD${NC} (Bash: ${bash_status}, Mini: ${minishell_status})"
    fi
	echo;
}

CMD1=cat
CMD2=cat

run_minipipe_test3 test57 $EXECUTABLE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test58 $READ_WRITE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test59 $READ_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test60 $WRITE_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test61 $PUBLIC $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test62 $OWNER_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test63 $NOEXIST_INFILE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT

CMD1=ls
CMD2=cat

run_minipipe_test3 test64 $EXECUTABLE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test65 $READ_WRITE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test66 $READ_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test67 $WRITE_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test68 $PUBLIC $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test69 $OWNER_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test70 $NOEXIST_INFILE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT

CMD1=cat
CMD2=ls

run_minipipe_test3 test71 $EXECUTABLE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test72 $READ_WRITE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test73 $READ_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test74 $WRITE_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test75 $PUBLIC $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test76 $OWNER_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test77 $NOEXIST_INFILE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT

CMD1=ls
CMD2=ls

run_minipipe_test3 test78 $EXECUTABLE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test79 $READ_WRITE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test80 $READ_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test81 $WRITE_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test82 $PUBLIC $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test83 $OWNER_ONLY $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT
run_minipipe_test3 test84 $NOEXIST_INFILE $CMD1 $CMD2 $EXIST_OUT $EXIST_OUT_TEST $BASE_OUT

echo "--NOCOMMAND FOUND TEST--"


CMD1=nofoundcommand
CMD2=cat

run_minipipe_test test85 $EXECUTABLE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test86 $READ_WRITE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test87 $READ_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test88 $WRITE_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test89 $PUBLIC $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test90 $OWNER_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test91 $NOEXIST_INFILE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST

CMD1=cat
CMD2=nofoundcommand

run_minipipe_test test92 $EXECUTABLE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test93 $READ_WRITE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test94 $READ_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test95 $WRITE_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test96 $PUBLIC $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test97 $OWNER_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test98 $NOEXIST_INFILE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST

CMD1=nofoundcommand
CMD2=nofoundcommand

run_minipipe_test test99 $EXECUTABLE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test100 $READ_WRITE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test101 $READ_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test102 $WRITE_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test103 $PUBLIC $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test104 $OWNER_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test105 $NOEXIST_INFILE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST

CMD1=./test/files/outfile
CMD2=nofoundcommand

run_minipipe_test test106 $EXECUTABLE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test107 $READ_WRITE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test108 $READ_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test109 $WRITE_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test110 $PUBLIC $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test111 $OWNER_ONLY $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST
run_minipipe_test test112 $NOEXIST_INFILE $CMD1 $CMD2 $NOEXIST_OUT $NOEXIST_OUT_TEST


echo ""
echo -e "${GREEN}--- finished ---${NC}"

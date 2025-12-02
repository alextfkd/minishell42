make clean && make quote_rm_test

rm test/out
rm test/test

touch test/out
touch test/test

echo "BASH" >> test/out
echo "MINISHELL" >> test/test

function write_result() {
	echo "" >> test/out
	echo "" >> test/test
	echo $1 >> test/out
	echo $1 >> test/test
	echo $1 >> test/out
	valgrind --leak-check=full -q ./quote_rm_test $1 $2 >> test/test
}

write_result "hello" 2
write_result 'h'ello 0
write_result "'h'ello" 2
write_result '"'h'ello"' 1

diff test/out test/test --side-by-side
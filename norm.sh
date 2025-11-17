ERROR_COUNT=$(norminette ./srcs ./libft ./includes 2>&1 | grep "Error!" | wc -l)
NOTICE_COUNT=$(norminette ./srcs ./libft ./includes 2>&1 | grep "GLOBAL_VAR_DETECTED" | wc -l)

if [ "$ERROR_COUNT" -eq 0 ]; then
    echo "✅ Norminette Pass: No errors, $NOTICE_COUNT notice(s) found."
	exit 0;
else
    echo "❌ Norminette Fail: $ERROR_COUNT errors found, $NOTICE_COUNT notice(s) found."
	norminette ./srcs ./libft ./includes | grep Error
	exit 1;
fi

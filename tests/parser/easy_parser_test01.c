#include "ast.h"
#include "parser.h"
#include "tokenizer.h"
#include "test_tools.h"

#include <stdlib.h>
#include <unistd.h>

int
show_expr_ast_parsing_proc(char *str)
{
	t_token_list *tkn_lst;
	t_expr *expr_ast;


	debug_dprintf(STDERR_FILENO, "test case: \"%s\"\n", str);
	tkn_lst = tokenizer(str);
	print_token_list_ln(tkn_lst);
	expr_ast = parse_expression(&tkn_lst);

	if (expr_ast == NULL)
	{
		debug_dprintf(STDERR_FILENO, "something wrong with while parsing\n");
		return 1;
	}
	print_expr_ast(expr_ast, 0);
	clear_ast(expr_ast);
	return 0;
}

/// ```bash
/// make vtest TEST_FILE=tests/parser/easy_parser_test01.c
/// ```
int main()
{
	char *str_arr[20] = {
		"a = x && y || z",
		"a = b + c * d - 1",
		"a = w << x | y << z",
		"a = b",
		"a = 0 <= x || x <= 10",
		"a = w + x + y +z",
		"a = x * y * z * w",
		"p = ***a",
		"p = *a + **b",
		"p = *a * **b",
		"p = *a * b[42]",
		"p = *a * b[42 + i + j + k + l + m]",
		"p = lst[y][x]",
		"expr->contents.postfix->left_expr",
		"player->vec.x = lst[x]",
		"*p = 1 + x",
		"p = (1 + x) * y",

	};

	for (int i = 0; i < 17; i++){
		debug_dprintf(STDERR_FILENO, "===========================\n");
		show_expr_ast_parsing_proc(str_arr[i]);
	}

	//show_expr_ast_parsing_proc(str_arr[1]);
	//show_expr_ast_parsing_proc(str_arr[10]);
	//show_expr_ast_parsing_proc(str_arr[11]);
	//show_expr_ast_parsing_proc(str_arr[12]);
	//show_expr_ast_parsing_proc(str_arr[13]);
	//show_expr_ast_parsing_proc(str_arr[14]);
	return (0);
}

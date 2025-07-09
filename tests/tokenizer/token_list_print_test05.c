#include "list.h"
#include "test_tools.h"
#include "tokenizer.h"
#include <unistd.h>
#include "brackets.h"

/// ```
/// make vtest TEST_FILE=tests/tokenizer/token_list_print_test05.c
/// ```
int main()
{
	char *str = \
		"int a = 123;"
		"if (a % 2 == 0)"
		"{a = a + 456;}"
		"else {a = 0;}"
		"return a;"
	;
	t_token_list *tkn_lst;

	debug_dprintf(STDERR_FILENO, "test case:\nstart>>>>>>>>\n%s\n<<<<<<<<end\n", str);
	debug_dprintf(STDERR_FILENO, "%s\n", "tokenize...");
	tkn_lst = tokenizer(str);
	debug_dprintf(STDERR_FILENO, "%s\n", "DONE");
	if (tkn_lst == NULL)
		debug_dprintf(STDERR_FILENO, "failed to tokenize\n");

	group_paren(&tkn_lst, e_token_type_open_paren, e_token_type_close_paren, e_token_type_paren);
	group_paren(&tkn_lst, e_token_type_open_brace, e_token_type_close_brace, e_token_type_brace);
	group_paren(&tkn_lst, e_token_type_open_bracket, e_token_type_close_bracket, e_token_type_bracket);

	print_token_list_ln(tkn_lst);
	clear_token_list(&tkn_lst);
	return 0;
}

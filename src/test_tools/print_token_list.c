#include "test_tools.h" 
#include "token_data.h"
#include "list.h"
#include "token_data.h"
#include <unistd.h>

char *print_operator_as_string(t_operator operator)
{
	switch (operator)
	{
		case e_operator_add:
			return "+";
		case e_operator_sub:
			return "-";
		case e_operator_mul:
			return "*";
		case e_operator_div:
			return "/";
		case e_operator_mod:
			return "%";
		case e_operator_assignment:
			return "=";
		case e_operator_add_assignment:
			return "+=";
		case e_operator_sub_assignment:
			return "-=";
		case e_operator_mul_assignment:
			return "*=";
		case e_operator_div_assignment:
			return "/=";
		case e_operator_bitshift_right_assignment:
			return ">>=";
		case e_operator_bitshift_left_assignment:
			return "<<=";
		case e_operator_and_assignment:
			return "&=";
		case e_operator_or_assignment:
			return "|=";
		case e_operator_ne:
			return "!=";
		case e_operator_xor_assignment:
			return "^=";
		case e_operator_incr:
			return "++";
		case e_operator_decr:
			return "--";
		case e_operator_bitshift_right:
			return ">>";
		case e_operator_bitshift_left:
			return "<<";
		case e_operator_addr:
			return "&";
		case e_operator_pointer:
			return "*";
		case e_operator_arrow:
			return "->";
		case e_operator_logic_and:
			return "&";
		case e_operator_logic_or:
			return "|";
		case e_operator_logic_xor:
			return "^";
		case e_operator_and:
			return "&&";
		case e_operator_or:
			return "||";
		case e_operator_not:
			return "!";
		case e_operator_gt:
			return ">";
		case e_operator_ge:
			return ">=";
		case e_operator_lt:
			return "<";
		case e_operator_le:
			return "<=";
		case e_operator_eq:
			return "==";
		case e_operator_comma:
			return ",";
		case e_operator_dot:
			return ".";
		case e_operator_funccall:
			return "funccall";
		case e_operator_arr_index_access:
			return ("index_access");
		default:
			return NULL;
	}
}

void get_token_str(t_anytype token, 
	char **contents_str,
	char **token_type_str
)
{
	switch (token.token->token_type)
	{
		case e_token_type_operator:
			*contents_str = print_operator_as_string(token.token->contents.ope);
			*token_type_str = "operator ";
			break;
		case e_token_type_word:
			*contents_str = token.token->contents.str;
			*token_type_str = "word     ";
			break;
		case e_token_type_open_brace:
			*contents_str = "{";
			*token_type_str = "o_brace  ";
			break;
		case e_token_type_close_brace:
			*contents_str = "}";
			*token_type_str = "c_brace  ";
			break;
		case e_token_type_open_paren:
			*contents_str = "(";
			*token_type_str = "o_paren  ";
			break;
		case e_token_type_close_paren:
			*contents_str = ")";
			*token_type_str = "c_paren  ";
			break;
		case e_token_type_open_bracket:
			*contents_str = "[";
			*token_type_str = "o_bracket";
			break;
		case e_token_type_close_bracket:
			*contents_str = "]";
			*token_type_str = "c_bracket";
			break;
		case e_token_type_comment:
			*contents_str = token.token->contents.str;
			*token_type_str = "comment  ";
			break;
		case e_token_type_string:
			*contents_str = token.token->contents.str;
			*token_type_str = "string   ";
			break;
		case e_token_type_colon:
			*contents_str = ":";
			*token_type_str = "colon    ";
			break;
		case e_token_type_semi_colon:
			*contents_str = ";";
			*token_type_str = "semicolon";
			break;
		case e_token_type_paren:
			*contents_str = "list - list - list ...";
			*token_type_str = "paren    ";
			break;
		case e_token_type_brace:
			*contents_str = "list - list - list ...";
			*token_type_str = "brace    ";
			break;
		case e_token_type_bracket:
			*contents_str = "list - list - list ...";
			*token_type_str = "bracket  ";
			break;
		default:
			break;
	}
}


static int print_token(int index, t_anytype token)
{
	char *contents_str;
	char *token_type_str;

	contents_str = NULL;
	token_type_str = NULL;

	get_token_str(token, &contents_str, &token_type_str);
	// トークン自体の表示も
	debug_dprintf(
		STDERR_FILENO, 
		"[%d] [%s] [%s] \n", 
		index,
	       	token_type_str, 
		contents_str
	);
	if (token.token->token_type == e_token_type_paren)
	{
		debug_dprintf(STDERR_FILENO, "\e[36m");
		print_token_list_ln(token.token->contents.token_list);
		debug_dprintf(STDERR_FILENO, "\e[m");
	}
	else if (token.token->token_type == e_token_type_brace)
	{
		debug_dprintf(STDERR_FILENO, "\e[36m");
		print_token_list_ln(token.token->contents.token_list);
		debug_dprintf(STDERR_FILENO, "\e[m");
	}
	else if (token.token->token_type == e_token_type_bracket)
	{
		debug_dprintf(STDERR_FILENO, "\e[36m");
		print_token_list_ln(token.token->contents.token_list);
		debug_dprintf(STDERR_FILENO, "\e[m");
	}
	return (0);
}

int print_token_list_ln(t_token_list *token_list)
{
	void_list_print(
		token_list,
	       	print_token
	);
	return (0);
}


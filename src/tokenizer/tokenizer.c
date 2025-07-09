#include "token_data.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "libft.h"
#include "tokenizer.h"

#include "test_tools.h"

enum e_ptr_state
{
	e_ptr_state_in_single_quotation,
	e_ptr_state_in_double_quotation,
	e_ptr_state_in_oneline_comment,
	e_ptr_state_in_multiline_comment,
	e_ptr_state_in_word,
	e_ptr_state_out
};
typedef enum e_ptr_state t_ptr_state;

int push_token(
	t_token_list **lst,
	t_token_type token_type, 
	char *str
)
{
	t_anytype elem;

	elem.token = init_token_by_str(
		token_type,
		str
	);		
	return void_list_push(lst, elem);
}

int push_operator(t_token_list **lst, t_operator operator_token_type)
{
	t_anytype elem;

	elem.token = init_token_by_ope(
			e_token_type_operator,
			operator_token_type
	);		
	return void_list_push(lst, elem);
}

bool is_valid_identifer_char(char c)
{
	return ft_isalnum(c) || c == '_';
}

size_t case_ptr_state_in_word(char *str, t_ptr_state *ptr_state)
{
	size_t index;

	index = 0;
	while (is_valid_identifer_char(str[index]))
	{
		index += 1;
	}
	*ptr_state = e_ptr_state_out;
	return index - 1;
}

size_t match_operator_token(char *str, t_token_list **lst)
{
	struct {
		char buf[3];
		size_t size;
		t_operator operator;
	} str_operator_conv_table[35] = {
		{{'>', '>', '='},3, e_operator_bitshift_right_assignment},
		{{'<', '<', '='},3, e_operator_bitshift_left_assignment},
		{{'+', '+', '\0'},2, e_operator_incr},
		{{'+', '=', '\0'},2, e_operator_add_assignment},
		{{'-', '-', '\0'},2, e_operator_decr},
		{{'-', '=', '\0'},2, e_operator_sub_assignment},
		{{'*', '=', '\0'},2, e_operator_mul_assignment},
		{{'/', '=', '\0'},2, e_operator_div_assignment},
		{{'%', '=', '\0'},2, e_operator_mod_assignment},
		{{'<', '<', '\0'},2, e_operator_bitshift_left},
		{{'<', '=', '\0'},2, e_operator_le},
		{{'>', '>', '\0'},2, e_operator_bitshift_right},
		{{'-', '>', '\0'},2, e_operator_arrow},
		{{'>', '=', '\0'},2, e_operator_ge},
		{{'&', '&', '\0'},2, e_operator_and},
		{{'&', '=', '\0'},2, e_operator_and_assignment},
		{{'|', '|', '\0'},2, e_operator_or},
		{{'|', '=', '\0'},2, e_operator_or_assignment},
		{{'^', '=', '\0'},2, e_operator_xor_assignment},
		{{'!', '=', '\0'},2, e_operator_ne},
		{{'=', '=', '\0'},2, e_operator_eq},
		{{'!', '\0', '\0'},1, e_operator_not},
		{{'|', '\0', '\0'},1, e_operator_logic_or},
		{{'&', '\0', '\0'},1, e_operator_logic_and},
		{{'^', '\0', '\0'},1, e_operator_logic_xor},
		{{'>', '\0', '\0'},1, e_operator_gt},
		{{'<', '\0', '\0'},1, e_operator_lt},
		{{'/', '\0', '\0'},1, e_operator_div},
		{{'*', '\0', '\0'},1, e_operator_mul},
		{{'-', '\0', '\0'},1, e_operator_sub},
		{{'+', '\0', '\0'},1, e_operator_add},
		{{'=', '\0', '\0'},1, e_operator_assignment},
		{{',', '\0', '\0'},1, e_operator_comma},
		{{'.', '\0', '\0'},1, e_operator_dot},
		{{'%', '\0', '\0'},1, e_operator_mod},
	};

	for (int i = 0; i < 35; i++)
	{
		if (
			ft_strncmp(str, str_operator_conv_table[i].buf, str_operator_conv_table[i].size) == 0
		)
		{
			push_operator(lst, str_operator_conv_table[i].operator);
			return str_operator_conv_table[i].size;
		}
	}
	return 0;
}


/// return next state
/// if error -> return 0
size_t case_ptr_state_out(
	char *str,
	t_ptr_state *ptr_state,
       	t_token_list **lst
)
{
	//debug_dprintf(STDERR_FILENO, "case_ptr_state_out:%s\n", str); 
	if (*str == '"')
	{
		*ptr_state = e_ptr_state_in_double_quotation;
		return (1);
	}
	else if  (*str == '\'')
	{
		*ptr_state = e_ptr_state_in_single_quotation;
		return (1);
	}
	else if (is_valid_identifer_char(*str))
	{
		size_t slide = case_ptr_state_in_word(str, ptr_state);
		push_token(lst, e_token_type_word, ft_substr(str, 0, slide + 1));
		return (slide + 1);
	}
	else if (ft_isspace(*str))
	{
		return (1);
	}
	else if (str[0] == '/')
	{
		if (str[1] == '/')
		{
			*ptr_state = e_ptr_state_in_oneline_comment;
			return (2);
		}
		else if (str[1] == '*')
		{
			*ptr_state = e_ptr_state_in_multiline_comment;
			return (2);
		}
	}
	else if (*str == ';')
	{
		push_token(lst, e_token_type_semi_colon, NULL);
		return (1);
	}
	else if (*str == ':')
	{
		push_token(lst, e_token_type_colon, NULL);
		return (1);
	}
	else if (*str == '{')
	{
		push_token(lst, e_token_type_open_brace, NULL);
		return (1);
	}
	else if (*str == '}')
	{
		push_token(lst, e_token_type_close_brace, NULL);
		return (1);
	}
	else if (*str == '(')
	{
		push_token(lst, e_token_type_open_paren, NULL);
		return (1);
	}
	else if (*str == ')')
	{
		push_token(lst, e_token_type_close_paren, NULL);
		return (1);
	}
	else if (*str == '[')
	{
		push_token(lst, e_token_type_open_bracket, NULL);
		return (1);
	}
	else if (*str == ']')
	{
		push_token(lst, e_token_type_close_bracket, NULL);
		return (1);
	}
	//// 上のelse ifチェーンとは繋げない
	return match_operator_token(str, lst);
}

/// 一行のコメントをリストに追加する
size_t case_ptr_state_in_oneline_comment(
	char *str,
	t_ptr_state *ptr_state,
       	t_token_list **lst
)
{
	size_t index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '\n')
		{
			*ptr_state = e_ptr_state_out;
			break ;
		}
		index += 1;
	}
	push_token(lst, e_token_type_comment, ft_substr(str, 0, index));
	return index;
}

/// 複数行コメントをリストに追加する
size_t case_ptr_state_in_multiline_comment(
	char *str,
	t_ptr_state *ptr_state,
       	t_token_list **lst
)
{
	size_t index;

	index = 0;
	while (str[index] != '\0')
	{
		if (
			str[index] == '*' && 
			str[index + 1] == '/'
		){
			*ptr_state = e_ptr_state_out;
			push_token(lst, e_token_type_comment, ft_substr(str, 0, index));
			index += 2;
			break ;
		}
		index += 1;
	}
	return index;
}

size_t case_ptr_state_in_double_quotation(
	char *str,
	t_ptr_state *ptr_state,
       	t_token_list **lst
)
{
	size_t index;
	bool esc_flag;

	index = 0;
	esc_flag = false;
	while (str[index] != '\0')
	{
		if (str[index] == '"' && !esc_flag)
		{
			*ptr_state = e_ptr_state_out;
			push_token(lst, e_token_type_string, ft_substr(str, 0, index));
			index += 1;
			break ;
		}
		if (str[index] == '\\')
			esc_flag = true;
		else
			esc_flag = false;
		index += 1;
	}
	return index;
}

size_t case_ptr_state_in_single_quotation(
	char *str,
	t_ptr_state *ptr_state,
       	t_token_list **lst
)
{
	size_t index;
	bool esc_flag;

	index = 0;
	esc_flag = false;
	while (str[index] != '\0')
	{
		if (str[index] == '\'' && !esc_flag)
		{
			*ptr_state = e_ptr_state_out;
			push_token(lst, e_token_type_string, ft_substr(str, 0, index));
			index += 1;
			break ;
		}
		if (str[index] == '\\')
			esc_flag = true;
		else
			esc_flag = false;
		index += 1;
	}
	return index;
}

t_token_list *tokenizer(char *str)
{
	t_token_list *lst;
	t_ptr_state ptr_state;
	size_t slide;

	lst = NULL;
	ptr_state = e_ptr_state_out;
	while (*str != '\0')
	{
		slide = 0;
		switch (ptr_state)
		{
			case e_ptr_state_out:
				//debug_dprintf(STDERR_FILENO, "e_ptr_state_out\n");
				slide = case_ptr_state_out(str, &ptr_state, &lst);
				break;
			case e_ptr_state_in_word:
				//debug_dprintf(STDERR_FILENO, "e_ptr_state_in_word\n");
				slide = case_ptr_state_in_word(str, &ptr_state);
				break;
			case e_ptr_state_in_double_quotation:
				//debug_dprintf(STDERR_FILENO, "e_ptr_state_in_double_quotation\n");
				slide = case_ptr_state_in_double_quotation(str, &ptr_state, &lst);
				break;
			case e_ptr_state_in_single_quotation:
				//debug_dprintf(STDERR_FILENO, "e_ptr_state_in_single_quotation\n");
				slide = case_ptr_state_in_single_quotation(str, &ptr_state, &lst);
				break;
			case e_ptr_state_in_oneline_comment:
				//debug_dprintf(STDERR_FILENO, "e_ptr_state_in_oneline_comment\n");
				slide = case_ptr_state_in_oneline_comment(str, &ptr_state, &lst);
				break;
			case e_ptr_state_in_multiline_comment:
				//debug_dprintf(STDERR_FILENO, "e_ptr_state_in_multiline_comment\n");
				slide = case_ptr_state_in_multiline_comment(str, &ptr_state, &lst);
				break;
		}
		if (slide == 0)
		{
			// listをクリアにする
			debug_dprintf(STDERR_FILENO, "Ops!\n");
			return lst;
		}
		str += slide; // TODO
	}
	return lst;
}


#include "ast.h"
#include "libft.h"
#include "list.h"
#include "token_data.h"
#include "brackets.h"
#include "err.h"
#include "test_tools.h"

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static bool is_declaration_specifier(t_token token, t_void_list *declaration_specifier_lst)
{
	if (token.token_type == e_token_type_word)
	{
		while (declaration_specifier_lst != NULL)
		{
			
			if (ft_streq(declaration_specifier_lst->ptr.token->contents.str, token.contents.str))
			{
				return true;
			}
			declaration_specifier_lst = declaration_specifier_lst->next;
		}
		return false;
	}
	else
		return false;
}

static int infer_declaration_specifier_index(
	t_void_list *lst, /* token list */
	t_void_list *declaration_specifier_lst /* declaration_specifier_lst */
)
{
	int i;

	i = 0;
	while (lst != NULL)
	{
		if (is_declaration_specifier(*lst->ptr.token, declaration_specifier_lst))
		{
			lst = lst->next;
			i += 1;
		}
		else
			break ;
	}
	return i;
}

/// ```bnf
/// <declaration> ::= {<declaration_specifier>}+ {<init_declarator>}* ;
/// declaration最低でも一つのdeclaration_specifierを持つ
/// ```
/// 
/// ```c
/// {<declaration_specifier>}+ = collect_declaration_specifier(&tkn_lst, declaration_specifier_lst);
/// ```
t_void_list *collect_declaration_specifier(
	t_void_list **lst, /* token list */
	t_void_list *declaration_specifier_lst /* declaration_specifier_lst */
)
{
	int index;

	index = infer_declaration_specifier_index(*lst, declaration_specifier_lst);
	return void_list_cut(lst, index - 1);
}

/// =========== statement ===========

/// 渡されたトークン列から、どの式に属するかを判定する
t_stmt_type judge_stmt(t_void_list *lst)
{
	t_void_list *tkn_node;

	tkn_node = void_list_get_elem(lst, 0); // 
	switch (tkn_node->ptr.token->token_type)
	{
		case e_token_type_word:
			if (ft_streq(
				tkn_node->ptr.token->contents.str, "if"
			) || ft_streq(
				tkn_node->ptr.token->contents.str, "switch"
			))
				return e_stmt_type_labeled;
			else if (
				ft_streq(
					tkn_node->ptr.token->contents.str, "while"
				) || ft_streq(
					tkn_node->ptr.token->contents.str, "do"
				) || ft_streq(
					tkn_node->ptr.token->contents.str, "for"
				)
			)
				return e_stmt_type_iteration;
			else if (
				ft_streq(
					tkn_node->ptr.token->contents.str, "goto"
				) || ft_streq(
					tkn_node->ptr.token->contents.str, "continue"
				) || ft_streq(
					tkn_node->ptr.token->contents.str, "break"
				) || ft_streq(
					tkn_node->ptr.token->contents.str, "return"
				)
			)
				return e_stmt_type_jump;
			else if (
				ft_streq(
					tkn_node->ptr.token->contents.str, "case"
				) || ft_streq(
					tkn_node->ptr.token->contents.str, "default"
				)
			)
				return e_stmt_type_labeled;
			break ;
		case e_token_type_brace:
			return e_stmt_type_compound;
		default:
			return e_stmt_type_expr;
	}
	return -1; // ERR 
}

/// parse_compound_statement
/// 
t_parse_err *parse_compound_statement(t_void_list **lst, t_stmt **stmt_ast)
{
	t_void_list *token;

	token = void_list_get_elem(*lst, 0);
	if (token->ptr.token->token_type == e_token_type_brace)
	{
		t_stmt *stmt = malloc(sizeof(t_stmt));
	 	t_compound_stmt *compound_stmt = malloc(sizeof(t_compound_stmt));
		stmt->type_of_expr = e_stmt_type_compound;
		stmt->contents.compound_stmt = compound_stmt;
		(*stmt_ast) = stmt;
		compound_stmt->lst = NULL; // TODO:
					   // // Vec<declaration|statement>
	}
	else 
	{
		// TODO:ERROR
		return NULL;
	}
	return NULL;
}
/*
t_parse_err *parse_statement_s(t_void_list **lst, t_stmt **stmt_ast) // TODO 名前考えろ
{
	switch (judge_stmt(*lst))
	{
		case e_stmt_type_compound:
			break ;
		case e_stmt_type_expr:
			break ;
		case e_stmt_type_iteration:
			break ;
		case e_stmt_type_selection:
			break ;
		case e_stmt_type_labeled:
			break ;
		case e_stmt_type_jump:
			break ;
		default:
			debug_dprintf(STDERR_FILENO, "ERR!\n");
			break ;
	}
	return NULL;
}

/// <statement> ::= <labeled_statement>
///               | <expression_statement>
///               | <compound_statement>
///               | <selection_statement>
///               | <iteration_statement>
///               | <jump_statement>
t_stmt *parse_statement(t_void_list **lst)
{
	group_paren(lst, e_token_type_open_brace, e_token_type_close_brace, e_token_type_brace);
	return NULL; // TODO
}
*/

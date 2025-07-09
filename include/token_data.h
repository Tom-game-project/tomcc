#ifndef TOKEN_DATA_H
#define TOKEN_DATA_H

enum e_operator
{

	e_operator_add,
	e_operator_sub,
	e_operator_mul,
	e_operator_div,
	e_operator_mod,

	/// assignment
	e_operator_assignment,
	e_operator_add_assignment,
	e_operator_sub_assignment,
	e_operator_mul_assignment,
	e_operator_div_assignment,
	e_operator_mod_assignment,
	e_operator_bitshift_right_assignment,
	e_operator_bitshift_left_assignment,
	e_operator_and_assignment,
	e_operator_or_assignment,
	e_operator_xor_assignment,
	e_operator_incr,
	e_operator_decr,
	e_operator_bitshift_right,
	e_operator_bitshift_left,

	/// addr pointer
	e_operator_addr, // 最初はe_operator_logic_and として解釈される
	e_operator_pointer, // 最初はe_operator_logic_and として解釈される
	e_operator_arrow, // 最初はe_operator_logic_and として解釈される

	/// logic
	e_operator_logic_and,
	e_operator_logic_or,
	e_operator_logic_xor,
	e_operator_and,

	e_operator_or,
	e_operator_not,
	e_operator_gt,
	e_operator_ge,
	e_operator_lt,
	e_operator_le,
	e_operator_eq,
	e_operator_ne,

	e_operator_comma,
	e_operator_dot,

	/// recursive data (特別な演算子)
	e_operator_arr_index_access, // 配列のindexアクセス
	e_operator_funccall,         // 関数の呼び出し
};

typedef enum e_operator t_operator;

enum e_token_type
{
	e_token_type_comment, //           char * not null: 
	e_token_type_string,  // "string"  char * not null:
	e_token_type_char,    // 'c'       char * not null:
	e_token_type_word,    // string    char * not null
	e_token_type_open_brace, //        char * null
	e_token_type_close_brace,//        char * null
	e_token_type_open_paren, //        char * null
	e_token_type_close_paren,//        char * null
	e_token_type_open_bracket,//       char * null
	e_token_type_close_bracket,//      char * null
	e_token_type_operator,     //      char * not null;
	e_token_type_semi_colon,   //      char * null
	e_token_type_colon,        //      char * null
	e_token_type_brace,        // {}
	e_token_type_bracket,      // []
	e_token_type_paren         // ()
};

typedef enum e_token_type t_token_type;


typedef struct s_void_list t_void_list; // preventing recursive import
typedef union u_token_contents t_token_contents;
union u_token_contents
{
	char *str;
	t_operator ope;
	t_void_list *token_list;
};

typedef struct s_token t_token;
struct s_token
{
	t_token_type token_type;
	t_token_contents contents; // token_typeによってここが指す値が変わる
};

 // ========= functions ==========
 
#endif


#ifndef DRLL_H_
# define DRLL_H_
int rd_lex();
void rd_syntax_error(int expected, int token, char *output);
void parse_axiom();
void parse_expresion();
void parse_rest_expression();
void match_symbol(int expected_token);
void parse_parameter();
int open_file(char *file_name);

#endif
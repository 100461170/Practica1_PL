#ifndef DRLL_H_
# define DRLL_H_
int rd_lex();
void rd_syntax_error(int expected, int token, char *output);
void parse_statement();
void parse_expresion();
void parse_rest_expression();
void match_symbol(int expected_token);
void parse_parameter();

#endif
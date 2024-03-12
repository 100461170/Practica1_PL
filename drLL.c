/* Grupo de trabajo 03. Alejandro Díaz Cuéllar y Tomás Mendizábal */
/* 100472173@alumnos.uc3m.es 100461170@alumos.uc3m.es */

#include "drLL.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

#define T_NUMBER 1001
#define T_OP 1002
#define T_VARIABLE 1003
#define MAX 256

int g_token;  // Here we store the current token/literal
int g_value; // and the value of the number
int g_line_counter = 1;
char g_output_str[MAX];

// TODO: clean code
int rd_lex(){
    int c = getchar();
    // end of file
    if (c == EOF) {
        // printf ("\n");// Force an exit to avoid
        exit (0) ;// a Syntax Error
    }
    // digits
    if (isdigit(c)){
        ungetc(c, stdin);
        scanf("%d", &g_value);
        g_token = T_NUMBER;  
        int next_d = getchar();
        // next character
        if (next_d == ')'){
            ungetc(next_d, stdin);
            return g_token;
        }
        if (next_d != ' '){
            fprintf(stderr, "Syntax error in line: %d.\n", g_line_counter);
            exit(-1);
        }
            return g_token;     
    }
    // variable
    if (isalpha(c)){
        g_token = T_VARIABLE;
        int space = getchar();
        // next character
        if (space == ')'){
            ungetc(space, stdin);
            g_value = c;
            return g_value;
        }
        if (space != ' '){ 
            fprintf(stderr, "Syntax error in line: %d.\n", g_line_counter);
            exit(-1);
        }
        g_value = c;
        return g_token; 
    }  
    // handling of parentesis and spaces
    if (c !='(' && c != ')' && c != '\n'){
        int next_char = getchar();
        if (next_char != ' ' && next_char != ')'){
            fprintf(stderr, "Syntax error in line: %d.\n", g_line_counter);
            exit(-1);
        }
        if (next_char == ')' || next_char == '\n'){
            ungetc(next_char, stdin);
        }       
    }
    
    // new line
    if (c == '\n'){
        g_line_counter++; // info for rd_syntax_error()
    }
    g_token = c;
    return g_token; // returns a literal
}
void rd_syntax_error(int expected, int token, char * output){
    if ('\n' == g_token){
        g_line_counter--;
    }
    fprintf(stderr, "ERROR in line: %d. \n", g_line_counter);
    fprintf(stderr, output, token, expected, "\n");
    exit(-1);
}

void match_symbol(int expected_token){
    if (g_token != expected_token){
        rd_syntax_error(expected_token, g_token, "token %d expected, but %d was read.");
        exit(-1);
    }
    rd_lex();
}

#define parse_open_paren() match_symbol('(');
#define parse_close_paren() match_symbol(')');

void parse_axiom(){ //S::=E
    parse_expression();
    // print result
    strcat(g_output_str, ". \n");
    printf("%s", g_output_str);
    // reset global string
    memset(g_output_str, 0, strlen(g_output_str));
}

void parse_expression(){ // E::=(R
    parse_open_paren();
    parse_rest_expression();
}

void parse_rest_expression(){ //R::=oPP|=vP // o: Operador(token) = {+,-,*,/}. v: variable(token)
    switch(g_token){
        case '+':
        case '-':
        case '*':
        case '/':
            char oper_str[MAX];
            sprintf(oper_str, "%c ", g_token);
            rd_lex();
            parse_parameter();
            parse_parameter();
            strcat(g_output_str, oper_str);
            break;
        case '=':
            rd_lex();
            char variable_str[MAX];
            sprintf(variable_str, "%c ! ", g_value);
            match_symbol(T_VARIABLE);
            parse_parameter();
            strcat(g_output_str, variable_str);
            break;
        default: 
            if ('\n' == g_token){
                g_line_counter--;
            }
            rd_syntax_error(g_token, 0, "Token %d was read, but an operator was expected.\n");
    }
    parse_close_paren();
}

void parse_parameter(){//P::=E|v|n // n: numero(token). v: variable(token)
    switch(g_token){
        case T_NUMBER:
            char number_str[MAX];
            sprintf(number_str, "%d ", g_value);
            strcat(g_output_str, number_str);
            rd_lex();
            break;
        case T_VARIABLE:
            char t_variable_str[MAX];
            sprintf(t_variable_str, "%c @ ", g_value);
            strcat(g_output_str, t_variable_str);
            rd_lex();
            break;
        default:
            parse_expression();
    }
       
}



int main(int argc, char *argv[]){
    int flagMultiple = 1;
    // check number of arguments
    if (argc >= 2){
        if (strcmp("-s", argv[1]) == 0){
            flagMultiple = 0;
        }
    }
    do
    {
        rd_lex(); // new line
        parse_axiom();
        // printf("OK\n");
    } while (flagMultiple);


}
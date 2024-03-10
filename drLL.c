/* Grupo de trabajo 03. Alejandro Díaz Cuéllar y Tomás Mendizábal */
/* 100472173@alumnos.uc3m.es 100461170@alumos.uc3m.es */

#include "drLL.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define T_NUMBER 1001
#define T_OP 1002
#define T_VARIABLE 1003


int g_token;  // Here we store the current token/literal
int g_number; // and the value of the number
int g_line_counter = 1;

// TODO: fix line error
int rd_lex(){
    int c = getchar();
    // digits
    if (isdigit(c)){
        ungetc(c, stdin);
        scanf("%d", &g_number);
        g_token = T_NUMBER;  
        int next_d = getchar();
        // next character
        if (next_d == ')'){
            ungetc(next_d, stdin);
            return g_token;
        }
        if (next_d != ' '){
            fprintf(stderr, "Syntax error in line: %d.\n", g_line_counter);
        }
            return g_token;     
    }
    // variable
    if (isalpha(c)){
        g_token = T_VARIABLE;
        int space = getchar();
        // next character
        if (space != ' '){
            fprintf(stderr, "Syntax error in line: %d.\n", g_line_counter);
        }
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
    fprintf(stderr, "ERROR in line: %d. \n", g_line_counter);
    fprintf(stderr, output, token, expected, "\n");
    exit(-1);
}

void match_symbol(int expected_token){
    if (g_token != expected_token){
        rd_syntax_error(expected_token, g_token, "token %d expected, but %d was read.");
    }
    rd_lex();
}

#define parse_endline() match_symbol('\n');
#define parse_lparen() match_symbol('(');
#define parse_rparen() match_symbol(')');

void parse_statement(){
    parse_expresion();
    parse_endline();
}

void parse_expresion(){
    parse_lparen();
    parse_rest_expression();
}

void parse_rest_expression(){
    switch(g_token){
        case '+':
        case '-':
        case '*':
        case '/':
            rd_lex();
            parse_parameter();
            parse_parameter();
            break;
        case '=':
            rd_lex();
            match_symbol(T_VARIABLE);
            parse_parameter();
            break;
        default: 
            rd_syntax_error(g_token, 0, "Token %d was read, but and operator was expected.\n");
    }
    parse_rparen();
}

//TODO: Revisar posible syntax_error
void parse_parameter(){
    switch(g_token){
        case T_NUMBER:
        case T_VARIABLE:
            rd_lex();
            break;
        default:
            parse_expresion();
    }
       
}

int main(){
    while (1){
        rd_lex(); // new line
        parse_statement();
        printf("OK\n");
    }
    system("PAUSE");
}
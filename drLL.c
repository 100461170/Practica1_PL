/* Grupo de trabajo 03. Tomás Mendizábal y Alejandro Díaz Cuéllar */
/* 100461170@alumos.uc3m.es 100472173@alumnos.uc3m.es*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define T_NUMBER 1001
#define T_OP 1002
#define T_VARIABLE 1003

int token;  // Here we store the current token/literal
int number; // and the value of the number

int line_counter = 1;

int rd_lex(){
    int c = getchar();
    // tratamiento parentesis y espacios
    if (c !='(') {
        int siguiente = getchar();
        if (siguiente != ' ' && siguiente != ')'){
            printf(stderr, "Syntax error in line: %d\n", line_counter);
            exit(-1);
        }
        if (siguiente == ')'){
            ungetc(siguiente, stdin);
        } 
    }
    // digitos
    if (isdigit(c)){
        ungetc(c, stdin);
        scanf("%d", &number);
        token = T_NUMBER;
        return token; // returns the Token for Number
    }
    // variable
    if (isalpha(c)){
        token = T_VARIABLE;
        return token;
    }

    // salto de linea
    if (c == '\n')
        line_counter++; // info for rd_syntax_error()

    token = c;
    return token; // returns a literal
}
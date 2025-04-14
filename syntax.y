%{
#include <stdlib.h>
#include "syn.h"
#include <stdio.h>

#define YYSTYPE yyTypes

int yylex(){
    int a;
    while(a=getchar()){
        if (a == '\n' || a == '\0') {
            return 0;
        }
        if(a!='(' && a!=')' && a!='*' && a!='+' && 
            a!='>' && a!='~' && a!='!' && a!='a' && 
            a!='b' && a!='c' && a!='d' && a!='A' && 
            a!='B' && a!='C' && a!='D'){
                continue;
        }
        if(a >= 'A' && a <= 'D'){
            a+=32;
        }
        return a;
    }
}

int yyerror(expr_t **e,char *s){
    printf("error\n");
    exit(0);
}

typedef struct {
    expr_t *expr_t;
}yyTypes;
%}

%left '~' '>'
%left '+'
%left '*'
%right '!'

%parse-param {expr_t **root}
%type <expr_t> expr

%%
input: expr { *root = $1; }
expr: '(' expr ')' {
        $$ = $2;
    }
    | '!' expr { // 这里要按优先级排
        $$ = malloc(sizeof(expr_t));
        $$->left = NULL;
        $$->right = $2;
        $$->op = '!';
    }
    | expr '*' expr {
        $$ = malloc(sizeof(expr_t));
        $$->left = $1;
        $$->right = $3;
        $$->op = '*';
    }
    | expr '+' expr {
        $$ = malloc(sizeof(expr_t));
        $$->left = $1;
        $$->right = $3;
        $$->op = '+';
    }
    | expr '>' expr {
        $$ = malloc(sizeof(expr_t));
        $$->left = $1;
        $$->right = $3;
        $$->op = '>';
    }
    | expr '~' expr {
        $$ = malloc(sizeof(expr_t));
        $$->left = $1;
        $$->right = $3;
        $$->op = '~';
    }
    | 'a' {
        $$ = malloc(sizeof(expr_t));
        $$->left = NULL;
        $$->right = NULL;
        $$->op = 'a';
        useA = true;
    }
    | 'b' {
        $$ = malloc(sizeof(expr_t));
        $$->left = NULL;
        $$->right = NULL;
        $$->op = 'b';
        useB = true;
    }
    | 'c' {
        $$ = malloc(sizeof(expr_t));
        $$->left = NULL;
        $$->right = NULL;
        $$->op = 'c';
        useC = true;
    }
    | 'd' {
        $$ = malloc(sizeof(expr_t));
        $$->left = NULL;
        $$->right = NULL;
        $$->op = 'd';
        useD = true;
    }
%%

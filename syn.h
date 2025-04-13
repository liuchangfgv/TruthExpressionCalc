#ifndef SYN_H
#define SYN_H

#include <stdbool.h>

typedef struct expr_t {
    struct expr_t *left;
    struct expr_t *right;
    char op;
}expr_t;

extern bool useA;
extern bool useB;
extern bool useC;
extern bool useD;

extern int yyparse(expr_t **root);

#endif
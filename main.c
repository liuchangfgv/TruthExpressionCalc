#include "stdio.h"
#include "syn.h"
#include <stdbool.h>

bool useA = false;
bool useB = false;
bool useC = false;
bool useD = false;

bool calc(expr_t *root,bool a, bool b, bool c, bool d) {
    switch (root->op) {
        case 'a':
            return a;
        case 'b':
            return b;
        case 'c':
            return c;
        case 'd':
            return d;
        case '!':
            return !calc(root->right,a,b,c,d);
        case '*':
            return calc(root->left,a,b,c,d) && calc(root->right,a,b,c,d);
        case '+':
            return calc(root->left,a,b,c,d) || calc(root->right,a,b,c,d);
        case '>': // 这里AI自己补的我也忘了
            return !calc(root->left,a,b,c,d) || calc(root->right,a,b,c,d);
        case '~': // 这里也是
            return !calc(root->right,a,b,c,d);
    }
    fprintf(stderr, "OOps!我也不知道发生了啥，程序不应该跑到这里才对");
    return false;
}

bool calcWarper(expr_t *root,char selected1,char selected2,char selected3,char selected4) {
    bool a=false,b=false,c=false,d=false;
    if(selected1 == 'A' || selected2 == 'A' || selected3 == 'A' || selected4 == 'A'){
        a = true;
    }
    if(selected1 == 'B' || selected2 == 'B' || selected3 == 'B' || selected4 == 'B'){
        b = true;
    }
    if(selected1 == 'C' || selected2 == 'C' || selected3 == 'C' || selected4 == 'C'){
        c = true;
    }
    if(selected1 == 'D' || selected2 == 'D' || selected3 == 'D' || selected4 == 'D'){
        d = true;
    }

    return calc(root,a,b,c,d);
}

void draw(expr_t *root) {
    int numOfVar = useA + useB + useC + useD; // 用于绘制表格时确定行数和列数
    bool a,b,c,d;

    switch(numOfVar){
        case 0:
            printf("No variables used!\n");
            break;
        case 1: // 一行两列
            printf("%c\t0\t1\n",useA?'A':useB?'B':useC?'C':'D');
            printf(" \t%s\t%s\n",
                calc(root,false, false, false, false)?"🥰":"😅",
                calc(root,useA, useB, useC, useD)?"🥰":"😅" // 这里凑个巧，但不难看出
            );
            break;
        case 2: // 两行两列
            do{
                char first = useA?'A':useB?'B':useC?'C':'D';
                char second = useD?'D':useC?'C':useB?'B':'A';
                printf("%c\t%c\t0\t1\n",first,second);
                printf("0\t \t%s\t%s\n",
                    calc(root,false, false, false, false)?"🥰":"😅",
                    calcWarper(root, second,' ',' ',' ')?"🥰":"😅"
                );
                printf("1\t \t%s\t%s\n",
                    calcWarper(root, first,' ',' ',' ')?"🥰":"😅",
                    calcWarper(root, first,second,' ',' ')?"🥰":"😅"
                );
            }while(0);
            break;
        case 3: // 四行两列
            do{
                char first = useA?'A':useB?'B':useC?'C':'D';
                char secend = ({
                    char ret;
                    if(useA){
                        ret = useB?'B':useC?'C':'D';
                    }else if(useB){
                        ret = useC?'C':'D';
                    }else{
                        ret = 'D';
                    }
                    ret;
                });
                char third = useD?'D':useC?'C':useB?'B':'A';
                printf("%c\t%c%c\t00\t01\t10\t11\n",first,secend,third);
                printf("0\t  \t%s\t%s\t%s\t%s\n",
                    calc(root,false, false, false, false)?"🥰":"😅",
                    calcWarper(root, third,' ',' ',' ')?"🥰":"😅",
                    calcWarper(root, secend,' ',' ',' ')?"🥰":"😅",
                    calcWarper(root, third,secend,' ',' ')?"🥰":"😅"
                );
                printf("1\t  \t%s\t%s\t%s\t%s\n",
                    calcWarper(root, first,' ',' ',' ')?"🥰":"😅",
                    calcWarper(root, first,third,' ',' ')?"🥰":"😅",
                    calcWarper(root, first,secend,' ',' ')?"🥰":"😅",
                    calcWarper(root, first,secend,third,' ')?"🥰":"😅"
                );
            }while(0);
            break;
        case 4: // 四行四列
            do{
                printf("AB\tCD\t00\t01\t10\t11\n");
                printf("00\t  \t%s\t%s\t%s\t%s\n",
                    calc(root,false, false, false, false)?"🥰":"😅",
                    calc(root,false, false, false, true)?"🥰":"😅",
                    calc(root,false, false, true, false)?"🥰":"😅",
                    calc(root,false, false, true, true)?"🥰":"😅"
                );
                printf("01\t  \t%s\t%s\t%s\t%s\n",
                    calc(root,false, true, false, false)?"🥰":"😅",
                    calc(root,false, true, false, true)?"🥰":"😅",
                    calc(root,false, true, true, false)?"🥰":"😅",
                    calc(root,false, true, true, true)?"🥰":"😅"
                );
                printf("10\t  \t%s\t%s\t%s\t%s\n",
                    calc(root,true, false, false, false)?"🥰":"😅",
                    calc(root,true, false, false, true)?"🥰":"😅",
                    calc(root,true, false, true, false)?"🥰":"😅",
                    calc(root,true, false, true, true)?"🥰":"😅"
                );
                printf("11\t  \t%s\t%s\t%s\t%s\n",
                    calc(root,true, true, false, false)?"🥰":"😅",
                    calc(root,true, true, false, true)?"🥰":"😅",
                    calc(root,true, true, true, false)?"🥰":"😅",
                    calc(root,true, true, true, true)?"🥰":"😅"
                );
            }while(0);
            break;
        default:
            fprintf(stderr, "OOps!我也不知道发生了啥，程序不应该跑到这里才对");
            return;
    }
}

int main(){
    printf("请输入一个表达式（支持 a,b,c,d 和运算符 ! * + > ~)\n");

    expr_t *root;
    if (yyparse(&root) == 0 && root != NULL) {
        draw(root);
    } else {
        fprintf(stderr, "解析失败。\n");
    }

    return 0;
}
%{
#include <stdio.h>
#include <stdlib.h>
int id=0, dig=0, key=0, op=0;
%}
%token  ID KEY OP
%%
input: ID input { id++; }
| KEY input { key++; }
| OP input {op++;}
| ID { id++; }
| KEY { key++; }
| OP { op++;}
;
%%
#include <stdio.h>
extern FILE *yyin;
main() {
yyin = fopen("input.c", "r");
yyparse();
printf("numbers = %d\nKeywords = %d\nIdentifiers = %d\noperators =%d\n",key,id, op);
}
void yyerror() {
printf(“ parse error! Message: ");
exit(-1);
} 

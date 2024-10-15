%{
#include<stdio.h>
#include<string.h>
int sl=0,ml=0;
%}
%%
"//".* {sl++;}
"/*"[a-zA-Z0-9' '\t\n]+"*/" {ml++;}
%%
int main()
{
	yyin=fopen("input.c","r");
	yyout=fopen("output.c","w");
	yylex();
	fclose(yyin);
	fclose(yyout);
	printf("\n Number of single line comments are = %d\n",sl); 
	printf("\nNumber of multiline comments are =%d\n",ml);
	return 0;
}

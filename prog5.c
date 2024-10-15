#include<stdio.h>
#include<stdlib.h>
char op[5][5],arg1[5][5],arg2[5][5],res[5][5];
int i,n;
int main()
{
    printf("\n input statement is A=-B*(C+D)");
    printf("\n Enter the input in three address code:");
    printf("\n Enter number of line in code:");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("\n %s %s %s %s",res[i],arg1[i],op[i],arg2[i]);
    }
    printf("\n machine code");
    for(i=0;i<n;i++){
        if(strcmp(op[i],"+")==0)
        {
            printf("\n MoV R0,%s",arg1[i]);
            printf("\n ADD R0,%s",arg2[i]);
            printf("\n MoV %s,R0",res[i]);
        }
        if(strcmp(op[i],"-")==0)
        {
            printf("\n MoV R0,%s",arg1[i]);
            printf("\n sub R0,%s",arg2[i]);
            printf("\n MoV %s,R0",res[i]);
        }
        if(strcmp(op[i],"*")==0)
        {
            printf("\n MoV R0,%s",arg1[i]);
            printf("\n MUL R0,%s",arg2[i]);
            printf("\n MoV %s,R0",res[i]);
        }
        if(strcmp(op[i],"/")==0)
        {
            printf("\n MoV R0,%s",arg1[i]);
            printf("\n DIV R0,%s",arg2[i]);
            printf("\n MoV %s,R0",res[i]);
        }
        if(strcmp(op[i],"=")==0)
        {
            printf("\n MoV R0,%s",arg1[i]);
            printf("\n MoV %s,R0",res[i]);
        }
    }
}

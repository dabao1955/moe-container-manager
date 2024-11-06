%{
#include <stdio.h>
#include <string.h>
#include <linux/version.h>

#define version 0.0.1rc3

//在lex.yy.c里定义，会被yyparse()调用。在此声明消除编译和链接错误。
extern int yylex(void); 

// 在此声明，消除yacc生成代码时的告警
extern int yyparse(void); 

int yywrap()
{
	return 1;
}

// 该函数在y.tab.c里会被调用，需要在此定义
void yyerror(const char *s)
{
	printf("[error] %s\n", s);
}

int main()
{
	printf("hello");
	yyparse();
	return 0;
}
%}

%token NUMBER TOKHEAT STATE TOKTARGET TOKTEMPERATURE

%%
commands: /* empty */
| commands command
;

command: heat_switch | target_set ;

heat_switch:
TOKHEAT STATE
{
	printf("\tHeat turned on or off\n");
};

target_set:
TOKTARGET TOKTEMPERATURE NUMBER
{
	printf("\tTemperature set\n");
};
%%

#include "parser.h"



int main (int argc, char **argv, char **envp)
{
	char *str = ft_strdup("lol; ke\"osl;o;beck\"k; chebureck");
	char **str1 = ft_split(str,';');
	int i = -1;
	while(str1[++i])
		printf("str%d == %s\n", i, str1[i]);
	write(1, "kek\n", 4);
	return (0);
}
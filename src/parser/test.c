#include "parser.h"

int	*args_count(char *str, char c, int *j)
{
	int i;
	int *count;
	
	count = malloc(sizeof(int) * 2);
	count[*j] = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\"')
				i++;
		}
		if (str[i] == c || str[i] == '\0')
		{
			printf("count[%d] = %d == %c\n", (*j), i, str[i]);
			count[++(*j)] = i;
		}

	}
	return (count);
}

void	comand_clean(char **str, char c)
{
	
	int i;
	int j;
	char **tmp;

	i = 0;
	while(*str[i] == c || *str[i] == '\t' || *str[i] == ' ')
		i++;
	while (str[i])
	{
		if(*str[i] == '\t' || *str[i] == ' ')	
	}

}

char **args_split(char *str, char c)
{
	char	**av;
	int		i;
	int 	j;
	int		*ac;

	j = 0;
	ac = args_count(str, c, &j);
	av = (char **)malloc(sizeof(char *) * j);
	i = 0;
	while (i <= j)
	{
		i++;
		av[i - 1] = ft_substr(str, ac[i - 1], ac[i] - ac[i - 1]);
		comand_clean(&av[i - 1], c);
		printf("av[%d] == %s\n",i - 1,  av[i - 1]);

	}
	return (av);
}

int main (int argc, char **argv, char **envp)
{
	char *str = ft_strdup("lol | ke\"osl|o|beck\"k | chebureck");
	char **str1 = args_split(str, '|');
	int i = 0;
	while(str1[i])
	{
		printf("str%d == %s\n", i, str1[i]);
		i++;
	}
	return (0);
}
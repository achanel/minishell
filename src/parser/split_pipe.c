#include "parser.h"

int	*args_count(char *str, char *c, int *j)
{
	int i;
	int *count;
	
	count = malloc(sizeof(int) * 5);
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
		if (ft_strchr(c, str[i]) || str[i] == '\0')
		{
			count[++(*j)] = i;
		}
	}
	count[++(*j)] = ft_strlen(str);
	return (count);
}

void	comand_clean(char **str, char *c)
{
	
	int i;
	char *tmp;

	tmp = *str;

	i = 0;
	while((ft_strchr(c, tmp[i]) || tmp[i] == '\t' || tmp[i] == ' '))
	{
		i++;
		if ((tmp[i] == '\'' || tmp[i] == '\"') && ft_isalpha(tmp[i]))
			break ;
		// printf ("in clean %s\n", *str);
	}
	*str = ft_strdup(tmp + i);
}

char **args_split(char *str, char *c)
{
	char	**av;
	int		i;
	int 	j;
	int		*ac;

	j = 0;
	ac = args_count(str, c, &j);
	av = (char **)malloc(sizeof(char *) * j);
	i = 0;
	while (i < j)
	{
		i++;
		av[i - 1] = ft_substr(str, ac[i - 1], ac[i] - ac[i - 1]);
		comand_clean(&av[i - 1], c);
		// printf("av[%d] == %s\n",i - 1,  av[i - 1]);

	}
	return (av);
}

char **str_parse(char *str1, char **envp)
{
	// char *str = ft_strdup("/bin/echo l$_\"o\"l | cat > \"osl|o|beck\"k | chebureck");
	char **str2 = args_split(str, "|");
	char **str3 = NULL;
	int i = 0;
	main_parcer(str2, envp);
	while(str2[i])
	{
		// printf("str%d == %s\n", i, str2[i]);
		srt3 = args_split(str2[i], " ");
		i++;
	}
	// pipex(i, str1, envp);
	return (str3);
}



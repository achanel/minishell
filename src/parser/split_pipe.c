#include "../../includes/minishell.h"

int	*args_count(char *str, char *c, int *j)
{
	int i;
	int *count;
	
	count = malloc(sizeof(int) * 50);
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
		if (ft_strchr(c, str[i])) //|| str[i] == '\0')
		{
			// while(ft_strchr(c, str[i]))
			// 	i++;
			count[++(*j)] = i;
		}
	}
	count[++(*j)] = ft_strlen(str);
	// for(int k = 0;k < *j;k++)
	// 	printf("count[%d] == %d\n", k, count[k]);
	return (count);
}

void	comand_clean(char **str, char *c)
{
	
	int i;
	int j;
	char *tmp;

	tmp = *str;

	i = 0;
	j = ft_strlen(tmp);
	while(ft_strchr(c, tmp[i]) || tmp[i] == '\t' || tmp[i] == ' ')
		i++; 
	while(ft_strchr(c, tmp[j]) || tmp[j] == '\t' || tmp[j] == ' ')
		j--;
	j++;
	
	// while((tmp[i + j] == '\'' || tmp[i + j] == '\"') || ft_isalpha(tmp[i + j])){
	// 	j++;
	// }
		// printf ("in clean %s\n", *str);
	*str = ft_substr(tmp, i, j - i);
}

char **args_split(char *str, char *c)
{
	char	**av;
	int		i;
	int 	j;
	int		*ac;

	j = 0;
	if(str[0] == '\0')
		return(NULL);
	// while(ft_strchr(c, *str) || *str == '\t' || *str == ' ')
	// 	str++;
	// printf("prev clean %s$\n", str);
	comand_clean(&str, c);
	// printf("past clean %s$\n", str);

	ac = args_count(str, c, &j);
	av = (char **)malloc(sizeof(char *) * j);
	i = 0;
	int k = 0;
	while (i < j)
	{
		i++;
		// write(1, "lol\n", 4);
		if (ac[i] - ac[i - 1] > 0){
			av[k] = ft_substr(str, ac[i - 1], ac[i] - ac[i - 1]);
			comand_clean(&av[k], c);
			// printf("av_split[%d] == %s$\n", k, av[k]);
			k++;
		}
	}
	av[k] = NULL;
	return (av);
}

char **str_parse(char *str1, char **envp, t_fd *fd)
{
	char **str2 = NULL;

	// write(1, "lol4\n", 5);
	main_space(&str1);
	main_redir(&str1, fd);
	if(ft_strchr(" \t\0", str1[0]) && ft_strlen(str1) <= 1)
		return(NULL);
	str2 = args_split(str1, " ");
	int i = 0;
	main_parcer(str2, envp);
	
	return (str2);
}

#include "../../includes/minishell.h"

char *str2str(char *str)
{
	int i = 0, j = 0;
	char *tmp;
	

	tmp = malloc(ft_strlen(str));
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\'' || str[i] == '\"')
		i++;
	while(str[i] == '<')
		i++;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\'' || str[i] == '\"')
		i++;
	while (ft_isalnum(str[i]))
	{
		printf("str[i] == %c\n", str[i]);
		tmp[j++] = str[i++];
	}
	return(tmp);
}

char	*redir_out(char *str, int *i,char **env)
{
	int fd;
	char *file_name;

	file_name = str2str(str);
	fd = open(file_name, O_RDONLY, 0644);
	dup2(fd, 0);
	return(file_name);
}

void	parcer(char *str, char **env)
{
	int i = -1;
	while (str[++i])
	{
		// if (str[i] == '<')
		// 	str = redir_in();
		if (str[i] == '<')
			str = redir_out(str, &i, env);
	}
}

// int main(int argc, char *argv[], char **env)
// {
// 	char *str = ft_strdup("<< 	kek <1 lol");
// 	parcer(str,env);
// 	return 0;
// }


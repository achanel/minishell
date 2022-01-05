#include "../../includes/minishell.h"

char *str2str(char *str, int *i1, char c)
{
	int i = 0, j = 0;
	char *tmp;
	
	i = *i1;
	tmp = malloc(ft_strlen(str));

	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\'' || str[i] == '\"')
		i++;
	while(str[i] == c)
		i++;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\'' || str[i] == '\"')
		i++;
	while (ft_isalnum(str[i]))
	{
		// printf("str[i] == %c\n", str[i]);
		tmp[j++] = str[i++];
	}
	printf("tmp == %s\n", tmp);
	return(tmp);
}

char	*redir_in(char *str, int *i, int flag)
{
	int fd;
	char *file_name;

	file_name = str2str(str, i, '<');

	fd = open(file_name, O_RDONLY, 0644);
	dup2(fd, 0);
	return(str);
}

char	*redir_out(char *str, int *i, int flag)
{
	int fd;
	char *file_name;

	file_name = str2str(str, i, '>');
	if (flag)
		fd = open(file_name , O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd = open(file_name , O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd)
	dup2(fd, 1);
	close(fd);
	return (str);
}

void	parcer(char *str, char **env)
{
	int i = -1;
	while (str[++i])
	{ 
		if (str[i] == '<'){
			if (str[i + 1] == '<'  && str[i + 2] != '<')
			{
				str = redir_in(str, &i, 1);
			}
			else if (str[i + 1] != '<')
				str = redir_in(str, &i, 0);
		}
		if (str[i] == '>')
			if (str[i + 1] == '>'  && str[i + 2] != '>')
			{
				str = redir_out(str, &i, 1);
			}
			else if (str[i + 1] != '<')
				str = redir_out(str, &i, 0);
	}
	printf("str == %s\n", str);
}

int main(int argc, char *argv[], char **env)
{
	char *str = ft_strdup("cat < 1 <2");
	parcer(str,env);

	return 0;
}

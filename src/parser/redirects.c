#include "../../includes/minishell.h"

void	tmp_file(char *break_name)
{
	int		tmp;
	int		ret;
	char	buf[255];

	tmp = open("temp_del", O_RDWR | O_CREAT, 0644);
	if (tmp == -1)
		exit(EXIT_FAILURE);
	ret = 1;
	while (ret)
	{
		write(1, "> ", 2);
		ret = read(0, buf, 254);
		buf[ret] = '\0';
		if (strncmp(ft_strjoin(break_name, "\n"), buf, ft_strlen(buf)) == 0)
			break ;
		write(tmp, buf, ft_strlen(buf));
	}
	dup2(tmp, 0);
	close(tmp);
}

char *str2str(char *str, int *i1, char c)
{
	int i, j = 0;
	char *tmp;
	
	i = *i1;
	printf("*i1 == %d\n", *i1);
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

	// file_name = str2str(str, i, '>');
	printf("%s\n", file_name);
	if (flag)
		tmp_file(file_name);
	else
		fd = open(file_name , O_RDONLY, 0644);
	if (fd){

		dup2(fd, 1);
		close(fd);
	}
	return(str);
}

char	*redir_out(char *str, int *i, int flag)
{
	int fd;
	char *file_name;

	file_name = str2str(str, i, '>');
	printf("%s\n", file_name);
	if (flag)
		fd = open(file_name , O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd = open(file_name , O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd){

		dup2(fd, 1);
		close(fd);
	}

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
			if (str[i + 1] != '<'){

				str = redir_in(str, &i, 0);
				printf("i == %d\n", i);
			}
		}
		if (str[i] == '>'){

			if (str[i + 1] == '>'  && str[i + 2] != '>')
			{
				str = redir_out(str, &i, 1);
			}
			if (str[i + 1] != '>')
				str = redir_out(str, &i, 0);
		}
	}
	printf("str == %s\n", str);
}

int main(int argc, char *argv[], char **env)
{
	char *str = ft_strdup("cat < 1 <2");
	parcer(str,env);

	return 0;
}

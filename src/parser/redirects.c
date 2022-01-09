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
}

char *str2str(char *str, int *i, char c)
{
	int j = 0;
	char *tmp;
	
	
	// printf("*i == %c\n", str[*i]);
	tmp = malloc(ft_strlen(str) + 1);

	while (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\'' || str[*i] == '\"')
		(*i)++;
	while(str[*i] == c)
		(*i)++;
	while (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\'' || str[*i] == '\"')
		(*i)++;
	while (ft_isalnum(str[*i]))
	{
		// printf("str[i] == %c\n", str[i]);
		tmp[j++] = str[(*i)++];
	}
	tmp[j] = '\0';
	// printf("tmp == %s\n", tmp);
	return(tmp);
}

char	*redir_in(char *str, int *i, int flag)
{
	int fd;
	int j;
	char *file_name;
	char *tmp;


	j = *i;
	tmp = ft_substr(str, 0, j);
	file_name = str2str(str, i, '<');
	tmp = ft_strjoin(tmp, ft_strdup(str + *i));
	str = ft_strdup(tmp);
	*i = j;
	free(tmp);
	// file_name = str2str(str, i, '>');
	// printf("%s\n", file_name);
	if (flag){

		tmp_file(file_name);
		fd = open("temp_del", O_RDONLY, 0644);
	}
	else
		fd = open(file_name , O_RDONLY, 0644);
	if (fd){

		dup2(fd, 0);
		close(fd);
	}
	unlink("temp_del");
		// error_msg(strerror(errno));
	// printf("str redir_in == %s\n", *str);
	return(str);
}

char	*redir_out(char *str, int *i, int flag)
{
	int fd;
	int j;
	char *file_name;
	char *tmp;

	j = *i;
	tmp = ft_substr(str, 0, j);
	file_name = str2str(str, i, '>');
	tmp = ft_strjoin(tmp, ft_strdup(str + *i));
	str = ft_strdup(tmp);
	*i = j - 1; // *i = 0;
	free(tmp);

	// printf("%s\n", file_name);
	fd = 1;
		if (flag)
			fd = open(file_name , O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			fd = open(file_name , O_CREAT | O_TRUNC | O_WRONLY, 0644);

	if (fd){
		dup2(1, 1);
		close(fd);
	}
	// printf("str redir_out== %s\n", str);
	return (str);
}

static void	parcer(char **src, char **env)
{
	char *str;
	str = *src;
	int i = 0;
	while (str[i])
	{ 
		if (str[i] == '<'){
			if (str[i + 1] == '<' && str[i + 2] != '<')
			{
				str = redir_in(str, &i, 1);
			}
			if (str[i + 1] != '<'){

				str = redir_in(str, &i, 0);
				// printf("i == %d\n", i);
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
		i++;
	}
	*src = ft_strdup(str);
	free(str);
	// printf("str == %slol\n", str);
}

int	main(int argc, char **args, char **env)
{
	char *str = ft_strdup("<1 cat >4");
	parcer(&str,env);
	// for (int i = 0; str[i]; i++)
	// 	printf("str == %c %d$\n", str[i], str[i]);
	char **tmp = args_split(str, " ");
	for (int i = 0;tmp[i]; i++)
		printf("tmplen[%d] == %s\n", i, tmp[i]);


	if (execve(get_path(env, tmp[0]), tmp, env) == -1)
		write(1, "lol_kek_chebureck\n", 18);
	return 0;
}

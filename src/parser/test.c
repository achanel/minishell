#include "parser.h"

int main(int argc, char const *argv[], char **envp)
{
	char *str = ft_strdup("echo lol kek");
	char **str1 = args_split(str, ' ');
	// write(0, str, ft_strlen(str));
	write(1,'lol', 3);
	char *cmd;
	
	execve(get_path(envp, str1[0]), str1, envp);
	return 0;
}

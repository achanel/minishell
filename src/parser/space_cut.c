#include "../../includes/minishell.h"

char *space_cut(char *str)
{
	int i = 0;
	int j = 0;

	char *tmp;


	tmp = malloc(sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		if (ft_strchr(" \t\'\"", str[i])){
			if (ft_strchr("\'\"", str[i])){
				tmp[j++] = str[i++];
				while (1){
					tmp[j++] = str[i++];
					if (ft_strchr("\'\"", str[i]))
						break ;
				}
				tmp[j++] = str[i++];
			}
			if (ft_strchr(" \t", str[i])){
				while (ft_strchr(" \t", str[i])){
					i++;
				}
				i--;
				tmp[j++] = ' ';
			}
		}
		if (!ft_strchr(" \t\'\"\0", str[i])){
			tmp[j++] = str[i++];
		}
		else
			i++;
	}
	return (tmp);
}

int main(int argc, char const *argv[])
{
	char *str = ft_strdup("lo_l       \"		 ke		ek\"	chebureck");
	char **tmp;
	str = space_cut(str);
	tmp = args_split(str, " ");
	for(int i = 0; tmp[i]; i++)
		printf("%s\n", tmp[i]);
	
	return 0;
}

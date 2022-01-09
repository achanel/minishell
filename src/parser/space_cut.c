#include "../../includes/minishell.h"
const char *space_cut(char *str)
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
	tmp[j] = '\0';
	return (tmp);
}

void	main_space(char **str)
{
	*str = space_cut(*str);

}

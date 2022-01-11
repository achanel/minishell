#include "../../includes/minishell.h"
const char *space_cut(char *str)
{
	int i = 0;
	int j = 0;

	char *tmp;


	tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
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
		if (!ft_strchr(" \t\'\"", str[i])){
			tmp[j++] = str[i++];
			printf("tmp[%d] == %c\n", j - 1, tmp[j - 1]);
		}
		else
			i++;
	}
	tmp[j] = 0;
	return (tmp);
}

void	main_space(char **str)
{
	*str = ft_strdup(space_cut(*str));

}

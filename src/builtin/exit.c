/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:12:50 by achanel           #+#    #+#             */
/*   Updated: 2022/01/09 15:10:54 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	not_num_args(char *s)
{
	ft_putstr_fd(MSL, 2);
	ft_putstr_fd(": exit: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": numeric argument required", 2);
	g_status = 255;
	exit(255);
}

static int	ex_atoi(char *str)
{
	uint64_t	num;
	int			i;
	int			np;

	np = 1;
	i = 0;
	num = 0;
	if (ft_strlen(str) > 20)
		not_num_args(str);
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			np = -1;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
		num = num * 10 + (str[i++] - '0');
	if (num > 9223372036854775807 && np == 1)
		not_num_args(str);
	if (num > 9223372036854775808U && np == -1)
		not_num_args(str);
	return ((int)(np * num));
}

static int	check_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		i++;
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

void	do_exit(char **cmd)
{
	int	error_status;

	if (!cmd[1])
	{
		printf("exit\n");
		exit(0);
	}
	if (cmd[2])
	{
		error_msg("exit", "too many arguments\n", 1);
		return ;
	}
	if (check_arg(cmd[1]))
		not_num_args(cmd[1]);
	error_status = ex_atoi(cmd[1]);
	g_status = error_status % 256;
	printf("exit\n");
	exit(g_status);
}

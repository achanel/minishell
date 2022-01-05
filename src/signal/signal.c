/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:53:23 by achanel           #+#    #+#             */
/*   Updated: 2022/01/05 15:09:57 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void input_process(int signum)
{
    (void)signum;
    g_status = 130;
    printf("\n");
}

static void kill_process(int signum)
{
    (void)signum;
    g_status = 131;
    printf("Quit (core dumped)\n");
}

static void ft_handler(int signum)
{
    if (signum == SIGINT)
	{
		g_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// else if (signum == SIGQUIT)
	// {
	// 	printf("here");
	// 	// ft_putstr_fd("\b\b \b\b", 2);
	// }
}

void    exec_signal_catcher(void)
{
    signal(SIGQUIT, kill_process);
	signal(SIGINT, input_process); 
}

static void	test(int signum)
{
	printf("asdasdas");
}

void    input_signal_catcher(void)
{
    signal(SIGQUIT, test);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, ft_handler);
}

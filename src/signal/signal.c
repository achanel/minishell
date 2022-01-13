/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:53:23 by achanel           #+#    #+#             */
/*   Updated: 2022/01/13 14:50:57 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void input_process(int signum)
{
    (void)signum;
    g_status = 130;
    printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

static void kill_process(int signum)
{
    (void)signum;
    g_status = 131;
    printf("Quit (core dumped)\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void ft_handler(int signum)
{
		g_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
}

void    exec_signal_catcher(void)
{
    signal(SIGQUIT, kill_process);
	signal(SIGINT, input_process); 
}

void    input_signal_catcher(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, ft_handler);
}

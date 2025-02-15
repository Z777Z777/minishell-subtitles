/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizohin <elizohin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:34:48 by elizohin          #+#    #+#             */
/*   Updated: 2024/05/20 20:02:23 by elizohin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigquit(int sig_quit)
{
	(void)sig_quit;
	g_return_val = 131;
	ft_putstr("Quit (core dumped)\n");
}

void	handle_sigsegv(int sig_segv)
{
	(void)sig_segv;
	err_msg(NULL, "exit", NULL, 1);
	exit(1);
}

void	handle_sigint(int sig_int)
{
	(void)sig_int;
	g_return_val = 130;
	ft_putstr("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//	gere les signaux ctrl-\(SIGQUIT) & ctrl-C(SIGINT)
void	handle_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGSEGV, handle_sigsegv);
	signal(SIGINT, handle_sigint);
}

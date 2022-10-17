/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 08:26:18 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/30 11:46:13 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- SIGNAL HANDLER -------------*/
/* 	SIGINT - ctrl + C
	SIGQUIT - ctrl + \
	ctrl + D- is not a signal. It is EOF */

void	ft_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_err = 1;
	}
}

void	ft_sig_handler2(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		g_err = 130;
	}
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_err = 131;
	}
}

void	ft_sig_handler_child(int signal)
{
	if (signal == SIGINT)
	{
		exit(0);
	}
	if (signal == SIGQUIT)
	{
		exit(0);
	}
}

void	ft_sig_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \n");
		g_err = 130;
		exit(130);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:29:14 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:47:17 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dup_out(int i, t_cmd	*cmd_node, int	**pipe_fds)
{
	if (cmd_node->out_fd != STDOUT_FILENO)
	{
		if (dup2(cmd_node->out_fd, STDOUT_FILENO) < 0)
			return (1);
	}
	else if (cmd_node->next != NULL)
	{
		if (dup2(pipe_fds[i][1], STDOUT_FILENO) < 0)
			return (1);
	}
	return (0);
}

int	ft_dup_in(int i, t_cmd	*cmd_node, int	**pipe_fds)
{
	if (cmd_node->here_doc == 1)
	{
		if (dup2(cmd_node->here_fd, STDIN_FILENO) < 0)
			return (1);
	}
	else
	{
		if (cmd_node->in_fd != STDIN_FILENO)
		{
			if (dup2(cmd_node->in_fd, STDIN_FILENO) < 0)
				return (1);
		}
		else if (i != 0)
		{
			if (dup2(pipe_fds[i - 1][0], STDIN_FILENO) < 0)
				return (1);
		}
	}
	return (0);
}

/*------------- DUP STDIN AND STDOUT -------------*/
int	ft_dup(int i, t_cmd	*cmd_node, int	**pipe_fds)
{
	if (ft_dup_out(i, cmd_node, pipe_fds) == 1)
		return (1);
	if (ft_dup_in(i, cmd_node, pipe_fds) == 1)
		return (1);
	return (0);
}

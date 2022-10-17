/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 07:37:16 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:54:43 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- CREATE PIPES -------------*/
int	ft_create_pipes(int **fd, int p)
{
	int	j;

	j = 0;
	while (j < p)
	{
		if (pipe(fd[j]) < 0)
		{
			ft_putstr_fd("minishell: Unable to create pipes.\n", 2);
			g_err = 1;
			return (0);
		}
		j++;
	}
	return (1);
}

/*------------- OPENS PIPES -------------*/
int	**ft_open_pipes(int p)
{
	int	j;
	int	**fd;

	if (p == 0)
		return (NULL);
	fd = (int **)malloc(p * sizeof(int *));
	if (!fd)
	{
		ft_malloc_error();
		return (NULL);
	}
	j = 0;
	while (j < p)
	{
		fd[j] = (int *)malloc(2 * sizeof(int));
		if (!fd[j])
		{
			ft_malloc_error();
			return (NULL);
		}
		j++;
	}
	if (ft_create_pipes(fd, p) == 0)
		return (NULL);
	return (fd);
}

/*------------- CLOSE PIPES -------------*/
void	ft_close_pipes(int **fd, int p)
{
	int	i;

	i = 0;
	if (p == 0)
		return ;
	while (i < p)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

/*------------- CLOSE FILE DESCRIPTOR FOR ALL CMDS -------------*/
void	ft_close_fds(t_cmd *cmd_lst)
{
	t_cmd	*tmp;

	if (!cmd_lst)
		return ;
	tmp = cmd_lst;
	while (tmp)
	{
		if (tmp->in_fd != STDIN_FILENO)
			close(tmp->in_fd);
		if (tmp->out_fd != STDOUT_FILENO)
			close(tmp->out_fd);
		if (tmp->here_fd != STDIN_FILENO)
			close(tmp->here_fd);
		tmp = tmp->next;
	}
}

/*------------- FREE PIPE MEMORY -------------*/
void	ft_free_pipes(int **fd, int p)
{
	int	i;

	i = 0;
	if (p == 0)
		return ;
	while (i < p)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

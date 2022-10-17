/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:42:47 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:51:56 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write_to_pipe(char **arr, int *fd)
{
	int	i;
	int	len;

	i = 0;
	while (arr && arr[i])
	{
		len = ft_strlen(arr[i]);
		write(fd[1], arr[i], len);
		write(fd[1], "\n", 1);
		i++;
	}
	close(fd[1]);
	ft_free_array(arr);
}

void	ft_heredoc_fork(int *num, t_cmd *node, t_var *vars, int *fd)
{
	int		id;
	char	**arr;
	int		index;
	int		count;

	index = num[0];
	count = num[1];
	id = fork();
	if (id == -1)
		return ;
	if (id == 0)
	{
		arr = ft_read_stdin(node->cmd[index + 1]);
		if (count == 0)
			ft_heredoc_expansion(arr, vars);
		ft_write_to_pipe(arr, fd);
		exit(g_err);
	}
}

char	**ft_heredoc(int index, t_cmd *node, t_var *vars, int count)
{
	int		fd[2];
	int		status;
	int		num[2];

	status = 0;
	pipe(fd);
	signal(SIGINT, SIG_IGN);
	num[0] = index;
	num[1] = count;
	ft_heredoc_fork(num, node, vars, fd);
	close(fd[1]);
	wait(&status);
	if (WIFEXITED(status))
			g_err = WEXITSTATUS(status);
	if (g_err == 130)
	{
		close(fd[0]);
		g_err = 1;
		return (NULL);
	}
	node->here_fd = fd[0];
	count = 0;
	while (node->cmd[count])
		count++;
	return (ft_remove_redirection(node->cmd, count, index));
}

/*------------- HEREDOC HANDLING -------------*/
int	ft_handle_heredoc(t_cmd *node, t_var *vars)
{
	int		i;
	int		count;
	char	**new_cmd;

	i = -1;
	while (node->cmd[++i])
	{
		if (ft_strcmp(node->cmd[i], "<<") == 1)
		{
			if (node->here_fd != STDIN_FILENO)
				close(node->here_fd);
			if (ft_check_next_token(node->cmd[i + 1]) == 1)
				return (1);
			count = ft_count_quotes(node->cmd[i + 1]);
			node->cmd[i + 1] = ft_trim_2(node->cmd[i + 1]);
			new_cmd = ft_heredoc(i, node, vars, count);
			if (new_cmd == NULL)
				return (1);
			ft_free_array(node->cmd);
			node->cmd = new_cmd;
			i = -1;
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:23:03 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:54:20 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- FREE CHILD PROCESS MEMORY -------------*/
void	ft_free_child_memory(t_var *vars)
{
	ft_close_pipes(vars->pipe_fds, vars->pipe_count);
	ft_close_fds(vars->cmd_lst);
	ft_free_pipes(vars->pipe_fds, vars->pipe_count);
	ft_free_env(vars);
}

/*------------- GET COMMAND -------------*/
t_cmd	*ft_get_command_node(int index, t_var *vars)
{
	t_cmd	*tmp;
	int		j;

	j = 0;
	tmp = vars->cmd_lst;
	while (j != index)
	{
		tmp = tmp->next;
		j++;
	}
	return (tmp);
}

/*------------- EXECUTE COMMAND -------------*/
void	ft_execute(t_cmd *cmd_node, t_var *vars)
{
	signal(SIGINT, ft_sig_handler_child);
	signal(SIGQUIT, ft_sig_handler_child);
	if (ft_set_cmd_path(cmd_node, vars) == 1)
	{
		ft_free_child_memory(vars);
		exit(127);
	}
	ft_close_pipes(vars->pipe_fds, vars->pipe_count);
	ft_close_fds(vars->cmd_lst);
	g_err = 0;
	execve(cmd_node->cmd_path, cmd_node->cmd, vars->env_var);
	ft_free_pipes(vars->pipe_fds, vars->pipe_count);
	ft_free_list(vars);
	g_err = 1;
	exit(1);
}

/*------------- CHECK REDIRECTION, SET PATH, DUP & EXECUTE -------------*/
void	ft_child_process(int i, t_var *vars)
{
	t_cmd	*cmd_node;

	cmd_node = ft_get_command_node(i, vars);
	cmd_node = ft_redirections(cmd_node);
	if (cmd_node == NULL)
	{
		ft_free_child_memory(vars);
		g_err = 1;
		exit(1);
	}
	ft_trim_pipex(cmd_node);
	if (ft_dup(i, cmd_node, vars->pipe_fds) == 1)
	{
		ft_putstr_fd("minishell: dup2 failed\n", 2);
		ft_free_child_memory(vars);
		g_err = 1;
		exit(1);
	}
	if (built_in1(cmd_node->cmd, vars))
		built_in2(cmd_node->cmd, vars, cmd_node->out_fd);
	else
		ft_execute(cmd_node, vars);
}

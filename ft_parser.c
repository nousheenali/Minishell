/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 08:08:32 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:53:34 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- CHECK IF LAST REDIR IS < or << -------------*/
void	ft_input_redir_order(t_cmd *node)
{
	int		i;

	i = 0;
	while (node->cmd[i])
	{
		if (ft_strcmp(node->cmd[i], "<") == 1)
			node->here_doc = 0;
		if (ft_strcmp(node->cmd[i], "<<") == 1)
			node->here_doc = 1;
		i++;
	}
}

/*------------- INITIALIZES VARIABLES IN LINKED LIST -------------*/
int	init_list_variables(t_var *vars)
{
	t_cmd	*cmd_lst;

	cmd_lst = vars->cmd_lst;
	while (cmd_lst != NULL)
	{
		cmd_lst->cmd_path = NULL;
		cmd_lst->in_fd = STDIN_FILENO;
		cmd_lst->out_fd = STDOUT_FILENO;
		cmd_lst->here_doc = 0;
		cmd_lst->here_fd = STDIN_FILENO;
		ft_input_redir_order(cmd_lst);
		if (ft_handle_heredoc(cmd_lst, vars) == 1)
			return (1);
		if (cmd_lst->here_doc == 0 && cmd_lst->here_fd != STDIN_FILENO)
			close (cmd_lst->here_fd);
		cmd_lst = cmd_lst->next;
	}
	return (0);
}

/*------------- EXPAND VARIABLES, REMOVE NULL ENTRIES -------------*/
int	ft_perform_expansion(t_var *vars)
{
	t_cmd	*cmd_lst;

	cmd_lst = vars->cmd_lst;
	while (cmd_lst != NULL)
	{
		ft_expander(cmd_lst->cmd, vars);
		cmd_lst = cmd_lst->next;
	}
	cmd_lst = vars->cmd_lst;
	while (cmd_lst != NULL)
	{
		cmd_lst->cmd = ft_remove_null_entries(cmd_lst->cmd);
		cmd_lst = cmd_lst->next;
	}
	cmd_lst = vars->cmd_lst;
	while (cmd_lst != NULL)
	{
		cmd_lst->cmd = ft_split_expander(cmd_lst->cmd);
		if (cmd_lst->cmd == NULL)
			return (1);
		cmd_lst = cmd_lst->next;
	}
	return (0);
}

/*------------- INITIALIZE LIST AND EXPAND VARIABLES-------------*/
void	ft_parser(t_var *vars)
{
	if (!vars->cmd_lst)
		return ;
	if (init_list_variables(vars) == 1)
	{
		ft_free_list(vars);
		return ;
	}
	if (ft_perform_expansion(vars) == 1)
	{
		ft_free_list(vars);
		return ;
	}
	vars->cmd_count = ft_count_cmd(vars->cmd_lst);
	ft_pipex(vars);
	ft_free_list(vars);
}

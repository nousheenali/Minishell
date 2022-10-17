/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goto_builtin_parent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 06:39:12 by nali              #+#    #+#             */
/*   Updated: 2022/06/29 11:16:45 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_goto_export_parent(t_cmd	*cmd_lst, t_var *vars)
{
	cmd_lst = ft_redirections(cmd_lst);
	ft_trim_pipex(cmd_lst);
	ft_export_parent(cmd_lst->cmd, vars, cmd_lst->out_fd);
}

void	ft_goto_unset_parent(t_cmd	*cmd_lst, t_var *vars)
{
	ft_trim_pipex(cmd_lst);
	ft_unset_parent(cmd_lst->cmd, vars);
}

void	ft_goto_cd_parent(t_cmd	*cmd_lst, t_var *vars)
{
	ft_trim_pipex(cmd_lst);
	ft_cd_parent(cmd_lst->cmd, vars);
}

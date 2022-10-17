/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:43:50 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/29 10:55:01 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **cmd, t_var *vars)
{
	char	*dir;
	char	old_pwd[300];

	getcwd(old_pwd, sizeof(old_pwd));
	dir = getenv("HOME");
	if (cmd[1] != NULL && cmd[2] != NULL)
	{
		if (access(cmd[1], F_OK) != 0)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			g_err = 1;
			exit(g_err);
		}
	}
	ft_cd3(cmd, vars, dir, old_pwd);
	exit(g_err);
}

void	ft_cd_parent(char **cmd, t_var *vars)
{
	char	*dir;
	char	old_pwd[300];

	getcwd(old_pwd, sizeof(old_pwd));
	dir = getenv("HOME");
	if (cmd[1] != NULL && cmd[2] != NULL)
	{
		if (access(cmd[1], F_OK) != 0)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			g_err = 1;
			return ;
		}
	}
	ft_cd3_parent(cmd, vars, dir, old_pwd);
}

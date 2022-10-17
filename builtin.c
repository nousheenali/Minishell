/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 03:47:22 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/27 08:27:24 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in2(char **cmd, t_var *vars, int out_fd)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		ft_echo(cmd, out_fd);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		ft_cd(cmd, vars);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		ft_pwd(out_fd);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		ft_env(vars, cmd, out_fd);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		ft_export(cmd, vars, out_fd);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		ft_unset(cmd, vars);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		ft_exit(cmd);
}

int	built_in1(char **cmd, t_var *vars)
{
	char	*str;

	str = cmd[0];
	if (!cmd || !vars || !cmd[0])
		return (0);
	if (ft_strncmp(str, "echo", 5) == 0 || ft_strncmp(str, "cd", 3) == 0
		|| ft_strncmp(str, "pwd", 4) == 0 || ft_strncmp(str, "env", 4) == 0
		|| ft_strncmp(str, "export", 7) == 0 || ft_strncmp(str, "unset", 6) == 0
		|| ft_strncmp(str, "exit", 5) == 0)
		return (1);
	else
		return (0);
}

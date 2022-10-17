/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:19:17 by nali              #+#    #+#             */
/*   Updated: 2022/06/26 18:25:22 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo3(char **cmd, int fd, int j, int flag)
{
	while (cmd[j])
	{
		ft_putstr_fd(cmd[j], fd);
		j++;
		if (cmd[j])
			ft_putchar_fd(' ', fd);
	}
	if (!flag)
		ft_putchar_fd('\n', fd);
	g_err = 0;
	exit(g_err);
}

void	ft_echo2(char **cmd, int fd)
{
	int		flag;
	int		k;
	int		i;
	int		j;

	flag = 0;
	k = 1;
	j = 1;
	i = 1;
	while (cmd[k][1] && cmd[k][1] == 'n')
	{
		while (cmd[k][0] == '-' && cmd[k][i] == 'n')
			i++;
		if (cmd[k][i] == '\0')
		{
			flag = 1;
			j++;
		}
		else if (cmd[k][i] != '\0' || cmd[k][i] != 'n')
			break ;
		i = 1;
		k++;
	}
	ft_echo3(cmd, fd, j, flag);
}

void	ft_echo(char **cmd, int fd)
{
	if (!cmd[1])
	{
		ft_putchar_fd('\n', fd);
		g_err = 0;
		exit(g_err);
	}
	ft_echo2(cmd, fd);
}

void	ft_env(t_var *vars, char **cmd, int fd)
{
	int	i;

	i = 0;
	if (cmd[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_err = 127;
		exit(g_err);
	}
	while (vars->env_var[i])
	{
		if (ft_strchr(vars->env_var[i], '='))
		{
			ft_putstr_fd(vars->env_var[i], fd);
			ft_putchar_fd('\n', fd);
		}
		i++;
	}
	g_err = 0;
	exit(g_err);
}

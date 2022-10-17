/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:21:38 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:55:32 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(int fd)
{
	char	pwd[300];

	if (getcwd(pwd, sizeof(pwd)))
	{
		ft_putstr_fd(pwd, fd);
		ft_putchar_fd('\n', fd);
		g_err = 0;
		exit(g_err);
	}
	else
	{
		g_err = 1;
		exit(g_err);
	}
}

void	ft_exit(char **cmd)
{
	int	flag;

	flag = 0;
	if (!cmd[1])
		flag = 1;
	else if (cmd[1] && cmd[1][0])
	{
		flag = ft_exitb(cmd);
		if (cmd[2] != NULL)
		{
			g_err = 1;
			flag = 2;
			ft_putstr_fd("exit: too many arguments\n", 2);
			return ;
		}
		if (flag != 2 && cmd[1][0] == '-')
			g_err += ft_atoi(cmd[1]);
		if (flag != 2 && cmd[1][0] != '-')
			g_err = ft_atoi(cmd[1]);
	}
	if (flag != 2)
		exit(g_err);
}

int	ft_exitb(char **cmd)
{
	int	i;

	if (cmd[1][0] == '-')
		i = 1;
	else
		i = 0;
	while (cmd[1][i])
	{
		if (!ft_isdigit(cmd[1][i]))
		{
			g_err = 255;
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(" numeric argument required\n", 2);
			exit(g_err);
		}
		i++;
	}
	return (0);
}

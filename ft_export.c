/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 03:47:27 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/30 11:49:06 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_parent(char **cmd, t_var *vars, int fd)
{
	int		i;
	char	*err;

	if (!cmd[1])
		return (ft_export2_parent(vars, fd));
	i = 1;
	while (cmd[i] && cmd[i] != NULL)
	{
		if (ft_export7(cmd[i]) && !ft_export8(cmd[i]))
			ft_export3(cmd[i], vars);
		i++;
	}
	err = ft_is_export2(cmd);
	if (err != NULL)
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(err, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		g_err = 1;
		free(err);
	}
}

void	ft_export(char **cmd, t_var *vars, int fd)
{
	int		i;
	char	*err;

	if (!cmd[1])
		return (ft_export2(vars, fd));
	i = 1;
	while (cmd[i] && cmd[i] != NULL)
	{
		if (ft_export7(cmd[i]) && !ft_export8(cmd[i]))
			ft_export3(cmd[i], vars);
		i++;
	}
	err = ft_is_export2(cmd);
	if (err != NULL)
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(err, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		g_err = 1;
		free(err);
		exit(g_err);
	}
	exit(g_err);
}

//returns name
char	*ft_export5(char *cmd)
{
	int		i;
	char	*ret;

	i = 0;
	while (cmd[i] != '=')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, cmd, i + 1);
	return (ret);
}

// returns str after =
char	*ft_export6(char *cmd)
{
	int		i;
	char	*ret;

	i = 0;
	while (cmd[i] != '=')
		i++;
	ret = malloc(sizeof(char) * (ft_strlen(cmd) - i));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, cmd + i + 1, ft_strlen(cmd) - i + 1);
	return (ret);
}

//checks if '=' present in str
int	ft_export7(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0' && cmd[i] != '=')
		i++;
	if (ft_strlen(cmd) == i)
		return (0);
	return (1);
}

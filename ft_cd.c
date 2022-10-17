/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 03:58:55 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/29 10:48:20 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//added function:
static int	ft_strrchr2(char *str, int c)
{
	int	pos;
	int	i;

	i = 0;
	pos = -1;
	while (str[i])
	{
		if (str[i] == (char)c)
			pos = i;
		i++;
	}
	if (str[i] == c)
		return (0);
	if (pos != -1)
		return (pos);
	else
		return (-1);
}

//changed function
char	*ft_cd1(t_var *vars, char *old_pwd)
{
	char	*temp;
	char	*new_pwd;
	int		pos;

	(void)vars;
	pos = ft_strrchr2(old_pwd, '/');
	temp = ft_strdup(old_pwd);
	temp[pos] = '\0';
	new_pwd = ft_strjoin(temp, "/");
	free(temp);
	return (new_pwd);
}

void	ft_cd4(t_var *vars, char *new_pwd, char *old_pwd)
{
	ft_oldpwd(vars, old_pwd);
	ft_newpwd(vars, new_pwd);
}

void	ft_cd3(char **cmd, t_var *vars, char *dir, char *old_pwd)
{
	char	*new_pwd;

	if (!cmd[1] || cmd[1] == NULL)
		new_pwd = ft_strjoin(dir, "/");
	if (cmd[1] && cmd[1][0] && cmd[1][0] == '~')
	{
		if (cmd[1][1] == '\0')
			new_pwd = ft_strjoin(dir, "/");
		else if (cmd[1][1] == '/')
			new_pwd = ft_strjoin(dir, cmd[1] + 1);
	}
	if (cmd[1] && cmd[1][0] && cmd[1][0] == '/')
		new_pwd = ft_strdup(cmd[1]);
	if (cmd[1] && cmd[1][0] && cmd[1][0] != '/' && cmd[1][0] != '~')
		new_pwd = ft_cd2(cmd, vars, old_pwd);
	ft_cd5(new_pwd, cmd);
	ft_cd4(vars, new_pwd, old_pwd);
}

void	ft_cd3_parent(char **cmd, t_var *vars, char *dir, char *old_pwd)
{
	char	*new_pwd;

	if (!cmd[1] || cmd[1] == NULL)
		new_pwd = ft_strjoin(dir, "/");
	if (cmd[1] && cmd[1][0] && cmd[1][0] == '~')
	{
		if (cmd[1][1] == '\0')
			new_pwd = ft_strjoin(dir, "/");
		else if (cmd[1][1] == '/')
			new_pwd = ft_strjoin(dir, cmd[1] + 1);
	}
	if (cmd[1] && cmd[1][0] && cmd[1][0] == '/')
		new_pwd = ft_strdup(cmd[1]);
	if (cmd[1] && cmd[1][0] && cmd[1][0] != '/' && cmd[1][0] != '~')
		new_pwd = ft_cd2(cmd, vars, old_pwd);
	ft_cd5_parent(new_pwd, cmd);
	ft_cd4(vars, new_pwd, old_pwd);
}

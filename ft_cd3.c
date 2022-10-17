/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:43:50 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/26 13:10:46 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cd0b(t_var *vars)
{
	int		i;
	char	*new_pwd;

	i = -1;
	while (vars->env_var[++i])
	{
		if (ft_strncmp(vars->env_var[i], "OLDPWD=", 7) == 0)
			break ;
	}
	new_pwd = malloc(sizeof(char) * (ft_strlen(vars->env_var[i]) - 7 + 1));
	if (!new_pwd)
	{
		ft_malloc_error();
		return (NULL);
	}
	ft_strlcpy(new_pwd, vars->env_var[i] + 7, ft_strlen(vars->env_var[i]) - 6);
	printf("%s\n", new_pwd);
	return (new_pwd);
}

char	*ft_cd0a(char *old_pwd)
{
	char	*new_pwd;

	ft_putstr_fd("cd: OLDPWD not set\n", 2);
	new_pwd = ft_strdup(old_pwd);
	return (new_pwd);
}

char	*ft_cd0(t_var *vars, char *old_pwd)
{
	int		i;

	i = -1;
	while (vars->env_var[++i])
	{
		if (ft_strncmp(vars->env_var[i], "OLDPWD=", 7) == 0)
			break ;
	}
	if (vars->env_var[i] == NULL)
		return (ft_cd0a(old_pwd));
	else
		return (ft_cd0b(vars));
}

//updated this and added above
char	*ft_cd2(char **cmd, t_var *vars, char *old_pwd)
{
	char	*new_pwd;
	char	*tmp;

	if (cmd[1][0] == '-' && cmd[1][1] == '\0')
		new_pwd = ft_cd0(vars, old_pwd);
	else if (cmd[1][1] && cmd[1][0] == '.' && cmd[1][1] == '.' \
	&& cmd[1][2] == '\0')
		new_pwd = ft_cd1(vars, old_pwd);
	else
	{
		tmp = ft_strjoin(old_pwd, "/");
		new_pwd = ft_strjoin(tmp, cmd[1]);
		free(tmp);
	}
	return (new_pwd);
}

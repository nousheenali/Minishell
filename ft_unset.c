/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:08:56 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/27 11:51:09 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset2_parent(int j, t_var *vars)
{
	while (vars->env_var[j])
	{
		free(vars->env_var[j]);
		if (vars->env_var[j + 1] != NULL)
			vars->env_var[j] = ft_strdup(vars->env_var[j + 1]);
		else
			vars->env_var[j] = NULL;
		j++;
	}
	free(vars->env_var[j]);
	g_err = 0;
}

void	ft_unset_parent(char **cmd, t_var *vars)
{
	int		i;
	int		j;
	char	*temp;

	i = 1;
	while (cmd[i])
	{
		j = 0;
		temp = ft_strjoin(cmd[i], "=");
		while (vars->env_var[j])
		{
			if (ft_strncmp(vars->env_var[j], temp, ft_strlen(temp)) == 0)
			{
				ft_unset2_parent(j, vars);
				break ;
			}
			j++;
		}
		free(temp);
		i++;
	}
}

void	ft_unset2(int j, t_var *vars)
{
	while (vars->env_var[j])
	{
		free(vars->env_var[j]);
		if (vars->env_var[j + 1] != NULL)
			vars->env_var[j] = ft_strdup(vars->env_var[j + 1]);
		else
			vars->env_var[j] = NULL;
		j++;
	}
	free(vars->env_var[j]);
	g_err = 0;
	exit(g_err);
}

void	ft_unset(char **cmd, t_var *vars)
{
	int		i;
	int		j;
	char	*temp;

	i = 1;
	while (cmd[i])
	{
		j = 0;
		temp = ft_strjoin(cmd[i], "=");
		while (vars->env_var[j])
		{
			if (ft_strncmp(vars->env_var[j], temp, ft_strlen(temp)) == 0)
			{
				ft_unset2(j, vars);
				break ;
			}
			j++;
		}
		free(temp);
		i++;
	}
	exit(g_err);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:18:17 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/26 13:13:30 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//creates a new array conatining env variables
char	**ft_export2b(t_var *vars)
{
	int		len;
	int		i;
	char	**array;

	len = 0;
	while (vars->env_var[len])
		len++;
	array = (char **) malloc(sizeof(char *) * (len + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (vars->env_var[i])
	{
		array[i] = ft_strdup(vars->env_var[i]);
		i++;
	}
	array[i] = NULL;
	return (array);
}

//sorts the new array containing copy of env variables
void	ft_export2c(char **array, t_var *vars)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	len = 0;
	while (vars->env_var[len])
		len++;
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strncmp(array[j], array[j + 1], ft_strlen(array[j])) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

// display sorted array of env variables
void	ft_export2(t_var *vars, int fd)
{
	int		i;
	char	**array;

	array = ft_export2b(vars);
	ft_export2c(array, vars);
	i = 0;
	while (array[i] != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(array[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	g_err = 0;
	exit(g_err);
}

void	ft_export2_parent(t_var *vars, int fd)
{
	int		i;
	char	**array;

	array = ft_export2b(vars);
	ft_export2c(array, vars);
	i = 0;
	while (array[i] != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(array[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	g_err = 0;
	return ;
}

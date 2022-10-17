/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:29:15 by nali              #+#    #+#             */
/*   Updated: 2022/06/27 17:34:56 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*-------------FREE 2D ARRAY OF TYPE CHAR**-------------*/
void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*-------------FREE TOKENS 2D ARRAY -------------*/
void	ft_free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	if (tokens)
	{
		while (tokens[i])
		{
			free(tokens[i]);
			i++;
		}
		free(tokens);
	}
}

/*-------------FREE LINKED LIST-------------*/
void	ft_free_list(t_var *vars)
{
	t_cmd	*cmd_lst;
	t_cmd	*tmp;
	int		i;

	cmd_lst = vars->cmd_lst;
	while (cmd_lst != NULL)
	{
		tmp = cmd_lst;
		cmd_lst = cmd_lst->next;
		if (tmp->cmd)
		{
			i = -1;
			while (tmp->cmd[++i])
				free(tmp->cmd[i]);
			free(tmp->cmd);
		}
		if (tmp->cmd_path != NULL)
			free(tmp->cmd_path);
		free(tmp);
	}
	vars->cmd_lst = NULL;
}

/*-------------FREE ENV AND LINKED LIST IN VARS STRUCTURE-------------*/
void	ft_free_env(t_var *vars)
{
	int	i;

	i = 0;
	if (vars)
	{
		while (vars->env_var[i])
		{
			free(vars->env_var[i]);
			i++;
		}
		free(vars->env_var);
	}
}

/*-------------COUNT, SPLIT, EXPAND and TRIM TOKENS-------------*/
void	ft_free(char *buf, t_var *vars)
{
	if (buf)
		free(buf);
	ft_free_env(vars);
	ft_free_list(vars);
}

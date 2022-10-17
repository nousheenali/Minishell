/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 08:19:58 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:53:15 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- EXTRACTS COMMANDS BETWEEN PIPES -------------*/
char	**ft_extract_sub_cmd(char	**cmds, char **tokens, int start, int stop)
{
	int		i;
	int		l;

	i = 0;
	while (start < stop)
	{
		l = ft_strlen(tokens[start]);
		cmds[i] = (char *)malloc(l + 1);
		if (!cmds[i])
		{
			ft_malloc_error();
			return (NULL);
		}
		ft_strlcpy(cmds[i], tokens[start], l + 1);
		i++;
		start++;
	}
	cmds[i] = NULL;
	return (cmds);
}

/*------------- ALLOCATES MEMORY FOR A CMD NODE -------------*/
t_cmd	*ft_create_node(char **tokens, int start, int stop)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
	{
		ft_malloc_error();
		return (NULL);
	}
	new->cmd = (char **)malloc((stop - start + 1) * sizeof(char *));
	if (!new->cmd)
	{
		free(new);
		ft_malloc_error();
		return (NULL);
	}
	new->cmd = ft_extract_sub_cmd(new->cmd, tokens, start, stop);
	if (new->cmd == NULL)
	{
		free(new);
		ft_free_array(new->cmd);
		return (NULL);
	}
	new->next = NULL;
	new->cmd_path = NULL;
	return (new);
}

/*------------- ADDS NODE TO LINKED LIST -------------*/
void	ft_add_node(t_cmd **lst, t_cmd *new)
{
	t_cmd	*current;

	current = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

/*------------- CREATES LINKED LIST -------------*/
int	ft_create_list(char **tokens, t_var *vars)
{
	int		start;
	int		i;
	t_cmd	*node;

	i = 0;
	while (tokens[i])
	{
		start = i;
		while (tokens[i] && tokens[i][0] != '|')
			i++;
		node = ft_create_node(tokens, start, i);
		if (node == NULL)
			return (1);
		ft_add_node(&vars->cmd_lst, node);
		if (!tokens[i])
			break ;
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:30:40 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:59:51 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*----------- COMPARES 2 STRINGS IF THEY ARE EXCATLY SAME -------------*/
int	ft_strcmp(char *s1, char *s2)
{
	if (!s1)
		return (0);
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (1);
	else
		return (0);
}

/*------------- INITIALIAZE VARIABLES TO ZERO -------------*/
void	ft_init_var_zero(int *i, int *j, int *q0, int *q1)
{
	*i = 0;
	*j = 0;
	*q0 = 0;
	*q1 = 0;
}

/*------------- CHECKS IF CHAR IS NOT NEWLINE TAB OR SPACE -------------*/
int	ft_chk_not_space_tab_newline(int ch)
{
	if (ch != '\t' && ch != ' ' && ch != '\n')
		return (1);
	else
		return (0);
}

/*------------- PRINT LINKED LIST -------------*/
void	ft_print_list(t_cmd *cmd_lst)
{
	int		i;
	t_cmd	*current;

	i = 0;
	if (cmd_lst == NULL)
		return ;
	current = cmd_lst;
	while (current)
	{
		i = 0;
		while (current->cmd[i])
		{
			printf("%s ", current->cmd[i]);
			i++;
		}
		printf("\n");
		current = current->next;
	}
	printf("---------------\n");
}

/*------------- PRINT TOKENS -------------*/
void	ft_print_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
	printf("---------------\n");
}

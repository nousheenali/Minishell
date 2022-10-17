/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:38:50 by nali              #+#    #+#             */
/*   Updated: 2022/06/28 06:19:52 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_next_token(char *str)
{
	if (!str)
	{
		ft_putstr_fd("minishell: syntax error near unexpected ", 2);
		ft_putstr_fd("token `newline'\n", 2);
		g_err = 258;
		return (1);
	}
	if (ft_strcmp(str, "<<") || ft_strcmp(str, "<") || ft_strcmp(str, "|") \
	|| ft_strcmp(str, ">>") || ft_strcmp(str, ">"))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'\n", 2);
		g_err = 258;
		return (1);
	}
	return (0);
}

int	ft_syntax_check_2(char **tokens, int i)
{
	if (ft_strcmp(tokens[i], "<") && ft_check_next_token(tokens[i + 1]))
		return (1);
	if (ft_strcmp(tokens[i], "<<") && ft_check_next_token(tokens[i + 1]))
		return (1);
	if (ft_strcmp(tokens[i], ">") && ft_check_next_token(tokens[i + 1]))
		return (1);
	if (ft_strcmp(tokens[i], ">>") && ft_check_next_token(tokens[i + 1]))
		return (1);
	if (ft_strcmp(tokens[i], "|") && tokens[i + 1] \
	&& ft_strcmp(tokens[i + 1], "|"))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		g_err = 258;
		return (1);
	}
	return (0);
}

int	ft_syntax_check(char **tokens)
{
	int	i;

	i = 0;
	if (tokens[0] && tokens[0][0] && tokens[0][0] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		g_err = 258;
		return (1);
	}
	while (tokens[i])
	{
		if (ft_syntax_check_2(tokens, i) == 1)
			return (1);
		i++;
	}
	if (tokens[i - 1] && tokens[i - 1][0] == '|')
	{
		g_err = 0;
		ft_putstr_fd("minishell: format not supported\n", 2);
		return (1);
	}
	return (0);
}

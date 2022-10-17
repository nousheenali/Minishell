/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 05:33:08 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:57:45 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- CHECK COUNT OF CONSECUTIVE SYMBOLS ------------*/
int	ft_check_symbols(char *str, int *index, int count)
{
	int	j;
	int	i;

	i = 1;
	j = *index;
	while (str[j] && str[j + 1] && str[j] == str[j + 1])
	{
		i++;
		j++;
	}
	*index = j;
	if (i > 2 || (i > 1 && str[j] == '|'))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
		ft_putchar_fd(str[j], 2);
		ft_putchar_fd(str[j], 2);
		ft_putstr_fd("'\n", 2);
		g_err = 258;
		return (-1);
	}
	return (count + 1);
}

/*------------- CHECK IF QUOTE IS OPEN -------------*/
void	ft_handle_non_symbols(char *token, int *j, int *qv, int *open_quote)
{
	ft_check_if_quote(token, *j, qv, open_quote);
	if (*qv == 34 || *qv == 39)
	{
		ft_skip_till_next_quote(token, j, qv, open_quote);
		if (token[*j])
			*j = *j + 1;
	}
	else
		*j = *j + 1;
}

/*------------- INITIALIZE VARIABLES -------------*/
void	ft_init_var_split_count(int *i, int *count, int *qv, int *open_quote)
{
	*i = -1;
	*count = 0;
	*qv = 0;
	*open_quote = 0;
}

/*------------- COUNT NUMBER OF NEW TOKENS -------------*/
int	ft_split_count(char **tokens)
{
	int	i;
	int	j;
	int	count;
	int	qv;
	int	open_quote;

	ft_init_var_split_count(&i, &count, &qv, &open_quote);
	while (tokens[++i])
	{
		j = -1;
		while (tokens[i][++j])
		{
			if (ft_strchr(">|<", tokens[i][j]) == NULL)
				count++;
			while (ft_strchr(">|<", tokens[i][j]) == NULL && tokens[i][j])
				ft_handle_non_symbols(tokens[i], &j, &qv, &open_quote);
			if (ft_strchr(">|<", tokens[i][j]) != NULL && tokens[i][j])
				count = ft_check_symbols(tokens[i], &j, count);
			if (count == -1)
				return (-1);
			if (!tokens[i][j])
					j--;
		}
	}
	return (count);
}

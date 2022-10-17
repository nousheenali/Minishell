/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 06:26:35 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:58:58 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- COUNT QUOTES IN A TOKEN -------------*/
int	ft_count_quotes(char *input)
{
	int		i;
	int		quote_value;
	int		open_quote;
	int		count;

	i = -1;
	quote_value = 0;
	open_quote = 0;
	count = 0;
	while (input[++i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && open_quote == 0)
			quote_value = input[i];
		if (input[i] == quote_value)
		{
			open_quote += 1;
			count += 1;
		}
		if (open_quote % 2 == 0 && open_quote > 0)
		{
			quote_value = 0;
			open_quote = 0;
		}			
	}
	return (count);
}

/*------------- COPY TOKENS TO NEW LOCATION WITHOUT QUOTES -------------*/
char	*ft_trim_quotes(char *new_str, char *str)
{
	int	quote_value;
	int	open_quote;
	int	i;
	int	k;

	quote_value = 0;
	open_quote = 0;
	i = -1;
	k = 0;
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && open_quote == 0)
			quote_value = str[i];
		if (str[i] == quote_value)
			open_quote += 1;
		if (str[i] != quote_value)
			new_str[k++] = str[i];
		if (open_quote % 2 == 0 && open_quote > 0)
		{
			quote_value = 0;
			open_quote = 0;
		}
	}
	new_str[k] = '\0';
	return (new_str);
}

int	ft_strlen_test(const char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (len);
	while (*str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}

/*------------- TRIMS THE TOKENS OF ANY QUOTES -------------*/
char	*ft_trim_2(char *token)
{
	char	*new_str;
	int		c;

	c = ft_count_quotes(token);
	if (c > 0)
	{
		new_str = (char *)malloc(ft_strlen(token) - c + 1);
		if (!new_str)
		{
			ft_malloc_error();
			return (NULL);
		}
		new_str = ft_trim_quotes(new_str, token);
		free(token);
		token = new_str;
	}
	return (token);
}

int	ft_trim_pipex(t_cmd	*cmd_node)
{
	int		i;

	i = 0;
	while (cmd_node->cmd[i])
	{
		cmd_node->cmd[i] = ft_trim_2(cmd_node->cmd[i]);
		if (cmd_node->cmd[i] == NULL)
			return (1);
		i++;
	}
	return (0);
}

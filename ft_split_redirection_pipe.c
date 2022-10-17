/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_redirection_pipe.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 09:23:04 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:58:09 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- INIT VARIABLES -------------*/
void	ft_init_populate(int *qv, int *open_quote)
{
	*qv = 0;
	*open_quote = 0;
}

/*------------- SEGGREGATE PIPES, REDIRECTIONS -------------*/
void	ft_populate_new_tokens(int *j, int *k, char **new_tokens, char *str)
{
	int	start;
	int	m;
	int	n;
	int	qv;
	int	open_quote;

	m = *j;
	n = *k;
	start = m;
	ft_init_populate(&qv, &open_quote);
	if (ft_strchr(">|<", str[m]) == NULL && str[m])
	{
		while (ft_strchr(">|<", str[m]) == NULL && str[m])
			ft_handle_non_symbols(str, &m, &qv, &open_quote);
		new_tokens[n++] = ft_substr(str, start, m - start);
	}
	start = m;
	if (ft_strchr(">|<", str[m]) != NULL && str[m])
	{
		while (str[m] == str[m + 1])
			m++;
		new_tokens[n++] = ft_substr(str, start, m - start + 1);
	}
	*j = m;
	*k = n;
}

/*------------- SPLIT TOKENS -------------*/
void	ft_perform_split(char **new_tokens, char **tokens)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j])
		{
			ft_populate_new_tokens(&j, &k, new_tokens, tokens[i]);
			if (!tokens[i][j])
				j--;
			j++;
		}
		i++;
	}
	new_tokens[k] = NULL;
}

/*------------ SPLITS TOKENS ON BASIS OF PIPES AND REDIRECTIONS ------------*/
char	**ft_split_redirection_pipe(char **tokens)
{
	int		new_count;
	char	**new_tokens;

	if (!tokens || !*tokens)
		return (NULL);
	new_count = ft_split_count(tokens);
	if (new_count == -1)
		return (NULL);
	new_tokens = (char **)malloc((new_count + 1) * sizeof(char *));
	if (!new_tokens)
	{
		ft_malloc_error();
		return (NULL);
	}
	ft_perform_split(new_tokens, tokens);
	ft_free_tokens(tokens);
	return (new_tokens);
}

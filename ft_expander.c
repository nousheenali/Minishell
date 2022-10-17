/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:36:30 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:48:51 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- SKIP CHARACTERS TILL CLOSING SINGLE QUOTE -------------*/
void	ft_skip_till_next_quote(char *s, int *j, int *qval, int *open_quote)
{
	int	i;
	int	quote_val;

	i = *j;
	quote_val = *qval;
	i++;
	while (s[i] != quote_val && s[i])
		i++;
	*qval = 0;
	*open_quote = 0;
	*j = i;
}

/*------------- INITIALIAZE VARIABLES -------------*/
void	init_expander_var(int *i, int *qval, int *open_quote)
{
	*i = -1;
	*qval = 0;
	*open_quote = 0;
}

/*------------- EXPANDS ENV VARIABLES -------------*/
int	ft_handle_expansion(char **t, int i, int *j, t_var *vars)
{
	char	*sub;
	int		start;

	start = *j;
	sub = ft_handle_dollar(t[i], *j + 1, vars);
	if (ft_strlen(sub) < ft_strlen(t[i]))
		*j = -1;
	else
		*j = start;
	free(t[i]);
	if (sub == NULL)
	{
		t[i] = (char *)malloc(sizeof(char));
		if (!t[i])
		{
			ft_malloc_error();
			return (1);
		}
		t[i][0] = '\0';
		return (1);
	}
	t[i] = sub;
	return (0);
}

/*------------- EXPANDS ENV VARIABLES -------------*/
void	ft_expander(char **t, t_var *vars)
{
	int		i;
	int		j;
	int		qv;
	int		open_quote;

	init_expander_var(&i, &qv, &open_quote);
	while (t[++i])
	{
		j = 0;
		while (t[i][j])
		{
			ft_check_if_quote(t[i], j, &qv, &open_quote);
			if (t[i][j] == '$' && qv == 39)
				ft_skip_till_next_quote(t[i], &j, &qv, &open_quote);
			if (t[i][j] == '$' && t[i][j + 1] && (qv == 0 || qv == 34))
			{
				if (ft_handle_expansion(t, i, &j, vars) == 1)
					break ;
				if (j == 0)
					ft_check_if_quote(t[i], j, &qv, &open_quote);
			}
			j++;
		}
	}
}

/*------------- REMOVE EMPTY STRINGS -------------*/
char	**ft_remove_null_entries(char **t)
{
	int		i;
	int		k;
	char	**t_new;

	i = 0;
	k = 0;
	while (t[i] && t[i][0] != '\0')
		i++;
	t_new = (char **)malloc((i + 1) * sizeof(char *));
	i = -1;
	while (t[++i])
	{
		if (ft_strcmp(t[i], "\0") == 0)
		{
			t_new[k] = ft_strdup(t[i]);
			k++;
		}
	}
	t_new[k] = NULL;
	ft_free_tokens(t);
	return (t_new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 04:55:03 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:52:44 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- GETS QUOTE VALUE IF QUOTE IS OPEN -------------*/
void	ft_check_if_quote(char *s, int i, int *qval, int *openq)
{
	int	quote_value;
	int	open_quote;

	quote_value = *qval;
	open_quote = *openq;
	if ((s[i] == '\'' || s[i] == '\"') && quote_value == 0)
		quote_value = s[i];
	if (s[i] == quote_value)
		open_quote += 1;
	if (open_quote % 2 == 0 && open_quote > 0)
	{
		quote_value = 0;
		open_quote = 0;
	}
	*qval = quote_value;
	*openq = open_quote;
}

/*------------- COUNT TOKENS FOR SPLIT -------------*/
int	ft_count_tokens(char *s)
{
	int	words;
	int	i;
	int	quote_value;
	int	open_q;

	ft_init_var_zero(&words, &i, &quote_value, &open_q);
	while (s[i])
	{
		if (s[i] != '\t' && s[i] != ' ' && s[i] != '\n' && s[i] != '\0')
		{
			words++;
			while ((ft_chk_not_space_tab_newline(s[i]) || open_q == 1) && s[i])
			{
				ft_check_if_quote(s, i, &quote_value, &open_q);
				i++;
			}
			if (open_q == 1)
				return (-1);
		}
		else
			i++;
	}
	return (words);
}

/*------------- SPLIT INPUT STRING TO TOKENS -------------*/
void	ft_separate_tokens(char **t, char *s)
{
	int	i;
	int	j;
	int	start;
	int	len;
	int	q[2];

	ft_init_var_zero(&i, &j, &q[0], &q[1]);
	while (s[i])
	{
		if (s[i] != '\t' && s[i] != ' ' && s[i] != '\n' && s[i] != '\0')
		{
			start = i;
			len = 0;
			while ((ft_chk_not_space_tab_newline(s[i]) || q[1] == 1) && s[i])
			{
				ft_check_if_quote(s, i, &q[0], &q[1]);
				i++;
				len++;
			}
			t[j++] = ft_substr(s, start, len);
		}
		else
			i++;
	}
	t[j] = NULL;
}

/*------------- SPLITAND CREATE LIST -------------*/
void	ft_lexer_2(t_var	*vars, char **tokens)
{
	char	**new_tokens;

	new_tokens = NULL;
	new_tokens = ft_split_redirection_pipe(tokens);
	if (new_tokens == NULL)
	{
		ft_free_tokens(tokens);
		return ;
	}
	if (ft_syntax_check(new_tokens))
	{
		ft_free_tokens(new_tokens);
		return ;
	}
	if (ft_create_list(new_tokens, vars) == 1)
	{
		ft_free_tokens(new_tokens);
		ft_free_list(vars);
		return ;
	}
	ft_free_tokens(new_tokens);
	ft_parser(vars);
}

/*------------- COUNT TOKENS AND ALLOCATE MEMORY -------------*/
void	ft_lexer(char *input, t_var	*vars)
{
	int		count;
	char	**tokens;

	if (!*input || !input)
		return ;
	count = ft_count_tokens(input);
	if (count == -1)
	{
		ft_putstr_fd("minishell: Invalid Quotes: Format not supported.\n", 2);
		return ;
	}
	tokens = (char **)malloc((count + 1) * sizeof(char *));
	if (!tokens)
	{
		ft_malloc_error();
		return ;
	}
	ft_separate_tokens(tokens, input);
	if (!*tokens)
	{
		ft_free_tokens(tokens);
		return ;
	}
	ft_lexer_2(vars, tokens);
}

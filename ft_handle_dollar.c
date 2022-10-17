/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 05:44:55 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:51:00 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- IF VARIABLE NAME WITHIN BRACES -------------*/
char	*ft_substr_brace(char *first, char *str, int *p)
{
	char	*sub;
	int		start_brace;
	int		j;

	j = *p;
	start_brace = j;
	while (str[j] != '}' && str[j])
		j++;
	if (str[j] != '}')
	{
		if (first != NULL)
			free(first);
		sub = NULL;
		ft_putstr_fd("minishell: Syntax Error: no closing brace.\n", 2);
	}
	else
		sub = ft_substr(str, start_brace + 1, j - start_brace - 1);
	*p = j;
	return (sub);
}

/*------------- EXPANSION OF REGULAR CASES -------------*/
char	*ft_handle_normal_cases(char *str, int *p)
{
	char	*result;
	int		l;
	int		i;

	l = 0;
	i = *p;
	while (ft_isalnum(str[i + l]) || str[i + l] == '_')
		l++;
	result = ft_substr(str, i, l);
	if (!*result)
		*p = i;
	else
	{
		i = i + l - 1;
		*p = i;
	}
	return (result);
}

/*------------- IF VARIABLE NAME NOT WITHIN BRACES -------------*/
char	*ft_substr_no_brace(char *str, int *p)
{
	int		quote_pos;
	char	*result;
	int		i;

	i = *p;
	result = NULL;
	if (str[i] && (str[i] == '=' || str[i] == '+' || str[i] == '?' || \
	str[i] == ' '))
	{
		result = ft_handle_special_cases(str, result, i);
		return (result);
	}
	if (str[i] == '\'' || str[i] == '\"')
	{
		quote_pos = i;
		i++;
		while (str[i] && str[i] != str[quote_pos])
			i++;
		result = ft_substr(str, quote_pos, i - quote_pos + 1);
		*p = i;
	}
	else
		result = ft_handle_normal_cases(str, p);
	return (result);
}

/*------------- EXPANDS ENV VARIABLES -------------*/
char	*ft_handle_dollar(char *str, int p, t_var *vars)
{
	char	*var_name;
	char	*sub_str;
	char	*first;
	char	*result;
	int		flag;

	first = NULL;
	flag = 0;
	if (p > 1)
		first = ft_substr(str, 0, p - 1);
	if (str[p] == '{')
	{
		flag = 1;
		var_name = ft_substr_brace(first, str, &p);
	}
	else
		var_name = ft_substr_no_brace(str, &p);
	if (flag == -1)
		return (NULL);
	sub_str = ft_get_envp_val(var_name, vars, &flag);
	result = ft_strjoin_new(first, sub_str);
	if (str[++p])
		result = ft_strjoin_new(result, ft_substr(str, p, ft_strlen(str) - p));
	return (result);
}

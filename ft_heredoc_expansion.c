/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_expansion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:31:07 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:51:08 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_handle_dollar_heredoc(char *str, int p, t_var *vars)
{
	char	*var_name;
	char	*sub_str;
	char	*first;
	char	*result;
	int		flag;

	flag = 0;
	first = NULL;
	if (p > 1)
		first = ft_substr(str, 0, p - 1);
	var_name = ft_substr_no_brace(str, &p);
	sub_str = ft_get_envp_val(var_name, vars, &flag);
	result = ft_strjoin_new(first, sub_str);
	if (str[++p])
		result = ft_strjoin_new(result, ft_substr(str, p, ft_strlen(str) - p));
	return (result);
}

int	ft_handle_expansion_herdoc(char **t, int i, int j, t_var *vars)
{
	char	*sub;

	sub = ft_handle_dollar_heredoc(t[i], j + 1, vars);
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

void	ft_heredoc_expansion(char **arr, t_var *vars)
{
	int		i;
	int		j;

	i = -1;
	if (arr == NULL)
		return ;
	while (arr[++i])
	{
		j = -1;
		while (arr[i][++j])
		{
			if (arr[i][j] == '$' && arr[i][j + 1])
			{
				if (ft_handle_expansion_herdoc(arr, i, j, vars) == 1)
					break ;
			}
		}
	}
}

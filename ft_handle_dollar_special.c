/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_dollar_special.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:13:08 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:50:21 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- SPECIAL CASES -------------*/
char	*ft_handle_dollar_space(char *str, int i)
{
	int		j;
	int		k;
	char	*result;

	j = 0;
	while (str[i] && str[i] == ' ')
	{
		i++;
		j++;
	}
	result = (char *)malloc(j + 2);
	if (!result)
		return (NULL);
	result[0] = '$';
	k = 1;
	while (k <= j)
	{
		result[k] = ' ';
		k++;
	}
	result[k] = '\0';
	return (result);
}

/*------------- SPECIAL CASES -------------*/
char	*ft_handle_special_cases(char *str, char *result, int i)
{
	if (str[i] == '?')
	{
		result = (char *)malloc(2);
		if (!result)
			return (NULL);
		result[0] = '?';
		result[1] = '\0';
	}
	else if ((str[i] == '=' || str[i] == '+'))
	{
		result = (char *)malloc(3);
		if (!result)
			return (NULL);
		result[0] = '$';
		result[1] = str[i];
		result[2] = '\0';
	}
	if (str[i] == ' ')
		return (ft_handle_dollar_space(str, i));
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:15:17 by nali              #+#    #+#             */
/*   Updated: 2022/06/14 09:16:49 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_string_copy_new(char *s1, char *s2, char *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
		{
			p[i] = s1[i];
			i++;
		}
	}
	if (s2)
	{
		while (s2[j])
		{
			p[i] = s2[j];
			j++;
			i++;
		}
	}
	p[i] = '\0';
	return (p);
}

/*--------- STRJOIN VERSION 2 ---------*/
/*Created a new string join function so that the function tests for empty 
strings also and lets you join an empty string with a non-empty string.
This function also frees memory of incoming strings*/

char	*ft_strjoin_new(char *s1, char *s2)
{
	char	*ptr;
	int		l;

	if (!s1 && !s2)
		return (NULL);
	l = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ptr = (char *)malloc((l + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr = ft_string_copy_new(s1, s2, ptr);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_read.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:53:17 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:51:28 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_newline(char *buf)
{
	char	*str;

	if (!*buf)
	{
		free(buf);
		buf = (char *)malloc(2);
		buf[0] = '\n';
		buf[1] = '\0';
		return (buf);
	}
	str = ft_strjoin(buf, "\n");
	free(buf);
	return (str);
}

char	*ft_read_stdin_2(char *final, char *str)
{
	char	*tmp;

	tmp = ft_add_newline(final);
	final = ft_strjoin(tmp, str);
	free(tmp);
	return (final);
}

char	**ft_read_stdin(char *limiter)
{
	char	*str;
	char	*final;
	char	**arr;

	arr = NULL;
	signal(SIGINT, ft_sig_handler_heredoc);
	str = readline(">");
	if (str == NULL)
		return (NULL);
	final = ft_strdup(str);
	while (ft_strcmp(str, limiter) != 1 && str != NULL)
	{
		free(str);
		str = readline(">");
		if (ft_strcmp(str, limiter) != 1 && str != NULL)
			final = ft_read_stdin_2(final, str);
	}
	free(str);
	if (ft_strcmp(final, limiter) != 1)
		arr = ft_split(final, '\n');
	free(final);
	return (arr);
}

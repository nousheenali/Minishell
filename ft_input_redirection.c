/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:09:29 by nali              #+#    #+#             */
/*   Updated: 2022/06/28 06:32:45 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- REMOVE THE REDIRECTION OPERATOR FROM CMD ARRAY -------------*/
char	**ft_remove_redirection(char **cmd, int c, int index)
{
	int		i;
	int		j;
	char	**new_cmd;

	new_cmd = (char **)malloc((c - 1) * sizeof(char *));
	if (!new_cmd)
		exit(1);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (i == index && cmd[i + 1])
			i += 2;
		if (cmd[i])
		{
			new_cmd[j] = (char *)malloc(ft_strlen(cmd[i]) + 1);
			if (!new_cmd[j])
				exit(1);
			ft_strlcpy(new_cmd[j], cmd[i], ft_strlen(cmd[i]) + 1);
			i++;
			j++;
		}
	}
	new_cmd[j] = NULL;
	return (new_cmd);
}

/*------------- < OPERATOR -------------*/
/*	AFter opening the file remove < operator and filename
 from the command array*/
char	**ft_input_redirection(char **cmd, int index, int *fd)
{
	int		count;
	char	**new_cmd;
	int		file_fd;

	file_fd = open(cmd[index + 1], O_RDONLY);
	if (file_fd < 0)
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putstr_fd(cmd[index + 1], 2);
		ft_putchar_fd('\n', 2);
		g_err = 1;
		return (NULL);
	}
	*fd = file_fd;
	count = 0;
	while (cmd[count])
		count++;
	new_cmd = ft_remove_redirection(cmd, count, index);
	ft_free_array(cmd);
	return (new_cmd);
}

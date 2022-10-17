/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:36:57 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:53:44 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- REMOVE REDIRECTION AND GET NEW CMD -------------*/
char	**ft_output_redirection(char **cmd, int index)
{
	int		count;
	char	**new_cmd;

	count = 0;
	while (cmd[count])
		count++;
	new_cmd = ft_remove_redirection(cmd, count, index);
	ft_free_array(cmd);
	return (new_cmd);
}

/*------------- OPEN OUTPUT FILE ON TRUCATE OR APPEND MODE -------------*/
char	**ft_output(char **str, int index, t_cmd *lst_node)
{
	int		fd;
	char	*file;

	if (!lst_node->cmd[index + 1])
	{
		ft_putstr_fd("minishell: parse error\n", 2);
		g_err = 258;
		return (NULL);
	}
	file = lst_node->cmd[index + 1];
	if (ft_strcmp(str[index], ">") == 1)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putstr_fd(file, 2);
		ft_putchar_fd('\n', 2);
		g_err = 1;
		return (NULL);
	}
	lst_node->out_fd = fd;
	str = ft_output_redirection(str, index);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 12:22:08 by nali              #+#    #+#             */
/*   Updated: 2022/06/12 14:00:26 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_cmd(t_cmd *cmd_lst)
{
	int		count;
	t_cmd	*tmp;

	count = 0;
	if (!cmd_lst)
		return (count);
	tmp = cmd_lst;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

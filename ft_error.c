/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:47:00 by nali              #+#    #+#             */
/*   Updated: 2022/06/28 17:04:48 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_malloc_error(void)
{
	ft_putstr_fd("minishell: Insufficient Memory.\n", 2);
	g_err = 1;
}

void	ft_cmd_error(char *cmd)
{
	ft_putstr_fd("minishell:  command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putchar_fd('\n', 2);
	g_err = 127;
}

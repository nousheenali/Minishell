/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:08:17 by nali              #+#    #+#             */
/*   Updated: 2022/06/29 09:32:34 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*------------- GLOBAL VARIABLE - ERROR CODE -------------*/
int	g_err;

/*------------- SET SHLVL -------------*/
void	ft_shell_lvl(t_var *vars)
{
	int		i;
	char	*temp;
	char	*str;

	i = 0;
	while (vars->env_var[i])
	{
		if (ft_strncmp(vars->env_var[i], "SHLVL=", 6) == 0)
			break ;
		i++;
	}
	temp = vars->env_var[i] + 6;
	str = ft_itoa(ft_atoi(temp) + 1);
	temp = ft_strjoin("SHLVL=", str);
	free(str);
	free(vars->env_var[i]);
	vars->env_var[i] = ft_strdup(temp);
	free(temp);
}

/*------------- INITIALIZE PROMPT, ENVP -------------*/
int	ft_init_vars(t_var	*vars, char **envp)
{
	int	i;
	int	flag;

	ft_strlcpy(vars->prompt, "minishell>", 11);
	i = 0;
	flag = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
			flag = 1;
		i++;
	}
	vars->env_var = (char **)malloc((i + 1 - flag) * sizeof(char *));
	if (!vars->env_var)
	{
		ft_malloc_error();
		return (1);
	}
	ft_init_vars2(vars, envp);
	return (0);
}

void	ft_init_vars2(t_var	*vars, char **envp)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (envp[i + flag])
	{
		if (ft_strncmp(envp[i + flag], "OLDPWD=", 7) == 0)
			flag = 1;
		vars->env_var[i] = ft_strdup(envp[i + flag]);
		i++;
	}
	vars->env_var[i] = NULL;
	vars->cmd_lst = NULL;
	vars->pipe_fds = NULL;
	vars->pipe_count = 0;
	vars->num = 0;
}

/*------------- READ INPUT FROM USER LINE BY LINE -------------*/
/* 	realine() - Reads the command from user till newline
	add_history - Adds to the history of commands*/
void	ft_read_line(t_var *vars, int *flag)
{
	char	*buf;

	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	buf = readline(vars->prompt);
	if (buf != NULL)
	{
		if (*buf)
			add_history(buf);
		ft_lexer(buf, vars);
		free(buf);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		*flag = 0;
		ft_free(buf, vars);
	}
}

/*------------- MAIN FUNCTION -------------*/
int	main(int argc, char **argv, char **envp)
{
	t_var	vars;
	int		flag;

	flag = 1;
	if (argc == 1 && !argv[1])
	{
		if (ft_init_vars(&vars, envp) == 1)
			return (1);
		ft_shell_lvl(&vars);
		while (flag)
			ft_read_line(&vars, &flag);
	}
	return (0);
}

/*	following linkers required to execute the program
	gcc minishell.c -L/usr/local/lib -I/usr/local/include -lreadline */

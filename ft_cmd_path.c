/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:16:46 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:46:56 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- FREE PATH 2D ARRAY -------------*/
void	ft_free_paths(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

/*------------- RETRIEVE PATH VARIABLE FROM ENV -------------*/
char	**ft_get_path_variable(char	**env_var)
{
	char	**paths;
	char	*str;
	int		i;

	i = 0;
	if (!env_var)
		return (NULL);
	while (env_var[i])
	{
		str = env_var[i];
		if (ft_strncmp(str, "PATH=", 5) == 0)
			break ;
		i++;
	}
	paths = ft_split(str + 5, ':');
	return (paths);
}

/*------------- APPEND SLASH AT END OF THE PATH -------------*/
char	*ft_path_append_slash(char *path)
{
	int		l;
	char	end[2];
	char	*tmp;

	end[0] = '/';
	end[1] = '\0';
	l = ft_strlen(path);
	if (path[l - 1] != '/')
	{
		tmp = path;
		path = ft_strjoin(path, end);
		free(tmp);
	}
	return (path);
}

/*------------- LOOK FOR THE CORRECT CMD PATH -------------*/
char	*ft_get_cmd_path(t_cmd	*cmd_lst, char **paths)
{
	int		i;
	char	*cmd_path;

	i = 0;
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		paths[i] = ft_path_append_slash(paths[i]);
		cmd_path = ft_strjoin(paths[i], cmd_lst->cmd[0]);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	if (access(cmd_lst->cmd[0], F_OK) == 0)
	{
		cmd_path = ft_strdup(cmd_lst->cmd[0]);
		return (cmd_path);
	}
	return (NULL);
}

/*------------- SET CMD PATH VARIABLE------------*/
int	ft_set_cmd_path(t_cmd *cmd_node, t_var *vars)
{
	char	**paths;

	paths = ft_get_path_variable(vars->env_var);
	cmd_node->cmd_path = ft_get_cmd_path(cmd_node, paths);
	if (cmd_node->cmd_path == NULL)
	{
		ft_cmd_error(cmd_node->cmd[0]);
		ft_free_paths(paths);
		return (1);
	}
	ft_free_paths(paths);
	return (0);
}

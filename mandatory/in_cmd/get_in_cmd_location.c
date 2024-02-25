/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_cmd_location.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:51:16 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/12 19:58:54 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	search_in_env(t_pipex *pipex)
{
	int		i;
	char	*path;

	i = 0;
	while (pipex->env[i] != NULL)
	{
		path = ft_strjoin(pipex->env[i], "/");
		path = ft_strjoin(path, pipex->in_cmd[0]);
		if (access(path, X_OK) != -1)
		{
			pipex->in_cmd_loc = path;
			return (1);
		}
		free(path);
		i++;
	}
	return (0);
}

int	get_in_cmd_location(t_pipex *pipex)
{
	char	*cmd;

	if (pipex->in_cmd[0] == NULL)
		exit(0);
	cmd = ft_strrchr(pipex->in_cmd[0], '/');
	if (cmd != NULL)
	{
		if (access(pipex->in_cmd[0], R_OK) != -1)
		{
			pipex->in_cmd_loc = pipex->in_cmd[0];
			return (1);
		}
		else
		{
			if (errno == EACCES)
				return (3);
			else
				return (2);
		}
	}
	cmd = pipex->in_cmd[0];
	return (search_in_env(pipex));
}

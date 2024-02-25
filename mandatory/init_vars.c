/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:22:35 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/22 23:07:38 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	arglen(char *arg)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] != ' ')
			c++;
		i++;
	}
	return (c);
}

void	get_path(t_pipex *pipex, char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			path = ft_strchr(env[i], '/');
			break ;
		}
		i++;
	}
	if (path)
		pipex->env = ft_split(path, ':');
	else
		pipex->env = ft_split("  ", ':');
}

void	get_files(t_pipex *pipex, char **argv)
{
	pipex->in_file_path = argv[1];
	pipex->out_file_path = argv[4];
}

void	init_vars(t_pipex *pipex, char **argv, char **env)
{
	pipex->out_cmd_loc = NULL;
	pipex->in_cmd_loc = NULL;
	pipex->in_cmd = NULL;
	pipex->out_cmd = NULL;
	pipex->env = NULL;
	get_path(pipex, env);
	get_files(pipex, argv);
}

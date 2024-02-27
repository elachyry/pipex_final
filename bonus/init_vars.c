/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:22:35 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/27 01:37:49 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

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

char	*get_here_doc_name()
{
	char	*name;
	char	line[2];
	int		fd;
	int		c;
	
	name = malloc(sizeof(char) * 11);
	if (name == NULL)
		return (NULL);
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
	{
		free(name);
		return (NULL);
	}
	c = 0;
	while (c < 11)
	{
		read(fd, line, 1);
		if (ft_isalpha(line[0]))
		{
			name[c] = line[0];
			c++;
		}
	}
	name[c] = '\0';
	close(fd);
	return (name);
}

void	get_infile_outfile(t_pipex *pipex, char **argv)
{
	int		i;
	char	*name;

	i = 1;
	while (argv[i] != NULL)
	{
		if (i == 1)
		{
			if (pipex->is_here_doc)
			{
				name = get_here_doc_name();
				pipex->in_file_path = ft_strjoin("/tmp/", name, 0);
				free(name);
			}
			else
				pipex->in_file_path = argv[i];
		}
		if (argv[i + 1] == NULL)
			pipex->out_file_path = argv[i];
		i++;
	}
}

void	init_vars(t_pipex *pipex, char **argv, char argc, char **env)
{
	pipex->cmd_loc = NULL;
	pipex->cmd = NULL;
	pipex->env = NULL;
	pipex->delimiter = NULL;
	pipex->is_here_doc = 0;
	get_path(pipex, env);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		pipex->cmd_count = argc - 4;
		pipex->is_here_doc = 1;
		pipex->delimiter = ft_strjoin(argv[2], "\n", 0);
	}
	else
		pipex->cmd_count = argc - 3;
	pipex->pid = malloc(sizeof(int) * pipex->cmd_count);
	if (pipex->pid == NULL)
		return ;
	pipex->fd = malloc(sizeof(int *) * (pipex->cmd_count - 1));
	if (pipex->fd == NULL)
		return ;
	get_infile_outfile(pipex, argv);
}

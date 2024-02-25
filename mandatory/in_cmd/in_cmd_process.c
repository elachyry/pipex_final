/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_cmd_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:49:05 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/22 22:53:51 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	in_cmd_process(t_pipex pipex, int fd[2], char **argv, char **env)
{
	int	infile;
	int	result;

	get_in_cmd(&pipex, argv, 2);
	infile = open(pipex.in_file_path, O_RDONLY);
	if (infile == -1)
		command_error(pipex.in_file_path, 1);
	result = get_in_cmd_location(&pipex);
	if (!result)
		command_not_found(pipex.in_cmd[0], 127);
	else if (result == 2)
		command_error(pipex.in_cmd[0], 127);
	dup2(infile, 0);
	close(infile);
	dup2(fd[1], 1);
	close(fd[1]);
	close(fd[0]);
	execve(pipex.in_cmd_loc, pipex.in_cmd, env);
	command_error("execve", 1);
}

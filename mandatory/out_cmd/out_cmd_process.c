/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_cmd_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:50:48 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/21 21:30:33 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	out_cmd_process(t_pipex pipex, int fd[2], char **argv, char **env)
{
	int	out_fd;
	int	result;

	get_out_cmd(&pipex, argv, 3);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	out_fd = open(pipex.out_file_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (out_fd == -1)
		command_error(pipex.out_file_path, 1);
	result = get_out_cmd_location(&pipex);
	if (!result)
		command_not_found(pipex.out_cmd[0], 127);
	else if (result == 2)
		command_error(pipex.out_cmd[0], 127);
	else if (result == 3)
		command_error(pipex.out_cmd[0], 126);
	dup2(out_fd, 1);
	close(out_fd);
	execve(pipex.out_cmd_loc, pipex.out_cmd, env);
	command_error("execve", 1);
}

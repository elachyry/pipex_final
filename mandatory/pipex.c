/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:28:17 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/22 23:35:35 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	parent_process(t_pipex pipex, int fd[2], int pid[2], int *return_status)
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	if (waitpid(pid[0], &status, 0) == -1)
		command_error("waitpid", 1);
	if (waitpid(pid[1], &status, 0) == -1)
		command_error("waitpid", 1);
	if (WIFEXITED(status))
		*return_status = WEXITSTATUS(status);
	free_up(&pipex);
}

void	start_program(t_pipex pipex, char **argv,
		char **env, int *return_status)
{
	int	fd[2];
	int	pid[2];

	if (pipe(fd) == -1)
		command_error("pipe", 1);
	pid[0] = fork();
	if (pid[0] == -1)
		command_error("fork", 1);
	if (pid[0] == 0)
		in_cmd_process(pipex, fd, argv, env);
	else
	{
		pid[1] = fork();
		if (pid[1] == -1)
			command_error("fork", 1);
		if (pid[1] == 0)
			out_cmd_process(pipex, fd, argv, env);
		else
			parent_process(pipex, fd, pid, return_status);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		return_status;

	if (argc != 5 || env == NULL)
		return (1);
	init_vars(&pipex, argv, env);
	return_status = 0;
	start_program(pipex, argv, env, &return_status);
	return (return_status);
}

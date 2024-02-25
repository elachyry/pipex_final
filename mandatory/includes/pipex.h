/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:55:21 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/22 22:53:59 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	**env;
	char	**in_cmd;
	char	**out_cmd;
	char	*in_cmd_loc;
	char	*out_cmd_loc;
	char	*in_file_path;
	char	*out_file_path;
}	t_pipex;

//libft
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
char	**ft_split(char const *s, char sep);
char	**ft_split_2(char const *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *str1, const char *str2, size_t n);

//init
void	init_vars(t_pipex *pipex, char **argv, char **env);
int		get_in_cmd_location(t_pipex *pipex);
int		get_out_cmd_location(t_pipex *pipex);
void	free_table(char **tab);

//exceptions
void	command_error(char *msg, int exit_val);
void	free_up(t_pipex *pipex);
void	command_not_found(char *cmd, int exit_val);

void	get_in_cmd(t_pipex *pipex, char **argv, int i);
void	get_out_cmd(t_pipex *pipex, char **argv, int i);
void	in_cmd_process(t_pipex pipex, int fd[2], char **argv, char **env);
void	out_cmd_process(t_pipex pipex, int fd[2], char **argv, char **env);
int		arglen(char *arg);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_out_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:10:11 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/21 21:27:47 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_out_cmd(t_pipex *pipex, char **argv, int i)
{
	char	**result;
	int		j;

	if (!arglen(argv[3]))
		exit(0);
	result = ft_split_2(argv[i]);
	if (result[0] == NULL)
		return ;
	j = 0;
	while (result[j] != NULL)
		j++;
	pipex->out_cmd = malloc(sizeof(char **) * (j + 1));
	if (pipex->out_cmd == NULL)
		return ;
	j = 0;
	while (result[j] != NULL)
	{
		pipex->out_cmd[j] = result[j];
		j++;
	}
	pipex->out_cmd[j] = NULL;
	free(result);
}

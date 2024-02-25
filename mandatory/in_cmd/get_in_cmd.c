/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:01:36 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/22 23:07:45 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_in_cmd(t_pipex *pipex, char **argv, int i)
{
	char	**result;
	int		j;

	if (!arglen(argv[2]))
		exit(0);
	result = ft_split_2(argv[i]);
	if (result[0] == NULL)
		return ;
	j = 0;
	while (result[j] != NULL)
		j++;
	pipex->in_cmd = malloc(sizeof(char **) * (j + 1));
	if (pipex->in_cmd == NULL)
		return ;
	j = 0;
	while (result[j] != NULL)
	{
		pipex->in_cmd[j] = result[j];
		j++;
	}
	pipex->in_cmd[j] = NULL;
	free(result);
}

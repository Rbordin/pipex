/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbordin <rbordin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:00:40 by rbordin           #+#    #+#             */
/*   Updated: 2023/04/17 10:13:07 by rbordin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cancel(t_pipex *pipex)
{
	close(pipex->out_fd);
	close(pipex->in_fd);
	cleaner1(pipex->argv2);
	cleaner1(pipex->argv3);
	free(pipex);
}

void	cleaner1(char **matrix)
{
	int	x;
	x = -1;
	while (matrix[++x])
		free (matrix[x]);
	free(matrix);
}
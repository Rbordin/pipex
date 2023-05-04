/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbordin <rbordin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:00:40 by rbordin           #+#    #+#             */
/*   Updated: 2023/05/04 14:14:10 by rbordin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cancel(t_pipex *pipex)
{
	close(pipex->out_fd);
	close(pipex->in_fd);
	cleaner1(pipex->argv2);
	cleaner1(pipex->argv3);
	cleaner1(pipex->tacos);
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

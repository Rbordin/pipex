/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riccardobordin <riccardobordin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:43:53 by riccardobor       #+#    #+#             */
/*   Updated: 2023/03/25 14:29:13 by riccardobor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int pipes[PROCES_NUM + 1][2];
	int	i;
	int pids[PROCES_NUM];
	int	j;
	int	x;
	int	y;

	j = 0;
	i = 0;
	if (argc < 2)
	{
		perror("not enough arguments");
	}
	else
	{
		while (i < PROCES_NUM + 1)
		{
			if (pipe(pipes[i]) == -1)
				perror("error creating pipes\n");	
			i++;
		}
	}
	
	i = 0;
	while (i < PROCES_NUM)
	{
		pids[i] = fork();
		
		if (pids[i] == -1)
			perror("error creating process\n");
		if (pids[i] == 0) //child process
		{
			while (j < PROCES_NUM + 1)
			{
				if (i != j)
					close(pipes[j][0]);
				if (i + 1 != j)
					close(pipes[j][1]);
				j++;		
			}
			if (read(pipes[i][0], &x, sizeof(int)) == -1)
				perror("error reading\n");
			x++;
			if (write(pipe[i + 1][1], &x, sizeof(int)) == -1)
				perror("error writing\n");
			close(pipe[i][0]);
			close(pipe[i + 1][1]);
			return (0);
		}
	}
	//father process
	j = 0;
	while (j < PROCES_NUM + 1)
	{
		if (j != PROCES_NUM)
			close(pipes[j][0]);
		if (j != 0)
			close(pipes[j][1]);
		j++;		
	}
	y = 5;
	if (write(pipes[0][1], &y, sizeof(int)) == -1)
		perror("error at writing\n");
	if (read(pipes[PROCES_NUM][0], &y, sizeof(int)) == -1)
		perror("error at reading\n");
	close(pipes[0][1]);
	close(pipes[PROCES_NUM][0]);
	while (i < PROCES_NUM)
		wait(NULL);
	i++;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbordin <rbordin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:00:40 by rbordin           #+#    #+#             */
/*   Updated: 2023/04/07 15:05:34 by rbordin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ranger(char *temp, char **envp)
{
	int		i;
	char	*test;
	char	*res;

	i = 0;
	while (envp[i++])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			break ;
	}
	res = (char *)malloc(sizeof(char) * ft_strlen(envp[i]) - 4);
	printf("res = %p\n", res);
	res = ft_pathfinder(res, envp[i]);
	res = finder(temp, res);
	return (res);
}

char	*ft_pathfinder(char *dst, char *src)
{
	size_t	i;
	int		j;
	
	j = 0;
	i = 0;
	
	printf("src = %p\n", src);
	printf("dst = %p\n", dst);
	if (!dst && !src)
		return (NULL);
	while (src[i] != '=')
		i++;
	i++;
	while (src[i])
	{
		((char *)dst)[j] = ((char *)src)[i];
		i++;
		j++;
	}
	return (dst);
}

int	sex(t_pipex *pipex)
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
	{
		ft_putstr_fd("error forking\n", 1);
		return (-1);
	}
	if (pipex->pid1 == 0)
	{
		close(pipex->fd[0]);
		dup2(pipex->fd[1], 1);
		dup2(pipex->infile_fd, 0);
		execve(pipex->argv2[0], pipex->argv2, NULL);
	}
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
	{
		ft_putstr_fd("error forking\n", 1);
		return (-1);
	}
	if (pipex->pid2 == 0)
 	{
		dup2(pipex->fd[0], 0);
		dup2(pipex->outfile_fd, 1);
		close(pipex->fd[1]);
		execve(pipex->argv3[0], pipex->argv3, NULL);
	}
	return (1);
}


void	cancel(t_pipex *pipex)
{
	close(pipex->outfile_fd);
	close(pipex->infile_fd);
	cleaner1(pipex->argv2);
	cleaner1(pipex->argv3);
}

void	cleaner1(char **matrix)
{
	int	x;
	printf("ci proviam\n");
	x = -1;
	while (matrix[++x])
	{
		free(matrix[x]);
	}
	free(matrix);
}

char	*finder(char *temp, char *path)
{
	char	**tacos;
	int		i;
	char	*burritos;
	int		flag;
	
	i = 0;
	flag = 0;
	tacos = ft_split(path, ':');
	while (tacos[i])
	{
		tacos[i] = ft_strjoin(tacos[i], "/", FREE, NO_FREE);
		burritos = ft_strjoin(tacos[i], temp, FREE, NO_FREE);
		printf("burritos = %p\n", burritos);
		if (!access(burritos, 0))
		{
			tacos[i] = ft_strjoin(tacos[i], temp, FREE, NO_FREE);
			flag = 1;
			break ;
		}
		i++;
		free(burritos);
	}
	if (flag)
	{
		return (tacos[i]);
	}
	else
		perror("command not found");
	return (NULL);
}

void	print_matrix(char **matrix)
{
	int x;

	x = 0;
	while (matrix[x])
	{
		printf("porcodio = %s\n", matrix[x]);
		x++;
	}
}

void	free_tacos(char **tacos, int i)
{
	int x;

	x = 0;
	while (x++ < i)
		free(tacos[x]);
	x += 2;
	while (tacos[x])
		free (tacos[x]);
}
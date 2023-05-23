/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbordin <rbordin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:00:40 by rbordin           #+#    #+#             */
/*   Updated: 2023/05/22 14:08:14 by rbordin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ranger(t_pipex *pipex, char *temp, char **envp)
{
	int		i;
	char	*res;
	char	*final;

	i = 0;
	res = NULL;
	pipex->flag = 0;
	while (envp[i++])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			break ;
	}
	res = ft_pathfinder(res, envp[i]);
	res = finder(pipex, temp, res);
	final = ft_strdup(res);
	free(res);
	return (final);
}

char	*ft_pathfinder(char *dst, char *src)
{
	int		j;
	size_t	i;
	size_t	k;

	j = 0;
	i = 0;
	k = 0;
	if (!dst && !src)
		return (NULL);
	while (src[i] != '=')
		i++;
	i++;
	while (src[k])
		k++;
	dst = ft_calloc((k - i + 1), sizeof(char));
	while (src[i])
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	return (dst);
}

int	sex(t_pipex *pipex)
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		error("error forking\n");
	if (pipex->pid1 == 0)
	{
		close(pipex->fd[0]);
		dup2(pipex->fd[1], 1);
		dup2(pipex->in_fd, 0);
		execve(pipex->argv2[0], pipex->argv2, NULL);
	}
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		error("error forking\n");
	if (pipex->pid2 == 0)
	{
		dup2(pipex->fd[0], 0);
		dup2(pipex->out_fd, 1);
		close(pipex->fd[1]);
		execve(pipex->argv3[0], pipex->argv3, NULL);
	}
	return (1);
}

char	*finder(t_pipex *pipex, char *temp, char *path)
{
	pipex->i = -1;
	pipex->tacos = ft_split(path, ':');
	while (pipex->tacos[++pipex->i])
	{
		iteration(pipex, pipex->i, temp);
		if (access(pipex->burritos, F_OK) == 0)
		{
			free(pipex->tacos[pipex->i]);
			pipex->tacos[pipex->i] = ft_strdup(pipex->burritos);
			free(pipex->burritos);
			pipex->flag = 1;
			break ;
		}
		else if (pipex->tacos[pipex->i + 1] == NULL)
			error("command not found\n");
		free(pipex->burritos);
	}
	pipex->burritos = ft_strdup(pipex->tacos[pipex->i]);
	cleaner1(pipex->tacos);
	free(temp);
	free(path);
	if (pipex->flag == 1)
		return (pipex->burritos);
	return (NULL);
}

void	iteration(t_pipex *pipex, int i, char *temp)
{
	pipex->slash = "/";
	pipex->tacos[i] = ft_strjoin(pipex->tacos[i],
			pipex->slash, FREE, NO_FREE);
	pipex->burritos = ft_strjoin(pipex->tacos[i],
			temp, NO_FREE, NO_FREE);
}

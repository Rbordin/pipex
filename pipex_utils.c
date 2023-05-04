/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbordin <rbordin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:00:40 by rbordin           #+#    #+#             */
/*   Updated: 2023/05/04 14:16:17 by rbordin          ###   ########.fr       */
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
		perror("error forking\n");
	if (pipex->pid1 == 0)
	{
		close(pipex->fd[0]);
		dup2(pipex->fd[1], 1);
		dup2(pipex->in_fd, 0);
		execve(pipex->argv2[0], pipex->argv2, NULL);
	}
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		perror("error forking\n");
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
	int		i;

	i = 0;
	pipex->tacos = ft_split(path, ':');
	while (pipex->tacos[i++])
	{
		iteration(pipex, i, temp);
		if (!access(pipex->burritos, 0))
		{
			free(pipex->tacos[i]);
			pipex->tacos[i] = ft_strdup(pipex->burritos);
			free(pipex->burritos);
			pipex->flag = 1;
			break ;
		}
		free(pipex->burritos);
	}
	pipex->burritos = ft_strdup(pipex->tacos[i]);
	cleaner1(pipex->tacos);
	free(temp);
	free(path);
	if (pipex->flag)
		return (pipex->burritos);
	perror("command not found");
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

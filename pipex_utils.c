/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbordin <rbordin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:00:40 by rbordin           #+#    #+#             */
/*   Updated: 2023/04/17 10:36:15 by rbordin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ranger(char *temp, char **envp)
{
	int		i;
	char	*res;
	char	*final;

	i = 0;
	res = NULL;
	while (envp[i++])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			break ;
	}
	res = ft_pathfinder(res, envp[i]);
	res = finder(temp, res);
	final = ft_strdup(res);
	free(res);
	return (final);
}

char	*ft_pathfinder(char *dst, char *src)
{
	size_t	i;
	int		j;
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

char	*finder(char *temp, char *path)
{
	char	**tacos;
	int		i;
	char	*burritos;
	int		flag;
	char	*slash;

	i = 0;
	flag = 0;
	tacos = ft_split(path, ':');
	free(path);
	while (tacos[i++])
	{
		slash = "/";
		tacos[i] = ft_strjoin(tacos[i], slash, FREE, NO_FREE);
		burritos = ft_strjoin(tacos[i], temp, NO_FREE, NO_FREE);
		if (!access(burritos, 0))
		{
			free(tacos[i]);
			tacos[i] = ft_strdup(burritos);
			free(burritos);
			flag = 1;
			break ;
		}
		free(burritos);
	}
	burritos = ft_strdup(tacos[i]);
	free(temp);
	cleaner1(tacos);
	if (flag)
		return (burritos);
	else
		perror("command not found");
	return (NULL);
}

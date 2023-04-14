/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbordin <rbordin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:11:46 by rbordin           #+#    #+#             */
/*   Updated: 2023/04/11 15:20:12 by rbordin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	
	pipex = malloc(sizeof(t_pipex));
	if (argc < 5)
		ft_putstr_fd("not enough arguments\n", 1);
	if (pipe(pipex->fd) == -1)
		ft_putstr_fd("pipe didn't work properly\n", 1);
	if ((pipex->infile_fd = open(argv[1], O_RDONLY)) == -1)
		ft_putstr_fd("reading error\n", 1);
	if ((pipex->outfile_fd = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0777)) == -1)
		ft_putstr_fd("reading error\n", 1);
	checking_argv(pipex, argv, envp);
	if (sex(pipex) < 0)
		return (1);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
	cancel(pipex);
	return(0);
}

void	checking_argv(t_pipex *pipex, char **argv, char **envp)
{
	int x;
	int y;
	
	pipex->temp2 = remover(argv[2]);
	pipex->temp2_matrix = ft_split(pipex->temp2, ' ', NO_FREE);
	x = -1;
	while (pipex->temp2_matrix[++x])
		printf("--> %s\n", pipex->temp2_matrix[x]);	
	x = checazzoneso(pipex->temp2_matrix);
	printf("x = %d\n", x);
	pipex->argv2 = ft_calloc((x + 1), sizeof(char *));
	pipex->argv2 = moving_matrix(pipex->argv2, pipex->temp2_matrix, envp);
	y = 0;
	pipex->temp3 = remover(argv[3]);
	pipex->temp3_matrix = ft_split(pipex->temp3, ' ', NO_FREE);
	y = checazzoneso(pipex->temp3_matrix);
	printf("y = %d\n", y);
	pipex->argv3 = ft_calloc((y + 1), sizeof(char *));
	pipex->argv3 = moving_matrix(pipex->argv3, pipex->temp3_matrix, envp);
	//cleaner1(pipex->temp2_matrix);
	//cleaner1(pipex->temp3_matrix);

}

char	**moving_matrix(char **final_matrix, char **temp_matrix, char **envp)
{
	int	x;
	int	j;
	char *path;
	x = 1;
	j = 1;
	path = ranger(temp_matrix[0], envp);
	final_matrix[0] = ft_calloc((ft_strlen(path) + 1), sizeof(char));
	final_matrix[0] = ft_memmove(final_matrix[0], path, ft_strlen(path));
	printf("matrix0 = %s\n", final_matrix[0]);
	while (temp_matrix[j])
	{
		final_matrix[x] = ft_calloc((ft_strlen(temp_matrix[j])), sizeof(char));
		final_matrix[x] = ft_memmove(final_matrix[x], temp_matrix[j], ft_strlen(temp_matrix[j]));
		free(temp_matrix[j]);
		printf("FM[%d] = %s\n", x, final_matrix[x]);
		printf("TM[%d] = %s\n", j, temp_matrix[j]);
		x++;
		j++;
	}
	final_matrix[j] = NULL;
	free(temp_matrix[0]);
	free(temp_matrix);
	print_matrix(final_matrix);
	printf("pointer = %p\n", temp_matrix);
	return (final_matrix);
}

char	*remover(char *temp)
{
	int	i;
		
	i = 0;
	while (temp[i++])
	{
		if (temp[i] == '\'' || temp[i] == '\"')
			temp[i] = ' ';
	}
	return (temp);
}

int	checazzoneso(char **temp_matrix)
{
	int	i;
	
	i = 0;
	while (temp_matrix[i])
		i++;
	return (i);
}



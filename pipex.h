/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbordin <rbordin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:45:12 by riccardobor       #+#    #+#             */
/*   Updated: 2023/04/07 11:55:03 by rbordin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define PROCES_NUM 3

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <signal.h>
# include "libft/libft.h"

typedef struct pipe{
	int		fd[2];
	int		infile_fd;
	int		outfile_fd;
	int		pid1;
	int		pid2;
	char	**temp2_matrix;
	char	**temp3_matrix;
	char	**argv2;
	char	**argv3;
	char	*temp2;
	char	*temp3;
	int		count;
}	t_pipex;

char	**moving_matrix(char **final_matrix, char **temp_matrix, char **envp);
int		main(int argc, char **argv, char **envp);
void	checking_argv(t_pipex *pipex, char **argv, char **envp);
int		sex(t_pipex *pipex);
void	cancel(t_pipex *pipex);
void	cleaner2(t_pipex *pipex);
void	cleaner1(char **matrix);
char	*remover(char *temp);
char	*remover(char *temp);
char	*ranger(char *temp, char **envp);
char	*ft_pathfinder(char *dst, char *src);
int		checazzoneso(char **temp_matrix);
void	cleaner(char **argv);
char	*finder(char *temp, char *path);
void	print_matrix(char **matrix);
void	free_tacos(char **tacos, int i);


#endif
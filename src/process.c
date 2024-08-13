/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:18:10 by aumartin          #+#    #+#             */
/*   Updated: 2024/08/13 10:57:59 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	init_processes(t_pipex *pipex, t_process *processes)
{
	int	pipe_fd[2 * (pipex->cmd_count - 1)];
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (pipe(pipe_fd + i * 2) == -1)
			error_exit("pipe");
		i++;
	}
	i = 0;
	while (i < pipex->cmd_count)
	{
		processes[i].command = ft_split(pipex->cmds[i], ' ');
		// Verif a supprimer
		if (processes[i].command == NULL)
		{
			perror("ft_split");
			exit(EXIT_FAILURE);
		}

		if (i == 0)
		{
			processes[i].input = pipex->infile;
			processes[i].output = pipe_fd[1];
		}
		else if (i == pipex->cmd_count - 1)
		{
			processes[i].input = pipe_fd[2 * (i - 1)];
			processes[i].output = pipex->outfile;
		}
		else
		{
			processes[i].input = pipe_fd[2 * (i - 1)];
			processes[i].output = pipe_fd[2 * i + 1];
		}
		i++;
	}
}

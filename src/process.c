/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:18:10 by aumartin          #+#    #+#             */
/*   Updated: 2024/10/21 16:31:18 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	init_processes(t_pipex *pipex, t_process *processes)
{
	int	*pipe_fd;
	int	i;

	pipe_fd = alloc_pipes(pipex->cmd_count);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (pipe(pipe_fd + i * 2) == -1)
			error_exit("pipe");
		i++;
	}
	assign_processes(pipex, processes, pipe_fd);
	free(pipe_fd);
}

void	assign_processes(t_pipex *pipex, t_process *processes, int *pipe_fd)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		processes[i].command = ft_split(pipex->cmds[i], ' ');
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

/* = tableau de long variable
int	pipe_fd[2 * (pipex->cmd_count - 1)]; */

int	*alloc_pipes(int cmd_count)
{
	int	*pipe_fd;

	pipe_fd = malloc(sizeof(int) * 2 * (cmd_count - 1));
	if (!pipe_fd)
		error_exit("malloc pipe_fd");
	return (pipe_fd);
}

void	free_processes(t_process *processes, int cmd_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd_count)
	{
		if (processes[i].command)
		{
			j = 0;
			while (processes[i].command[j] != NULL)
			{
				free(processes[i].command[j]);
				j++;
			}
			free(processes[i].command);
		}
		i++;
	}
}

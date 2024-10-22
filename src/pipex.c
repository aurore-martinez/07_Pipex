/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:14:46 by aumartin          #+#    #+#             */
/*   Updated: 2024/10/22 09:36:47 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	wait_processes(int cmd_count, pid_t pid)
{
	int	status;
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			error_exit("child process failed");
		i++;
	}
}

/* t_process	processes[pipex->cmd_count] */
void	execute_pipex(t_pipex *pipex)
{
	t_process	*processes;
	pid_t		pid;
	int			i;

	processes = malloc(sizeof(t_process) * pipex->cmd_count);
	if (!processes)
		error_exit("malloc processes");
	init_processes(pipex, processes);
	i = 0;
	while (i < pipex->cmd_count)
	{
		pid = fork();
		if (pid == -1)
			error_exit("fork");
		if (pid == 0)
			exec_command(&processes[i], pipex->envp);
		close(processes[i].input);
		close(processes[i].output);
		i++;
	}
	wait_processes(pipex->cmd_count, pid);
	free_processes(processes, pipex->cmd_count);
	free(processes);
}
/*
utilise unlink, wait, et waitpid pour une gestion complète
des fichiers temporaires et des processus fils.
wait vs waitpid, on peut utiliser wait de manière similaire,
mais waitpid offre plus de contrôle (comme attendre
un processus spécifique ou vérifier des conditions particulières).
*/

void	here_doc(t_pipex *pipex, char *limiter)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd) == -1)
		error_exit("pipe");
	pid = fork();
	if (pid == -1)
		error_exit("fork");
	if (pid == 0)
	{
		close(pipe_fd[0]);
		write_here_doc(pipe_fd[1], limiter);
		exit(EXIT_SUCCESS);
	}
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		error_exit("child process failed");
	pipex->infile = pipe_fd[0];
	execute_pipex(pipex);
	close(pipe_fd[0]);
}

void	write_here_doc(int fd, char *limiter)
{
	char	*line;

	line = NULL;
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			error_exit("get_next_line");
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
}

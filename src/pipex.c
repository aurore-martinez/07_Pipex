/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:14:46 by aumartin          #+#    #+#             */
/*   Updated: 2024/09/11 12:04:25 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute_pipex(t_pipex *pipex)
{
	t_process	processes[pipex->cmd_count];
	pid_t		pid;
	int			status;
	int			i;

	init_processes(pipex, processes);
	i = 0;
	while (i < pipex->cmd_count)
	{
		pid = fork();
		if (pid == -1)
			error_exit("fork");
		if (pid == 0)
			exec_command(&processes[i], pipex->envp);
		// Parent
		close(processes[i].input);
		close(processes[i].output);
		i++;
	}
	// Parent process waitpid TOUS children aient fini
	i = 0;
	while (i < pipex->cmd_count)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			error_exit("child process failed");
		i++;
	}
}

// utilise unlink, wait, et waitpid pour une gestion complète des fichiers temporaires et des processus fils.
// wait vs waitpid, on peut utiliser wait de manière similaire, mais waitpid offre plus de contrôle (comme attendre un processus spécifique ou vérifier des conditions particulières).

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
		char	*line = NULL;

		while (1)
		{
			write(1, "> ", 2);
			line = get_next_line(STDIN_FILENO);
			if (!line)
				error_exit("get_next_line");
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n')
			{
				free(line);
				break ;
			}
			write(pipe_fd[1], line, ft_strlen(line));
			free(line);
		}
		close(pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			error_exit("child process failed");

		close(pipe_fd[1]);
		pipex->infile = pipe_fd[0];
		// Debugging message
		ft_printf("Infile descriptor: %d\n", pipex->infile);
		execute_pipex(pipex);
		close(pipe_fd[0]);
	}
}


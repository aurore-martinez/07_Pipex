/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:20:33 by aumartin          #+#    #+#             */
/*   Updated: 2024/10/21 16:39:51 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/gnl/get_next_line_bonus.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_process
{
	int		input;
	int		output;
	char	**command;
}	t_process;

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**cmds;
	int		cmd_count;
	char	**envp;
}	t_pipex;

/* Prototypes fonctions main */
void	handle_here_doc(int ac, char **av, t_pipex *pipex);

/* Prototypes fonctions pipex */
void	wait_processes(int cmd_count, pid_t pid);
void	execute_pipex(t_pipex *pipex);
void	here_doc(t_pipex *pipex, char *limiter);
void	write_here_doc(int fd, char *limiter);

/* Prototypes fonctions process */
void	init_processes(t_pipex *pipex, t_process *processes);
void	assign_processes(t_pipex *pipex, t_process *processes, int *pipe_fd);
int		*alloc_pipes(int cmd_count);
void	free_processes(t_process *processes, int cmd_count);

/* Prototypes fonctions error_management */
void	error_exit(const char *message);
void	handle_exec_errors(int error_code, const char *command);

/* Prototypes fonctions utils */
void	exec_command(t_process *process, char **envp);
char	*get_path_from_env(char **envp);
char	**split_path(char *path);
char	*find_command_path(char *command, char **envp);

#endif

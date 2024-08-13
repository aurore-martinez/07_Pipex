/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:20:33 by aumartin          #+#    #+#             */
/*   Updated: 2024/08/13 11:06:15 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
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

void	execute_pipex(t_pipex *pipex);
void	here_doc(t_pipex *pipex, char *limiter);
void	init_processes(t_pipex *pipex, t_process *processes);
void	error_exit(const char *message);
void	exec_command(t_process *process, char **envp);

char	*get_path_from_env(char **envp);
char	**split_path(char *path);
char	*find_command_path(char *command, char **envp);

#endif

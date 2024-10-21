/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:14:41 by aumartin          #+#    #+#             */
/*   Updated: 2024/10/21 12:11:02 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac < 5)
	{
		ft_printf("Erreur args < 4, file1 cmd1 cmd2 [cmd3 ...] file2\n");
		return (EXIT_FAILURE);
	}
	pipex.envp = envp;
	if (ft_strncmp(av[1], "here_doc", 8) == 0 && av[1][8] == '\0')
		handle_here_doc(ac, av, &pipex);
	else
	{
		pipex.infile = open(av[1], O_RDONLY);
		if (pipex.infile < 0)
			error_exit("open infile");
		pipex.outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex.outfile < 0)
			error_exit("open outfile");
		pipex.cmd_count = ac - 3;
		pipex.cmds = &av[2];
		execute_pipex(&pipex);
	}
	return (EXIT_SUCCESS);
}

void	handle_here_doc(int ac, char **av, t_pipex *pipex)
{
	if (ac < 6)
	{
		ft_printf("Erreur args < 6, here_doc LIMITER cmd cmd1[...] file\n");
		exit(EXIT_FAILURE);
	}
	pipex->cmd_count = ac - 4;
	pipex->cmds = &av[3];
	pipex->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	here_doc(pipex, av[2]);
}

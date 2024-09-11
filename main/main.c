/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:14:41 by aumartin          #+#    #+#             */
/*   Updated: 2024/09/11 12:08:01 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
	{
		ft_printf("Erreur arguments < 4, Usage: %s file1 cmd1 cmd2 [cmd3 ... cmdN] file2\n", argv[0]);
		return (EXIT_FAILURE);
	}

	pipex.envp = envp;

	/* if (strcmp(argv[1], "here_doc") == 0) */
	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && argv[1][8] == '\0')
	{
		if (argc < 6)
		{
			ft_printf("Erreur arguments < 6,  Usage: %s here_doc LIMITER cmd cmd1 [cmd2 ... cmdN] file\n", argv[0]);
			return (EXIT_FAILURE);
		}
		pipex.cmd_count = argc - 4;
		pipex.cmds = &argv[3];
		pipex.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		here_doc(&pipex, argv[2]);
	}
	else
	{
		pipex.infile = open(argv[1], O_RDONLY);
		if (pipex.infile < 0)
			error_exit("open infile");
		pipex.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex.outfile < 0)
			error_exit("open outfile");
		pipex.cmd_count = argc - 3;
		pipex.cmds = &argv[2];
		execute_pipex(&pipex);
	}
	return (EXIT_SUCCESS);
}

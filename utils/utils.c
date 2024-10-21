/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:18:24 by aumartin          #+#    #+#             */
/*   Updated: 2024/10/21 17:46:25 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
// Printf la commande et ses args
	ft_printf("Executing command: %s\n", process->command[0]);

	for (int i = 1; process->command[i]; i++)
	ft_printf("Argument %d: %s\n", i, process->command[i]);

// Vérifie si le fichier de commande est exécutable
	if (access(process->command[0], X_OK) != 0)
	{
		perror("access");
		exit(EXIT_FAILURE);
	}
*/

void	exec_command(t_process *process, char **envp)
{
	char	*command_path;

	command_path = find_command_path(process->command[0], envp);
	if (command_path == NULL)
		handle_exec_errors(ENOENT, process->command[0]);
	if (dup2(process->input, STDIN_FILENO) == -1
		|| dup2(process->output, STDOUT_FILENO) == -1)
	{
		ft_printf("%s\n", command_path);
		perror("dup2");
		free(command_path);
		exit(EXIT_FAILURE);
	}
	close(process->input);
	close(process->output);
	if (execve(command_path, process->command, envp) == -1)
	{
		handle_exec_errors(errno, process->command[0]);
		perror("execve");
		free(command_path);
		exit(EXIT_FAILURE);
	}
	free(command_path);
}

/* trouve PATH dans envp puis divise avec split et ignore "PATH=" */
char	*get_path_from_env(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (path);
}

char	**split_path(char *path)
{
	return (ft_split(path, ':'));
	ft_printf(" fonction split_path, path: %s\n", path);
}

char	*find_command_path(char *command, char **envp)
{
	char	*path_env;
	char	**paths;
	char	full_path[1024];
	int		i;

	path_env = get_path_from_env(envp);
	if (path_env == NULL)
		return (NULL);
	paths = split_path(path_env);
	if (paths == NULL)
		return (perror("split_path"), NULL);
	i = 0;
	while (paths[i])
	{
		ft_strlcpy(full_path, paths[i], sizeof(full_path));
		ft_strlcat(full_path, "/", sizeof(full_path));
		ft_strlcat(full_path, command, sizeof(full_path));
		if (access(full_path, X_OK) == 0)
			return (ft_strdup(full_path));
		i++;
	}
	free(paths);
	return (NULL);
}

/* fonction pour comprendre la mecanisme

 char	*find_command_path(char *command)
{
	char	*path_env = getenv("PATH");
	char	*path;
	char	full_path[1024];
	char	*path_copy;
	if (path_env == NULL)
		return (NULL);
	path_copy = strdup(path_env); // Crée une copie de PATH pour strtok
	if (path_copy == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	path = strtok(path_copy, ":");
	while (path != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", path, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return strdup(full_path);  // Retourne une copie du chemin complet
		}
		path = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);  // Retourne NULL si la commande n'a pas été trouvée
} */

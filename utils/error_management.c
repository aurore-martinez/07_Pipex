/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:33:46 by aumartin          #+#    #+#             */
/*   Updated: 2024/10/21 11:42:23 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error_exit(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	handle_exec_errors(int error_code, const char *command)
{
	if (error_code == ENOENT)
		ft_printf("Commande introuvable: %s\n", command);
	else if (error_code == EACCES)
		ft_printf("Permission refusée pour: %s\n", command);
	else if (error_code == EISDIR)
		ft_printf("%s est un répertoire, impossible de l'exécuter.\n", command);
	else if (error_code == EBADF)
		ft_printf("Mauvais descripteur de fichier pour: %s\n", command);
	else if (error_code == EIO)
		ft_printf("Erreur d'entrée/sortie pour: %s\n", command);
	else
		ft_printf("Erreur inconnue pour: %s\n", command);
	exit(EXIT_FAILURE);
}

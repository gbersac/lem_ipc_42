/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/09 19:09:58 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/21 14:04:19 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

void		sig_handler(int sig)
{
	exit_shmem();
	if (sig != -1)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}

int			main_init(int argc, char **argv)
{
	semaph_wait_lock(semaph_init());
	if (get_shmem() == NULL)
		return (-1);
	if (get_shmem()->nb_user > MAX_PLAYER)
	{
		printf("There is already enough player.\n");
		return (-1);
	}
	printf("\nNb user on this mem %zu\n", get_shmem()->nb_user);
	if (create_player(argc, argv) == -1)
		return (-1);
	semaph_unlock(get_shmem()->semaph_id);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTERM, sig_handler);
	return (0);
}

int			main(int argc, char **argv)
{
	if (main_init(argc, argv) == -1)
		sig_handler(-1);
	while (42)
	{
		play_turn();
	}
	exit_shmem();
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/09 19:09:58 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/28 15:12:22 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

void		sig_handler(int sig)
{
	exit_shmem();
	if (sig != -1)
	{
		// test_victory();
		exit(EXIT_SUCCESS);
	}
	else
		exit(EXIT_FAILURE);
}

int			main_init(int argc, char **argv)
{
	int		semid;

	semid = get_semaph();
	semaph_wait_lock(semid);
	if (get_shmem() == NULL || get_semaph() == 0)
		return (-1);
	if (get_shmem()->nb_user > MAX_PLAYER)
	{
		printf("There is already enough player.\n");
		return (-1);
	}
	printf("Nb user on this mem %zu\n", get_shmem()->nb_user);
	if (create_player(argc, argv) == -1)
		return (-1);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTERM, sig_handler);
	semaph_unlock(semid);
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

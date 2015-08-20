/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/09 19:09:58 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/20 15:39:27 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

void		sig_handler(int sig)
{
	exit_shmem();
	exit(EXIT_SUCCESS);
	sig = 0;
}

int			main()
{
	t_shmem	*mem;

	mem = get_shmem();
	if (mem == NULL)
		return (EXIT_FAILURE);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTERM, sig_handler);
	printf("Nb user on this mem %zu\n", mem->nb_user);

	// while (42)
	// {
	// 	semaph_wait_lock(mem->semaph_id);
	// 	printf("semaphor lock %d\n", getpid());
	// 	sleep(1);
	// 	semaph_unlock(mem->semaph_id);
	// 	printf("semaphor unlock %d\n\n", getpid());
	// }


	semaph_wait_lock(mem->semaph_id);
	printf("semaphor lock %d\n", getpid());
	while (42)
	{}

	exit_shmem();
	return (EXIT_SUCCESS);
}

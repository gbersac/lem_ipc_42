/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shmem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/19 19:32:21 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/20 15:44:20 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

void	exit_shmem(void)
{
	t_shmem	*mem;
	int		shmid;
	t_semun	arg;

	mem = get_shmem();
	shmid = get_shmemid();
	if (mem->nb_user <= 1)
	{
		if (semctl(mem->semaph_id, 0, IPC_RMID, arg) == -1)
			ft_putstr("error deleting the semaphore");
		shmctl(get_shmemid(NULL), IPC_RMID, NULL);
		ft_putstr("Delete shared memory");
	}
	else
	{
		--mem->nb_user;
		printf("semaphore unlock %d\n", getpid());
		printf("Remaing %zu users\n", mem->nb_user);
		shmdt(mem);
	}
}


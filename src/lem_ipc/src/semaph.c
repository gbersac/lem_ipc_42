/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaph.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/20 12:38:04 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/21 14:02:55 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static void	init_sembuf(t_sembuf *sembuf, short sem_op, short sem_flg)
{
	sembuf->sem_num = 0;
	sembuf->sem_op = sem_op;
	sembuf->sem_flg = sem_flg;
}

int			semaph_init(void)
{
	int		semid;
	key_t	key;

	key = SHMEM_KEY;
	semid = semget(key, 1, IPC_CREAT | IPC_EXCL | SHMEM_RIGHT);
	if (semid >= 0)
	{
		puts("Create new semaphore.");
		semaph_unlock(semid);
	}
	else if (errno == EEXIST)
		semid = semget(key, 1, 0);
	if (semid == -1)
	{
		puts("Error creating semaphore.");
		return (-1);
	}
	return(semid);
}

int		semaph_wait_lock(int semid)
{
	t_sembuf	sembuf;

	init_sembuf(&sembuf, -1, SEM_UNDO);
	if (semop(semid, &sembuf, 1) == -1)
	{
		printf("error while trying to lock the semaphore %d\n", semid);
		return (-1);
	}
	// printf("semaphore lock %d\n", getpid());
	return (0);
}

int			semaph_unlock(int semid)
{
	t_sembuf	sembuf;

	init_sembuf(&sembuf, 1, 0);
	if (semop(semid, &sembuf, 1) == -1)
	{
		printf("error while trying to unlock the semaphore %d\n", semid);
		return (-1);
	}
	// printf("semaphore unlock %d\n", getpid());
	usleep(10);
	return (0);
}

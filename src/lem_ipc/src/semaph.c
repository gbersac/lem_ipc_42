/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaph.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/20 12:38:04 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/24 16:37:35 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static void	init_sembuf(t_sembuf *sembuf, short sem_op, short sem_flg)
{
	sembuf->sem_num = 0;
	sembuf->sem_op = sem_op;
	sembuf->sem_flg = sem_flg;
}

int			semaph_wait_lock(void)
{
	t_sembuf	sembuf;

	init_sembuf(&sembuf, -1, SEM_UNDO);
	if (semop(get_semaph(), &sembuf, 1) == -1)
	{
		printf("error while trying to lock the semaphore %d\n", get_semaph());
		return (-1);
	}
	// printf("semaphore lock %d\n", getpid());
	return (0);
}

int			semaph_unlock(void)
{
	t_sembuf	sembuf;

	init_sembuf(&sembuf, 1, 0);
	if (semop(get_semaph(), &sembuf, 1) == -1)
	{
		printf("error while trying to unlock the semaphore %d\n", get_semaph());
		return (-1);
	}
	// printf("semaphore unlock %d\n", getpid());
	usleep(10);
	return (0);
}

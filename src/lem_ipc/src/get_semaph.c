/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_semaph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/24 15:51:26 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/24 16:09:15 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static int	init_semaph(void)
{
	key_t	key;
	int		semid = -1;

	key = SHMEM_KEY;
	semid = semget(key, 1, IPC_CREAT | IPC_EXCL | SHMEM_RIGHT);
	if (semid >= 0)
	{
		puts("Create new semaphore.");
		semaph_unlock(semid);
	}
	else if (errno == EEXIST)
		semid = semget(key, 1, SHMEM_RIGHT);
	if (semid == -1)
	{
		puts("Error creating semaphore.");
		return (-1);
	}
	return(semid);
}

int			get_semaph(void)
{
	static int	semid = -1;

	if (semid == -1)
		semid = init_semaph();
	return (semid);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/19 19:22:07 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/24 18:43:51 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static void		init_shmem(t_shmem *mem)
{
	mem->semaph_id = get_semaph();
	ft_bzero(mem, sizeof(t_shmem));
	memset(mem->map.tiles, -1, sizeof(t_tile) * MAP_SIZE * MAP_SIZE);
}

static t_shmem	*create_shmem()
{
	key_t	key;
	t_shmem	*to_return;
	int		shmid;

	key = SHMEM_KEY;
	shmid = shmget(key, sizeof(t_shmem), SHMEM_RIGHT);
	if (shmid > 0)
		to_return = shmat(shmid, (void *)0, 0);
	else
	{
		puts("Create new memory");
		shmid = shmget(key, sizeof(t_shmem), SHMEM_RIGHT | IPC_CREAT | IPC_EXCL);
		to_return = shmat(shmid, (void *)0, 0);
		init_shmem(to_return);
	}
	if (shmid == -1 || to_return == (t_shmem *)(-1))
	{
		puts("Error: can't open the shared memory.");
		return (NULL);
	}
	get_shmid(&shmid);
	++to_return->nb_user;
	return(to_return);
}

int				get_shmid(int *value)
{
	static int	to_return = -1;

	if (to_return == -1)
		to_return = *value;
	return(to_return);
}

t_shmem			*get_shmem()
{
	static t_shmem	*to_return = NULL;

	if (to_return == NULL)
		to_return = create_shmem();
	return (to_return);
}

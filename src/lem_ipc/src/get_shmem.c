/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/19 19:22:07 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/20 20:44:11 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static void		init_shmem(t_shmem *mem)
{
	ft_bzero(mem, sizeof(t_shmem));
	mem->semaph_id = semaph_init();
	mem->players = NULL;
}

static t_shmem	*create_shmem()
{
	key_t	key;
	t_shmem	*to_return;
	int		shmid;

	key = SHMEM_KEY;
	shmid = shmget(key, sizeof(t_shmem), SHMEM_RIGHT);
	if (shmid == -1)
	{
		puts("Create new memory\n");
		shmid = shmget(key, sizeof(t_shmem), SHMEM_RIGHT | IPC_CREAT);
		to_return = shmat(shmid, NULL, 0);
		init_shmem(to_return);
	}
	else
		to_return = shmat(shmid, NULL, 0);
	if (shmid == -1 || to_return == (t_shmem *)(-1))
	{
		ft_putstr("Error: can't open the shared memory.");
		return (NULL);
	}
	get_shmemid(&shmid);
	++to_return->nb_user;
	return(to_return);
}

int				get_shmemid(int *value)
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

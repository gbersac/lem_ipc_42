/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shmem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/19 19:32:21 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/25 16:22:32 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static void	shift_players(void)
{
	size_t	i;

	i = get_proc_player_id(NULL);
	while (i < get_shmem()->nb_user - 1)
	{
		memcpy(&get_shmem()->players[i], &get_shmem()->players[i + 1],
				sizeof(t_player));
		set_map_tile(get_shmem()->players[i].x, get_shmem()->players[i].y,
				&get_shmem()->players[i]);
		++i;
	}
	bzero(&get_shmem()->players[i], sizeof(t_player));
}

static void	test_proc_is_locking_semaph()
{
	printf("semaph_locker %d getpid %d\n",
			get_shmem()->semaph_locker, getpid());
	if (get_shmem()->semaph_locker == getpid())
		semaph_unlock();
}

void		exit_shmem(void)
{
	t_shmem	*mem;
	int		shmid;
	t_semun	arg;

	mem = get_shmem();
	shmid = get_shmid();
	get_proc_player()->is_active = 0;
	set_map_tile(get_proc_player()->x, get_proc_player()->y, NULL);
	shift_players();
	if (mem->nb_user <= 1)
	{
		if (semctl(mem->semaph_id, 0, IPC_RMID, arg) == -1)
			ft_putendl("error deleting the semaphore");
		shmctl(get_shmid(NULL), IPC_RMID, NULL);
		ft_putendl("Delete shared memory");
	}
	else
	{
		test_proc_is_locking_semaph();
		--mem->nb_user;
		printf("%d quit, remaing %zu users\n", getpid(), mem->nb_user);
		shmdt(mem);
	}
}

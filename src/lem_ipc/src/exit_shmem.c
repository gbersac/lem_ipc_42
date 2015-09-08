/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shmem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/19 19:32:21 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/28 17:31:16 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static void	shift_players(void)
{
	size_t	i;

	i = get_proc_player_id();
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

static void	test_proc_is_locking_semaph(void)
{
	if (get_shmem()->semaph_locker == getpid())
		semaph_unlock();
}

void		del_shmem(void)
{
	t_shmem	*mem;
	t_semun	arg;

	mem = get_shmem();
	semctl(get_semaph(), 0, IPC_RMID, arg);
	shmctl(get_shmid(NULL), IPC_RMID, NULL);
	remove_queue();
	ft_putendl("Delete shared memory");
}

void		exit_shmem(void)
{
	t_shmem	*mem;
	int		shmid;

	set_map_tile(get_proc_player()->x, get_proc_player()->y, NULL);
	mem = get_shmem();
	shmid = get_shmid();
	get_proc_player()->is_active = 0;
	shift_players();
	if (mem->nb_user <= 1)
		del_shmem();
	else
	{
		--mem->nb_user;
		printf("%d quit, remaing %zu users\n", getpid(), mem->nb_user);
		test_proc_is_locking_semaph();
		shmdt(mem);
	}
}

void		kill_all(void)
{
	t_player	*p;
	int			i;

	i = 0;
	while (i < MAX_PLAYER)
	{
		p = get_player(i);
		if (p->pid != getpid() && p->pid != 0)
			kill(p->pid, 9);
		++i;
	}
	get_shmem()->nb_user = 1;
	del_shmem();
	exit(EXIT_SUCCESS);
}

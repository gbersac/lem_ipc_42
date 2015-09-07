/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_turn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/20 17:42:04 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/28 17:30:10 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static void	increment_player(t_shmem *mem)
{
	++mem->current_player;
	if (mem->current_player >= mem->nb_user)
		mem->current_player = 0;
}

void		next_player(t_shmem *mem)
{
	increment_player(mem);
	while (!get_current_player()->is_active)
		increment_player(mem);
}

void		print_players_position(t_shmem *mem)
{
	size_t		i;
	t_player	*ps;

	i = 0;
	while (i < mem->nb_user)
	{
		ps = get_player(i);
		printf("pid %d team %d x %d y %d is_active %d\n",
				ps->pid, ps->team, ps->x, ps->y, ps->is_active);
		++i;
	}
}

static void	player_actions(t_shmem *mem, t_player *player)
{
	t_player	*target;

	++mem->nb_turn;
	if (!test_player_is_alive(player))
		return ;
	target = designate_target();
	if (target == NULL)
		return ;
	move_player(player, target);
	printf("play_turn player pid %d team %d target %d nb_turn %d\n",
			getpid(), player->team, target->pid, mem->nb_turn);
	print_map();
	player = NULL;
}

int			play_turn(void)
{
	t_shmem		*mem;
	t_player	*player;

	mem = get_shmem();
	player = get_current_player();
	semaph_wait_lock();
	if (player->pid == getpid())
	{
		printf("###new turn %d -> %d\n", getpid(),
				get_player(get_proc_player_id(NULL))->pid);
		player_actions(mem, player);
		sleep(2);
		next_player(mem);
	}
	semaph_unlock();
	return (0);
}

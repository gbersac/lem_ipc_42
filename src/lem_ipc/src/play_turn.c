/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_turn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/20 17:42:04 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/24 22:38:13 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static void	increment_player(t_shmem *mem)
{
	++mem->current_player;
	if (mem->current_player >= mem->nb_user)
		mem->current_player = 0;
	printf("increment_player %zu nb_user %zu\n", mem->current_player,
			mem->nb_user);
}

static void	next_player(t_shmem *mem)
{
	increment_player(mem);
	while (get_current_player()->is_active == 0)
		increment_player(mem);
	printf("new current_player %d\n", get_current_player()->pid);
	printf("player0 %d is_active %d\n", get_player(0)->pid, get_player(0)->is_active);
	printf("player1 %d is_active %d\n", get_player(1)->pid, get_player(1)->is_active);
	printf("player2 %d is_active %d\n", get_player(2)->pid, get_player(2)->is_active);
}

static void	player_actions(t_shmem *mem, t_player *player)
{
	++mem->nb_turn;
	player = NULL;
	printf("play_turn player pid %d nb_turn %d\n", getpid(), mem->nb_turn);
	print_map();
}

int			play_turn()
{
	t_shmem		*mem;
	t_player	*player;

	mem = get_shmem();
	player = get_current_player();
	semaph_wait_lock();
	if (player->pid == getpid())
	{
		player_actions(mem, player);
		next_player(mem);
		sleep(2);
	}
	semaph_unlock();
	return(0);
}

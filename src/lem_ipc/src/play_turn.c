/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_turn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/20 17:42:04 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/25 21:50:28 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static void	increment_player(t_shmem *mem)
{
	++mem->current_player;
	if (mem->current_player >= mem->nb_user)
		mem->current_player = 0;
}

static void	next_player(t_shmem *mem)
{
	increment_player(mem);
	while (!get_current_player()->is_active)
		increment_player(mem);
}

static void	player_actions(t_shmem *mem, t_player *player)
{
	t_player	*target;

	++mem->nb_turn;
	target = designate_target();
	printf("player_actions\n");
	if (target == NULL)
		return ;
	// read_message(&msgbf);
	// printf("team %d target %d\n", msgbf.team, msgbf.target);
	// send_message(get_current_player()->team, get_shmem()->nb_turn);
	printf("play_turn player pid %d team %d target %d nb_turn %d\n",
			getpid(), player->team, target->pid, mem->nb_turn);
	print_map();
	player = NULL;
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
		// check_is_alive();
		player_actions(mem, player);
		sleep(2);
		next_player(mem);
	}
	semaph_unlock();
	return(0);
}

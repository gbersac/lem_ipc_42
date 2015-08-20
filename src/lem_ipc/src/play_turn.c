/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_turn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/20 17:42:04 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/20 23:04:37 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static void	next_player(t_shmem *mem)
{
	++mem->current_player;
	if (mem->current_player >= mem->nb_user)
		mem->current_player = 0;

}

static void	player_actions(t_shmem *mem, t_player *player)
{
	printf("player pid %d\n", getpid());
	mem = NULL;
	player = NULL;
}

int			play_turn()
{
	t_shmem		*mem;
	t_player	*player;

	mem = get_shmem();
	player = get_current_player();
	semaph_wait_lock(mem->semaph_id);
	if (player->pid == getpid())
	{
		player_actions(mem, player);
		next_player(mem);
	}
	sleep(2);
	semaph_unlock(mem->semaph_id);
	return(0);
}

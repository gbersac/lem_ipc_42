/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/24 19:10:55 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/25 20:51:30 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

int			get_proc_player_id(int *player_id)
{
	static int	to_return = 0;

	if (player_id != NULL)
		to_return = *player_id;
	return(to_return);
}

t_player	*get_proc_player()
{
	t_player	*to_return;

	to_return = &get_shmem()->players[get_proc_player_id(NULL)];
	return(to_return);
}

t_player	*get_player(int idx)
{
	t_player	*to_return;

	if (idx < 0 || idx > MAX_PLAYER)
		return (NULL);
	to_return = &get_shmem()->players[idx];
	return (to_return);
}

int			get_player_id(t_player *p)
{
	int	to_return;

	to_return = p - get_shmem()->players;
	return(to_return);
}

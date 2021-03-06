/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 15:39:07 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/28 17:05:10 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static int		change_tile(t_player *player, int x, int y)
{
	int		old_x;
	int		old_y;

	if (get_map_tile(x, y) != NULL)
		return (0);
	old_x = player->x;
	old_y = player->y;
	if (!set_map_tile(x, y, player))
		return (0);
	set_map_tile(old_x, old_y, NULL);
	return (1);
}

static void		move_direction(t_player *player, int x, int y, int other_dir)
{
	int		other_dir_one;
	int		ret;

	if (change_tile(player, player->x + x, player->y + y))
		return ;
	if (other_dir == 0)
		other_dir = 1;
	other_dir_one = other_dir / abs(other_dir);
	if (x != 0)
		ret = change_tile(player, player->x, player->y + other_dir_one);
	else
		ret = change_tile(player, player->x + other_dir_one, player->y);
	if (ret)
		return ;
	if (x != 0)
		ret = change_tile(player, player->x, player->y - other_dir_one);
	else
		ret = change_tile(player, player->x - other_dir_one, player->y);
}

void			move_player(t_player *player, t_player *target)
{
	int		dist_x;
	int		dist_y;

	dist_x = player->x - target->x;
	dist_y = player->y - target->y;
	if (abs(dist_x) > abs(dist_y))
	{
		if (dist_x > 0)
			move_direction(player, -1, 0, dist_y);
		else
			move_direction(player, +1, 0, dist_y);
	}
	else
	{
		if (dist_y > 0)
			move_direction(player, 0, -1, dist_x);
		else
			move_direction(player, 0, +1, dist_x);
	}
}

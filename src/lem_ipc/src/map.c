/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/21 12:24:29 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/26 18:59:14 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

t_player	*get_map_tile(int x, int y)
{
	int		player_idx;

	if (x < 0 || y < 0 || x >= MAP_SIZE || y >= MAP_SIZE)
		return (NULL);
	player_idx = get_shmem()->map.tiles[x * MAP_SIZE + y];
	if (player_idx == -1)
		return (NULL);
	else
		return (&get_shmem()->players[player_idx]);
}

void		print_map(void)
{
	int			x;
	int			y;
	t_player	*t;

	x = 0;
	while (x < MAP_SIZE)
	{
		y = 0;
		while (y < MAP_SIZE)
		{
			t = get_map_tile(y, x);
			if (t == NULL)
				printf(". ");
			else
				printf("%d ", t->team);
			++y;
		}
		puts("");
		++x;
	}
}

void		set_map_tile(int x, int y, t_player *p)
{
	int		player_idx;

	if (x < 0 || y < 0 || x >= MAP_SIZE || y >= MAP_SIZE)
		return ;
	if (p != NULL)
		player_idx = p - get_shmem()->players;
	else
		player_idx = -1;
	get_shmem()->map.tiles[x * MAP_SIZE + y] = player_idx;
	if (p != NULL)
	{
		p->x = x;
		p->y = y;
	}
	// printf("set_map_tile[%d, %d] %p -> %p\n", x, y, p, *get_map_tile(x, y));
}

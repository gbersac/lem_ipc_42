/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/21 12:24:29 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/24 18:52:47 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

t_player	*get_map_tile(int x, int y)
{
	int		player_idx;

	player_idx = get_shmem()->map.tiles[x * MAP_SIZE + y];
	if (player_idx == -1)
		return (NULL);
	else
		return (&get_shmem()->players[player_idx]);
}

void	print_map(void)
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
			t = get_map_tile(x, y);
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

void	set_map_tile(int x, int y, t_player *p)
{
	int		player_idx;

	player_idx = p - get_shmem()->players;
	get_shmem()->map.tiles[x * MAP_SIZE + y] = player_idx;
	// printf("set_map_tile[%d, %d] %p -> %p\n", x, y, p, *get_map_tile(x, y));
}

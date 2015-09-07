/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/21 12:24:29 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/28 17:03:40 by gbersac          ###   ########.fr       */
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

int			nb_user_set_on_map(void)
{
	int		in_player;
	int		i;

	i = 0;
	in_player = 0;
	while (i < MAP_SIZE * MAP_SIZE)
	{
		if (get_shmem()->map.tiles[i] != -1)
			++in_player;
		++i;
	}
	return (in_player);
}

void		print_map(void)
{
	int			x;
	int			y;
	t_player	*t;

	x = 0;
	printf("nb_user_set_on_map %d\n", nb_user_set_on_map());
	while (x < MAP_SIZE)
	{
		y = 0;
		while (y < MAP_SIZE)
		{
			t = get_map_tile(y, x);
			if (t == NULL || !t->is_active)
				printf(". ");
			else
			{
				printf("%d ", t->team);
			}
			++y;
		}
		puts("");
		++x;
	}
}

int			set_map_tile(int x, int y, t_player *p)
{
	int		player_idx;

	if (x < 0 || y < 0 || x >= MAP_SIZE || y >= MAP_SIZE)
	{
		return (0);
	}
	if (p != NULL)
		player_idx = p - get_shmem()->players;
	else
		player_idx = -1;
	get_shmem()->map.tiles[x * MAP_SIZE + y] = player_idx;
	if (p != NULL)
	{
		p->x = x;
		p->y = y;
		return (1);
	}
	return (0);
}

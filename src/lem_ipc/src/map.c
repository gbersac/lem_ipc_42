/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/21 12:24:29 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/24 16:29:30 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

t_tile	*get_map_tile(int x, int y)
{
	t_tile	*to_return;

	to_return = &get_shmem()->map.tiles[x * MAP_SIZE + y];
	return (to_return);
}

void	print_map(void)
{
	int		x;
	int		y;
	t_tile	*t;

	x = 0;
	while (x < MAP_SIZE)
	{
		y = 0;
		while (y < MAP_SIZE)
		{
			t = get_map_tile(x, y);
			if (*t == NULL)
				printf(". ");
			else
				printf("%d ", (*t)->team);
			++y;
		}
		puts("");
		++x;
	}
}

void	set_map_tile(int x, int y, t_player *p)
{
	get_shmem()->map.tiles[x * MAP_SIZE + y] = p;
	// printf("set_map_tile[%d, %d] %p -> %p\n", x, y, p, *get_map_tile(x, y));
}
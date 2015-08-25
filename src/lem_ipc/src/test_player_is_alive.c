/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_player_is_alive.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 22:01:24 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/25 22:12:37 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static int		test_one_tile(t_player *p, int x, int y, int *teams)
{
	t_player	*tile;

	tile = get_map_tile(x, y);
	if (tile == NULL)
		return (0);
	if (tile->team == p->team)
		return (0);
	teams[tile->team - 1] += 1;
	return (1);
}

static int		test_teams(int *teams)
{
	int		i;

	i = 0;
	while (i < MAX_TEAM)
	{
		if (teams[i] >= 2)
			return (1);
		++i;
	}
	return (0);
}

int				test_player_is_alive(t_player *p)
{
	int		teams[MAX_TEAM];

	if (!p->is_active)
		return (0);
	test_one_tile(p, p->x + 1, p->y, teams);
	test_one_tile(p, p->x , p->y + 1, teams);
	test_one_tile(p, p->x - 1, p->y, teams);
	test_one_tile(p, p->x, p->y - 1, teams);
	if (test_teams(teams))
		return (0);
	return (1);
}

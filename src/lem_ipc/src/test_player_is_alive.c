/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_player_is_alive.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 22:01:24 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/28 17:16:33 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static int		test_one_tile(t_player *p, int x, int y, int *teams)
{
	t_player	*tile;

	// printf("test_one_tile begin x %d y %d\n", x, y);
	tile = get_map_tile(x, y);
	if (tile == NULL || !tile->is_active)
		return (0);
	if (tile->team == p->team)
		return (0);
	// printf("++team %d x %d y %d\n", tile->team, x, y);
	teams[tile->team - 1] += 1;
	return (1);
}

static int		test_teams(int *teams)
{
	int		i;

	i = 0;
	while (i < MAX_TEAM)
	{
		// if (i == 0 || i == 1)
		// 	printf("teams %d -> %d\n", i + 1, teams[i]);
		if (teams[i] >= 2)
			return (1);
		++i;
	}
	return (0);
}

int				test_player_is_alive(t_player *p)
{
	int		teams[MAX_TEAM];

	bzero(teams, MAX_TEAM * sizeof(int));
	if (!p->is_active)
		return (0);
	test_one_tile(p, p->x + 1, p->y, teams);
	test_one_tile(p, p->x, p->y + 1, teams);
	test_one_tile(p, p->x - 1, p->y, teams);
	test_one_tile(p, p->x, p->y - 1, teams);
	test_one_tile(p, p->x + 1, p->y + 1, teams);
	test_one_tile(p, p->x + 1, p->y - 1, teams);
	test_one_tile(p, p->x - 1, p->y + 1, teams);
	test_one_tile(p, p->x - 1, p->y - 1, teams);
	if (test_teams(teams))
	{
		printf("!!!player %d x %d y %d team %d is dead\n",
			getpid(), p->x, p->y, p->team);
		p->is_active = 0;
		if (test_victory())
			kill_all();
		next_player(get_shmem());
		sig_handler(0);
		return (0);
	}
	return (1);
}

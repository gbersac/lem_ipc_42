/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/27 20:41:13 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/28 16:04:23 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static int		usage(void)
{
	printf("Usage: ./lem_ipc team. Team must be between 1 and %d\n", MAX_TEAM);
	return (-1);
}

static void		set_player_position(t_player *p)
{
	int		i;
	int		x;
	int		y;

	srand(time(NULL));
	i = rand() % MAP_SIZE * MAP_SIZE;
	while (i < MAP_SIZE * MAP_SIZE)
	{
		x = i % MAP_SIZE;
		y = i / MAP_SIZE;
		if (get_map_tile(x, y) == NULL)
		{
			p->x = x;
			p->y = y;
			set_map_tile(x, y, p);
			return ;
		}
		++i;
		if (i >= MAP_SIZE * MAP_SIZE)
			i = 0;
	}
}

int				create_player(int argc, char **argv)
{
	t_player	*p;

	p = get_player(get_shmem()->nb_user - 1);
	if (argc < 2)
		return (usage());
	p->team = atoi(argv[1]);
	if (p->team <= 0 || p->team > MAX_TEAM)
		return (usage());
	set_player_position(p);
	p->pid = getpid();
	p->is_active = 1;
	printf("Create new player pid %d team %d x %d y %d\n",
			p->pid, p->team, p->x, p->y);
	return (0);
}

t_player		*get_current_player()
{
	t_player	*to_return;

	to_return = &get_shmem()->players[get_shmem()->current_player];
	return (to_return);
}

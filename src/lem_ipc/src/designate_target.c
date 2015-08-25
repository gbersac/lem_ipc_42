/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   designate_target.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 19:17:59 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/25 21:53:17 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static t_player	*target_from_msg()
{
	t_msg	qbuf;
	int		read_ret;

	printf("target_from_msg\n");
	read_ret = read_message(&qbuf, get_current_player()->team);
	if (read_ret < 0)
		return (NULL);
	return (get_player(qbuf.target));
}

static float	dist_players(t_player *p1, t_player *p2)
{
	float	dist;
	float	xs;
	float	ys;

	xs = (p2->x - p1->x) * (p2->x - p1->x);
	ys = (p2->y - p1->y) * (p2->y - p1->y);
	dist = sqrtf(xs + ys);
	return (dist);
}

static t_player	*choose_target()
{
	t_player	*to_return;
	t_player	*p;
	float		min_dist;
	float		player_dist;
	int			i;

	i = 0;
	min_dist = 10000;
	while (i < MAX_PLAYER && get_player(i)->is_active)
	{
		p = get_player(i);
		printf("i %d get_proc_player_id %d\n", i, get_proc_player_id(NULL));
		if (i != get_proc_player_id(NULL) &&
				p->team != get_current_player()->team)
		{
			printf("choose_target in loop\n");
			player_dist = dist_players(p, get_current_player());
			if (player_dist < min_dist)
			{
				to_return = p;
				min_dist = player_dist;
			}
		}
		++i;
	}
	printf("choose_target end\n");
	if (to_return != NULL)
		printf("choose_target %d\n", to_return->team);
	return(to_return);
}

t_player		*designate_target()
{
	t_player	*to_return;

	to_return = target_from_msg();
	printf("designate_target %p\n", to_return);
	if (to_return == NULL)
		to_return = choose_target();
	if (to_return != NULL)
	{
		printf("send_message team %d target %d\n",
				get_current_player()->team, get_player_id(to_return));
		send_message(get_current_player()->team, get_player_id(to_return));
	}
	return(to_return);
}

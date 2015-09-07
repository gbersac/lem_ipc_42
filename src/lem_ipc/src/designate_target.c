/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   designate_target.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 19:17:59 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/28 18:14:26 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static t_player	*target_from_msg(void)
{
	t_msg		qbuf;
	int			read_ret;
	t_player	*target;

	read_ret = read_message(&qbuf, get_current_player()->team);
	if (read_ret < 0)
		return (NULL);
	target = get_player(qbuf.target);
	if (!target->is_active ||
			target->team == get_current_player()->team)
		return (NULL);
	return (target);
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

static t_player	*choose_target(void)
{
	t_player	*to_return;
	t_player	*p;
	float		min_dist;
	float		player_dist;
	size_t		i;

	i = 0;
	min_dist = 10000;
	while (i < get_shmem()->nb_user)
	{
		p = get_player(i);
		if (p->pid != getpid() && p->team != get_current_player()->team)
		{
			// printf("p->pid %d p->team %d curplay->pid %d get_current_player()->team %d\n",
			// 		p->pid,
			// 		p->team,
			// 		getpid(),
			// 		get_current_player()->team);
			player_dist = dist_players(p, get_current_player());
			if (player_dist < min_dist)
			{
				to_return = p;
				min_dist = player_dist;
			}
		}
		++i;
	}
	return(to_return);
}

t_player		*designate_target(void)
{
	t_player	*to_return;

	to_return = target_from_msg();
	if (to_return == NULL)
		to_return = choose_target();
	if (to_return != NULL)
		send_message(get_current_player()->team, get_player_id(to_return));
	return(to_return);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_victory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 19:43:38 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/28 17:41:51 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

static void	print_victorious(int *teams)
{
	int			i;

	i = 0;
	while (i < MAX_TEAM)
	{
		if (teams[i] > 1)
		{
			printf("The team %d is victorious !!!\n", i + 1);
			return ;
		}
		++i;
	}
}

static int	test_teams(int *teams)
{
	size_t		i;
	int			nb_alive_team;

	i = 0;
	nb_alive_team = 0;
	while (i < MAX_TEAM)
	{
		if (teams[i] > 1)
			++nb_alive_team;
		++i;
	}
	if (nb_alive_team > 1)
		return (0);
	print_victorious(teams);
	return (1);
}

int			test_victory(void)
{
	size_t		i;
	int			teams[MAX_TEAM];

	bzero(teams, MAX_TEAM * sizeof(int));
	i = 0;
	while (i < get_shmem()->nb_user)
	{
		if (get_player(i)->is_active)
			++teams[get_player(i)->team - 1];
		++i;
	}
	return (test_teams(teams));
}

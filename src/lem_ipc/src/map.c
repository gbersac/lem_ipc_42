/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/21 12:24:29 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/21 13:00:16 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

t_tile	*get_map_tile(int x, int y)
{
	t_tile	*to_return;

	to_return = &get_shmem()->map.tiles[x * MAP_SIZE + y];
	return (to_return);
}

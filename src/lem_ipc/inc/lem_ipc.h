/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_ipc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/20 20:20:36 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/21 12:59:11 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IPC_H
# define LEM_IPC_H

# define SHMEM_RIGHT	0644
# define SHMEM_KEY		42
# define MAX_PLAYER		64
# define MAP_SIZE		32

# include <sys/shm.h>
# include <stdio.h>
# include <signal.h>
# include <sys/sem.h>
# include <errno.h>
# include <sys/ipc.h>
# include <sys/types.h>
# include <semaphore.h>

# include "libft.h"

struct s_player;

typedef struct sembuf	t_sembuf;
typedef union semun		t_semun;
typedef struct s_player	*t_tile;

typedef struct	s_player
{
	int			team;
	pid_t		pid;
	t_tile		*position;
	int			x;
	int			y;
}				t_player;


typedef struct	s_map
{
	t_tile		tiles[MAP_SIZE * MAP_SIZE];
	size_t		size;
}				t_map;

typedef struct	s_shmem
{
	size_t		nb_user;
	int			semaph_id;
	pid_t		locking_process;
	t_player	players[MAX_PLAYER];
	size_t		current_player;
	t_map		map;
}				t_shmem;

t_shmem		*get_shmem();
int			get_shmemid();

/*
** Maybe possibility of very rare data racing when exit_shmem decrement the
** number of users.
*/
void		exit_shmem();

int			semaph_init();
int			semaph_wait_lock(int semid);
int			semaph_unlock(int semid);

int			create_player();
t_player	*get_current_player();

int			play_turn();

t_tile		*get_map_tile(int x, int y);

#endif

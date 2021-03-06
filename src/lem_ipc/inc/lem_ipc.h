/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_ipc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/20 20:20:36 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/28 18:02:50 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IPC_H
# define LEM_IPC_H

# define SHMEM_RIGHT		0644
# define SHMEM_KEY			42
# define MAX_PLAYER			64
# define MAX_TEAM			9
# define MAP_SIZE			8
# define NO_SEMAPH_LOCKER	0

# include <string.h>
# include <math.h>
# include <time.h>
# include <sys/shm.h>
# include <stdio.h>
# include <signal.h>
# include <sys/sem.h>
# include <sys/msg.h>
# include <errno.h>
# include <sys/ipc.h>
# include <sys/types.h>
# include <semaphore.h>

# include "libft.h"

struct s_player;

typedef struct sembuf	t_sembuf;
typedef union semun		t_semun;
typedef int				t_tile;

typedef struct	s_player
{
	int			team;
	pid_t		pid;
	int			x;
	int			y;
	int			is_active;
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
	int			nb_turn;
	int			semaph_locker;
}				t_shmem;

t_shmem			*get_shmem();
int				get_shmid();

/*
** Maybe possibility of very rare data racing when exit_shmem decrement the
** number of users.
*/
void			exit_shmem();
void			sig_handler(int sig);

int				semaph_wait_lock();
int				semaph_unlock();
int				get_semaph();

int				create_player(int argc, char **argv);
t_player		*get_current_player();
t_player		*get_player(int idx);
int				get_player_id(t_player *p);
void			move_player(t_player *player, t_player *target);

/*
** Return the id on which the user of this process is registered in
** shmem->players.
*/
int				get_proc_player_id();

/*
** Return the player of this process.
*/
t_player		*get_proc_player();

int				play_turn();

t_player		*get_map_tile(int x, int y);
int				set_map_tile(int x, int y, t_player *p);
void			print_map(void);

typedef struct	s_msg
{
	long		type;
	int			team;
	int			target;
}				t_msg;
int				get_msg_queue();
void			send_message(int team, int target);
int				read_message(t_msg *qbuf, int team);
void			remove_queue();

t_player		*designate_target();
int				test_player_is_alive(t_player *p);
void			next_player(t_shmem *mem);
int				test_victory();
void			kill_all();

#endif

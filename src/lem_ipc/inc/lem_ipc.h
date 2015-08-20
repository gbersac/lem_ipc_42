#ifndef LEM_IPC_H
# define LEM_IPC_H

# define SHMEM_RIGHT	0644
# define SHMEM_KEY		42

# include <sys/shm.h>
# include <stdio.h>
# include <signal.h>
# include <sys/sem.h>
# include <errno.h>
# include <sys/ipc.h>
# include <sys/types.h>
# include <semaphore.h>

# include "libft.h"

typedef struct sembuf	t_sembuf;
typedef union semun		t_semun;

typedef struct	s_shmem
{
	size_t		nb_user;
	int			semaph_id;
	pid_t		locking_process;
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

#endif

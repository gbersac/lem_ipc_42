#ifndef LEM_IPC_H
# define LEM_IPC_H

# define SHMEM_RIGHT	0644
# define SHMEM_KEY		42

# include <sys/shm.h>
# include <stdio.h>
# include <signal.h>

# include "libft.h"

typedef struct	s_shmem
{
	size_t		nb_user;
}				t_shmem;

t_shmem		*get_shmem();
int			get_shmemid();
void		exit_shmem();

#endif

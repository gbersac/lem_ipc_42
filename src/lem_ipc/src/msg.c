/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 17:26:57 by gbersac           #+#    #+#             */
/*   Updated: 2015/08/25 20:44:31 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

int		get_msg_queue()
{
	static int	to_return = -1;
	int			key;

	if (to_return == -1)
	{
		key = SHMEM_KEY;
		if((to_return = msgget(key, IPC_CREAT | SHMEM_RIGHT)) == -1)
				printf("Error : can't get message queue");
	}
	return(to_return);
}

void	send_message(int team, int target)
{
	int		msgsnd_result;
	t_msg	qbuf;

	qbuf.type = (long)team;
	qbuf.team = team;
	qbuf.target = target;
	printf("send_message\n");
	msgsnd_result = msgsnd(get_msg_queue(),
			(struct msgbuf*)&qbuf,
			sizeof(t_msg),
			0);
	if(msgsnd_result == -1)
		printf("Error can't send message to msg queue %d\n", get_msg_queue());
}

int		read_message(t_msg *qbuf, int team)
{
	ssize_t	msgrcv_ret;

	printf("read_message\n");
	qbuf->type = team;
	msgrcv_ret = msgrcv(get_msg_queue(),
			(struct msgbuf*)qbuf, sizeof(t_msg), team, IPC_NOWAIT);
	return ((int)msgrcv_ret);
}

void	remove_queue()
{
	msgctl(get_msg_queue(), IPC_RMID, 0);
}

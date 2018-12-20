/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include "my.h"

static int create_map(data_t *data)
{
	data->mem = shmget(data->key, sizeof(int) *
			MAP_LENGTH * MAP_WIDTH, SHM_R | SHM_W);
	if (data->mem == -1)
	{
		data->host = 1;
		data->mem = shmget(data->key, sizeof(int) *
				MAP_LENGTH * MAP_WIDTH,
				IPC_CREAT | SHM_R | SHM_W);
		data->msg = msgget(data->key, IPC_CREAT | SHM_R | SHM_W);
		data->sem = semget(data->key, 2, IPC_CREAT | SHM_R | SHM_W);
		data->map = (int *)shmat(data->mem, NULL, SHM_R | SHM_W);
		memset(data->map, 0, sizeof(int) * MAP_LENGTH * MAP_WIDTH);
		return (SUCESS);
	}
	data->host = 0;
	data->msg = msgget(data->key, SHM_R | SHM_W);
	data->sem = semget(data->key, 2, SHM_R | SHM_W);
	data->map = shmat(data->mem, NULL, SHM_R | SHM_W);
	return (SUCESS);
}

static void create_player(data_t *data)
{
	data->move.sem_op = 1;
	while (semctl(data->sem, 0, GETVAL) > 0);
	semop(data->sem, &data->move, 1);
	do
	{
		data->pos.x = (rand() % (MAP_WIDTH - 1)) + 1;
		data->pos.y = (rand() % (MAP_LENGTH - 1)) + 1;
	} while (data->map[MAP_LENGTH * data->pos.x + data->pos.y] != 0);
	data->map[MAP_LENGTH * data->pos.x + data->pos.y] = data->team_name;
	data->move.sem_op = -1;
	semop(data->sem, &data->move, 1);
}

int connect(data_t *data, char *path, int teamname)
{
	if (teamname <= 0 || teamname > 999)
		return (ERROR);
	data->team_name = teamname;
	srand(getpid());
	data->key = ftok(path, 0);
	create_map(data);
	data->move.sem_num = 0;
	data->move.sem_flg = 0;
	data->move.sem_op = 1;
	data->alive.sem_num = 1;
	data->alive.sem_flg = 0;
	data->alive.sem_op = 1;
	semop(data->sem, &data->alive, 1);
	create_player(data);
	return (SUCESS);
}

int	disconnect(data_t *data)
{
	move_bot(data, 0);
	data->alive.sem_op = -1;
	semop(data->sem, &data->alive, 1);
	if (semctl(data->sem, 1, GETVAL) == 0)
	{
		shmctl(data->mem, IPC_RMID, NULL);
		semctl(data->sem, 0, IPC_RMID, NULL);
		semctl(data->sem, 1, IPC_RMID, NULL);
		msgctl(data->msg, IPC_RMID, NULL);
	}
	return (SUCESS);
}

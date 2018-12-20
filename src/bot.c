/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include "my.h"

int check_near(int *map, pos_t *pos, int team)
{
	int enemy = 0;

	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if (i + pos->x >= 0 && i + pos->x <= MAP_LENGTH - 1 &&
			j + pos->y >= 0 && j + pos->y <= MAP_WIDTH - 1 &&
			map[MAP_LENGTH * (i + pos->x) + (j + pos->y)] != 0 &&
			map[MAP_LENGTH * (i + pos->x) + (j + pos->y)] != team)
				enemy += 1;
	return (enemy);
}

int try_move_part_2(data_t *data)
{
	int tmp;

	if (data->pos.y > MAP_LENGTH / 2)
		tmp = direction[0](data);
	else
		tmp = direction[1](data);
	return (tmp);
}

int try_move(data_t *data)
{
	int	i = 0;
	int	tmp = ERROR;

	while (i < 5)
	{
		if (rand() % 2)
			tmp = try_move_part_2(data);
		else
		{
			if (data->pos.x < MAP_WIDTH / 2)
				tmp = direction[3](data);
			else
				tmp = direction[2](data);
		}
		if (tmp == SUCESS)
			return (SUCESS);
		i += 1;
	}
	return (ERROR);
}

int move_bot(data_t *data, int team_name)
{
	int enemy;

	data->move.sem_op = 1;
	while (semctl(data->sem, 0, GETVAL) > 0);
	semop(data->sem, &data->move, 1);
	data->map[MAP_LENGTH * data->pos.x + data->pos.y] = 0;
	enemy = check_near(data->map, &data->pos, team_name);
	if (enemy >= 2 || team_name == 0)
	{
		data->move.sem_op = -1;
		semop(data->sem, &data->move, 1);
		return (ERROR);
	}
	try_move(data);
	printf("%d %d %d\n", data->pos.x, data->pos.y, enemy);
	data->map[MAP_LENGTH * data->pos.x + data->pos.y] = team_name;
	data->move.sem_op = -1;
	semop(data->sem, &data->move, 1);
	return (SUCESS);
}

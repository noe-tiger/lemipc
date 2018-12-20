/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include "my.h"

int (*direction[4])(data_t *data) =
{
	north,
	south,
	east,
	west
};

int east(data_t *data)
{
	if (data->pos.x < 1)
		return (ERROR);
	if (data->map[MAP_LENGTH * (data->pos.x - 1) + data->pos.y] == 0)
	{
		data->pos.x -= 1;
		return (SUCESS);
	}
	return (ERROR);
}

int west(data_t *data)
{
	if (data->pos.x > MAP_LENGTH - 2)
		return (ERROR);
	if (data->map[MAP_LENGTH * (data->pos.x + 1) + data->pos.y] == 0)
	{
		data->pos.x += 1;
		return (SUCESS);
	}
	return (ERROR);
}

int north(data_t *data)
{
	if (data->pos.y < 1)
		return (ERROR);
	if (data->map[MAP_LENGTH * data->pos.x + (data->pos.y - 1)] == 0)
	{
		data->pos.y -= 1;
		return (SUCESS);
	}
	return (ERROR);
}

int south(data_t *data)
{
	if (data->pos.y > MAP_WIDTH - 2)
		return (ERROR);
	if (data->map[MAP_LENGTH * data->pos.x + (data->pos.y + 1)] == 0)
	{
		data->pos.y += 1;
		return (SUCESS);
	}
	return (ERROR);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_door_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:44:31 by melinaaam         #+#    #+#             */
/*   Updated: 2025/03/14 13:33:00 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_one_door(t_game *game, int i, int j)
{
	int	row_len;
	int	hor;
	int	vert;

	hor = 0;
	vert = 0;
	row_len = ft_strlen(game->map[i]);
	if (j > 0 && j < row_len - 1)
	{
		if (game->map[i][j - 1] == '1' && game->map[i][j + 1] == '1')
			hor = 1;
	}
	if (game->map[i - 1][j] && game->map[i + 1][j])
	{
		if (game->map[i - 1][j] == '1' && game->map[i + 1][j] == '1')
			vert = 1;
	}
	return (hor || vert);
}

int	door_surrounded(t_game *game)
{
	int	d;
	int	i;
	int	j;

	d = 0;
	while (d < game->barrier_nb)
	{
		i = game->door[d].pos.y;
		j = game->door[d].pos.x;
		if (!check_one_door(game, i, j))
			return (write_err(RED DOOR RESET), 1);
		d++;
	}
	return (0);
}

static void	recup_door(char **map, t_game *game)
{
	int	i;
	int	j;
	int	count;

	if (!game->door)
		return (write_err(RED MALLOC RESET));
	ft_bzero(game->door, sizeof(t_door) * game->barrier_nb);
	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D')
			{
				game->door[count].pos.y = i;
				game->door[count].pos.x = j;
				game->door[count].id = count;
				count++;
			}
			j++;
		}
		i++;
	}
}

int	map_parse_door(t_game *game, char **map)
{
	int	i;

	i = 0;
	while (map[i])
		game->barrier_nb += ft_count_chars(map[i++], "D");
	if (game->barrier_nb)
	{
		game->door = malloc(sizeof(t_door) * (game->barrier_nb));
		if (!game->door)
			return (write_err(RED MALLOC RESET), 1);
		recup_door(map, game);
		if (door_surrounded(game))
			return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elmts_parse_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinaaam <melinaaam@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:08:46 by melinaaam         #+#    #+#             */
/*   Updated: 2025/03/13 11:50:09 by melinaaam        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

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
	if (i > 0 && i < game->height_map - 1)
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

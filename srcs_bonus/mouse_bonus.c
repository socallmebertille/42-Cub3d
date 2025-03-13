/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinaaam <melinaaam@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:19:48 by saberton          #+#    #+#             */
/*   Updated: 2025/03/13 16:01:18 by melinaaam        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	mouse_move(int x, int y, t_game *game)
{
	(void)y;
	if (x < game->mouse.x)
	{
		move_view_west(game);
		mlx_mouse_move(game->mlx, game->win, game->win_width / 2,
			game->win_height / 2);
		game->mouse.x = game->win_width / 2;
		game->mouse.y = game->win_height / 2;
	}
	else if (x > game->mouse.x)
	{
		move_view_east(game);
		mlx_mouse_move(game->mlx, game->win, game->win_width / 2,
			game->win_height / 2);
		game->mouse.x = game->win_width / 2;
		game->mouse.y = game->win_height / 2;
	}
	return (0);
}

static int	check_proximity(t_game *game)
{
	double	distance;
	double	threshold;

	threshold = 3;
	distance = sqrt(pow(game->ray_door.map.x + 0.5 - game->player.x, 2)
			+ pow(game->ray_door.map.y + 0.5 - game->player.y, 2));
	if (distance > threshold)
		return (0);
	return (1);
}

int	mouse_press(int button, int x, int y, t_game *game)
{
	(void)y;
	if (button == 1)
	{
		if (get_ray_to_door(game, x) == 'D' && check_proximity(game))
		{
			game->barrier_open = 1;
			toggle_barrier(game, (int)game->ray_door.map.x,
				(int)game->ray_door.map.y);
		}
	}
	return (0);
}

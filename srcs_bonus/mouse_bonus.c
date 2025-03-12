/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:19:48 by saberton          #+#    #+#             */
/*   Updated: 2025/03/12 17:44:14 by memotyle         ###   ########.fr       */
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

static void	init_ray_door(t_game *g)
{
	if (g->ray_door.ray_dir.x == 0)
		g->ray_door.delta.x = 1e30;
	else
		g->ray_door.delta.x = fabs(1.0 / g->ray_door.ray_dir.x);
	if (g->ray_door.ray_dir.y == 0)
		g->ray_door.delta.y = 1e30;
	else
		g->ray_door.delta.y = fabs(1.0 / g->ray_door.ray_dir.y);
	if (g->ray_door.ray_dir.x < 0)
	{
		g->ray_door.step.x = -1;
		g->ray_door.side_dist.x = (g->player.x - g->ray_door.map.x)
			* g->ray_door.delta.x;
	}
	else
	{
		g->ray_door.step.x = 1;
		g->ray_door.side_dist.x = ((g->ray_door.map.x + 1.0) - g->player.x)
			* g->ray_door.delta.x;
	}
	if (g->ray_door.ray_dir.y < 0)
	{
		g->ray_door.step.y = -1;
		g->ray_door.side_dist.y = (g->player.y - g->ray_door.map.y)
			* g->ray_door.delta.y;
	}
	else
	{
		g->ray_door.step.y = 1;
		g->ray_door.side_dist.y = ((g->ray_door.map.y + 1.0) - g->player.y)
			* g->ray_door.delta.y;
	}
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
	float	ray_angle;
	t_ray	ray_door;
	float	fov;
	int		hit;
	char	c;

	(void)y;
	if (button == 1)
	{
		fov = M_PI / 3.0;
		ray_angle = game->angle - (fov / 2.0) + (x / (float)game->win_width)
			* fov;
		ft_bzero(&ray_door, sizeof(t_ray));
		game->ray_door.map.x = (int)game->player.x;
		game->ray_door.map.y = (int)game->player.y;
		game->ray_door.ray_dir.x = cos(ray_angle);
		game->ray_door.ray_dir.y = sin(ray_angle);
		init_ray_door(game);
		hit = 0;
		while (!hit)
		{
			if (game->ray_door.side_dist.x < game->ray_door.side_dist.y)
			{
				game->ray_door.side_dist.x += game->ray_door.delta.x;
				game->ray_door.map.x += game->ray_door.step.x;
				game->ray_door.side = 0;
			}
			else
			{
				game->ray_door.side_dist.y += game->ray_door.delta.y;
				game->ray_door.map.y += game->ray_door.step.y;
				game->ray_door.side = 1;
			}
			c = game->map[(int)game->ray_door.map.y][(int)game->ray_door.map.x];
			if (c == '1' || c == 'D')
				hit = 1;
		}
		if (c == 'D' && check_proximity(game))
		{
			game->barrier_open = 1;
			toggle_barrier(game, (int)game->ray_door.map.x,
				(int)game->ray_door.map.y);
		}
	}
	return (0);
}

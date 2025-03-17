/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_to_door_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinaaam <melinaaam@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:54:13 by melinaaam         #+#    #+#             */
/*   Updated: 2025/03/13 16:01:35 by melinaaam        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_ray_door2(t_game *g)
{
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
	init_ray_door2(g);
}

static char	get_hit(t_game *game)
{
	int		hit;
	char	c;

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
	return (c);
}

char	get_ray_to_door(t_game *game, int x)
{
	float	ray_angle;
	t_ray	ray_door;
	float	fov;

	fov = M_PI / 3.0;
	ray_angle = game->angle - (fov / 2.0) + (x / (float)game->win_width)
		* fov;
	ft_bzero(&ray_door, sizeof(t_ray));
	game->ray_door.map.x = (int)game->player.x;
	game->ray_door.map.y = (int)game->player.y;
	game->ray_door.ray_dir.x = cos(ray_angle);
	game->ray_door.ray_dir.y = sin(ray_angle);
	init_ray_door(game);
	return (get_hit(game));
}

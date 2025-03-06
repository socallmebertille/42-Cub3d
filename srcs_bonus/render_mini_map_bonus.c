/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertille <bertille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:15:22 by kepouliq          #+#    #+#             */
/*   Updated: 2025/03/05 17:09:49 by bertille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_square(t_game *game, int color, int start_x, int start_y)
{
	int	i;
	int	j;

	i = 0;
	while (i < PX)
	{
		j = 0;
		while (j < PX)
		{
			put_pixel_to_img(&game->img, start_x + j, start_y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_player(t_game *game, int color, float x, float y)
{
	int	i;
	int	j;

	i = 0 - (PX / 2);
	while (i < PX / 2)
	{
		j = 0 - (PX / 2);
		while (j < PX / 2)
		{
			put_pixel_to_img(&game->img, (int)x + j, (int)y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_game *game, t_player play, t_player *hit)
{
	int			i;
	float		steps;
	t_player	line;
	t_player	increment;

	steps = fmax(fabs(hit->x - (play.x * PX)), fabs(hit->y - (play.y * PX)));
	increment.x = (hit->x - (play.x * PX)) / steps;
	increment.y = (hit->y - (play.y * PX)) / steps;
	line.x = (play.x * PX);
	line.y = (play.y * PX);
	i = 0;
	while (i < steps)
	{
		put_pixel_to_img(&game->img, (int)line.x, (int)line.y, 0xff0000);
		line.x += increment.x;
		line.y += increment.y;
		i++;
	}
}

void	render_mini_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '0' || game->map[y][x] == 'N'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'W')
				draw_square(game, 0x40E0D0, x * PX, y * PX);
			else if (game->map[y][x] == '1')
				draw_square(game, 0xfffacd, x * PX, y * PX);
			x++;
		}
		y++;
	}
	draw_player(game, 0x7fff00, game->player.x * PX, game->player.y * PX);
	draw_radius(game, game->player);
}

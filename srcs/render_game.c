/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:40:43 by saberton          #+#    #+#             */
/*   Updated: 2025/03/03 17:31:06 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_view_west(t_game *game)
{
	game->degree -= 1;
	if (game->degree == -1)
		game->degree = 359;
	else if (game->degree == 360)
		game->degree = 0;
	game->angle = ((float)game->degree * M_PI / 180.0) - (0 - (2 * M_PI));
	game->dir.x = game->dir.x * cos(-0.02) - game->dir.y * sin(-0.02);
	game->dir.y = game->dir.x * sin(-0.02) + game->dir.y * cos(-0.02);
	game->plane.x = game->plane.x * cos(-0.02) - game->plane.y * sin(-0.02);
	game->plane.y = game->plane.x * sin(-0.02) + game->plane.y * cos(-0.02);
}

static void	move_view_east(t_game *game)
{
	game->degree += 1;
	if (game->degree == -1)
		game->degree = 359;
	else if (game->degree == 360)
		game->degree = 0;
	game->angle = ((float)game->degree * M_PI / 180.0) - (0 - (2 * M_PI));
	game->dir.x = game->dir.x * cos(0.02) + game->dir.y * sin(0.02);
	game->dir.y = game->dir.x * sin(0.02) - game->dir.y * cos(0.02);
	game->plane.x = game->plane.x * cos(0.02) - game->plane.y * sin(0.02);
	game->plane.y = game->plane.x * sin(0.02) + game->plane.y * cos(0.02);
}

int	render_game(t_game *game)
{
	if (game->keys.north)
		move_north(game);
	else if (game->keys.south)
		move_south(game);
	else if (game->keys.west)
		move_west(game);
	else if (game->keys.east)
		move_east(game);
	if (game->keys.view_west)
		move_view_west(game);
	else if (game->keys.view_east)
		move_view_east(game);
	put_img(game);
	render_mini_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

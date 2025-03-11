/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:19:48 by saberton          #+#    #+#             */
/*   Updated: 2025/03/11 14:13:21 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int mouse_move(int x, int y, t_game *game)
{
	(void)y;
	// mlx_mouse_hide(game->mlx, game->win);
	if (x < game->mouse.x)
	{
		move_view_west(game);
		mlx_mouse_move(game->mlx, game->win, game->win_width / 2, game->win_height / 2);
		game->mouse.x = game->win_width / 2;
		game->mouse.y = game->win_height / 2;
	}
	else if (x > game->mouse.x)
	{
		move_view_east(game);
		mlx_mouse_move(game->mlx, game->win, game->win_width / 2, game->win_height / 2);
		game->mouse.x = game->win_width / 2;
		game->mouse.y = game->win_height / 2;
	}
    return (0);
}

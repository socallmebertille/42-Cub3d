/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_handlebars_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:54:02 by saberton          #+#    #+#             */
/*   Updated: 2025/03/10 17:56:07 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	handle_left_movement(t_game *game)
{
	if (game->keys.west || game->keys.view_west)
	{
		if (game->pics->left != 1)
		{
			game->pics->left = 1;
			game->pics->step = 0;
		}
		if (game->pics->step < 5)
		{
			game->player_sprite = game->pics->left_0;
			game->pics->step++;
		}
		else
			game->player_sprite = game->pics->left_1;
	}
}

static void	handle_right_movement(t_game *game)
{
	if (game->keys.east || game->keys.view_east)
	{
		if (game->pics->left != 2)
		{
			game->pics->left = 2;
			game->pics->step = 0;
		}
		if (game->pics->step < 5)
		{
			game->player_sprite = game->pics->right_0;
			game->pics->step++;
		}
		else
			game->player_sprite = game->pics->right_1;
	}
}

static void	handle_return_left(t_game *game)
{
	if (game->pics->step < 5)
	{
		game->pics->step++;
		if (game->pics->step >= 5)
		{
			game->player_sprite = game->pics->straight;
			game->pics->left = 0;
			game->pics->step = 0;
		}
		game->player_sprite = game->pics->left_0;
	}
	else
	{
		game->player_sprite = game->pics->straight;
		game->pics->left = 0;
	}
}

static void	handle_return_right(t_game *game)
{
	if (game->pics->step < 5)
	{
		game->pics->step++;
		if (game->pics->step >= 5)
		{
			game->player_sprite = game->pics->straight;
			game->pics->left = 0;
			game->pics->step = 0;
		}
		game->player_sprite = game->pics->right_0;
	}
	else
	{
		game->player_sprite = game->pics->straight;
		game->pics->left = 0;
	}
}

void	update_animation(t_game *game)
{
	if ((game->keys.west || game->keys.view_west) && game->pics->left != 2)
		handle_left_movement(game);
	else if ((game->keys.east || game->keys.view_east) && game->pics->left != 1)
		handle_right_movement(game);
	else if (game->pics->left == 1 && !game->keys.west && !game->keys.view_west)
	{
		if (game->pics->step >= 5)
			game->pics->step = 0;
		handle_return_left(game);
	}
	else if (game->pics->left == 2 && !game->keys.east && !game->keys.view_east)
	{
		if (game->pics->step >= 5)
			game->pics->step = 0;
		handle_return_right(game);
	}
	else if (game->pics->left == 0)
		game->player_sprite = game->pics->straight;
}

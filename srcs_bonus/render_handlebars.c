/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_handlebars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 6025/03/07 15:04:51 by saberton          #+#    #+#             */
/*   Updated: 2025/03/10 14:31:52 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	start_sprite(t_game *game)
{
	if (game->keys.west == 1 || game->keys.view_west == 1)
	{
		game->pics->left = 1;
		if (timestamp() - game->pics->start_sprite >= 50)
		{
			game->player_sprite = game->pics->left_1;
			game->pics->start_sprite = 0;
			printf("2/3 left\n");
		}
		else
		{
			game->player_sprite = game->pics->left_0;
			printf("1/3 left\n");
		}
	}
	else if (game->keys.east == 1 || game->keys.view_east == 1)
	{
		game->pics->left = 0;
		if (timestamp() - game->pics->start_sprite >= 50)
		{
			game->player_sprite = game->pics->right_1;
			game->pics->start_sprite = 0;
			printf("2/3 right\n");
		}
		else
		{
			game->player_sprite = game->pics->right_0;
			printf("1/3 right\n");
		}
	}
}

static void	end_sprite(t_game *game)
{
	if (game->pics->left == 1)//(game->player_sprite == game->pics->left_1)
	{
		if (timestamp() - game->pics->end_sprite >= 50)
		{
			game->player_sprite = game->pics->straight;
			game->pics->end_sprite = 0;
			printf("2/3 left straight\n");
		}
		else
		{
			game->player_sprite = game->pics->left_0;
			printf("1/3 left end\n");
		}
	}
	else if (!game->pics->left)//(game->player_sprite == game->pics->right_1)
	{
		if (timestamp() - game->pics->end_sprite >= 50)
		{
			game->player_sprite = game->pics->straight;
			game->pics->end_sprite = 0;
			printf("2/3 right straight\n");
		}
		else
		{
			game->player_sprite = game->pics->right_0;
			printf("1/3 right end\n");
		}
	}
}

static void	get_handlebars_info(t_game *game)
{
	if (game->pics->start_sprite)//(game->keys.west == 1 || game->keys.view_west == 1 || game->keys.east == 1 || game->keys.view_east == 1)
	{
		start_sprite(game);
	}
	else if (game->pics->end_sprite)
	{
		printf("go end\n");
		end_sprite(game);
	}
	else
	{
		game->player_sprite = game->pics->straight;
		game->pics->left = -1;
		// game->pics->start_sprite = 0;
		// game->pics->end_sprite = 0;
	}
}

static void	draw_column_handlebars(t_game *game, int i, t_player *pic)
{
	int	j;
	int	color;

	j = 0;
	while (j < game->win_height)
	{
		if (j >= (game->win_height - game->player_sprite->h))
		{
			color = get_pixel_color(game->player_sprite, pic->x, pic->y);
			if ((color & 0x00FFFFFF) != 0)
				put_pixel_to_img(game, i, j, color);
			pic->y++;
			if (pic->y > game->player_sprite->h - 1)
				pic->y = 0;
		}
		j++;
	}
}

void	render_handlebars(t_game *game)
{
	t_player	pic;
	int			start;
	int			end;

	game->pics->left = -1;
	get_handlebars_info(game);
	ft_bzero(&pic, sizeof(t_player));
	start = (game->win_width - game->player_sprite->w) / 2;
	end = (game->win_width + game->player_sprite->w) / 2;
	while (start < end)
	{
		draw_column_handlebars(game, start, &pic);
		pic.x++;
		if (pic.x > game->player_sprite->w - 1)
			pic.x = 0;
		start++;
	}
}

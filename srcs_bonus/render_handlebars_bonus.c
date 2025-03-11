/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_handlebars_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:55:23 by saberton          #+#    #+#             */
/*   Updated: 2025/03/10 17:55:27 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

	update_animation(game);
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

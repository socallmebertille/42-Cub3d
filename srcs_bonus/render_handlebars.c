/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_handlebars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:04:51 by saberton          #+#    #+#             */
/*   Updated: 2025/03/07 16:29:28 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_img	*init_handlebars(t_game *game, t_img *img, int id)
{
	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		return (write_err(MALLOC), free_all(game), exit(1), NULL);
	ft_bzero(img, sizeof(t_img));
	if (id == 1)
		img->img = mlx_xpm_file_to_image(game->mlx,
				"textures/handlebars/handlebars_straight.xpm", &img->w_width,
				&img->w_height);
	else if (id == 2)
		img->img = mlx_xpm_file_to_image(game->mlx,
				"textures/handlebars/handlebars_left.xpm", &img->w_width,
				&img->w_height);
	else if (id == 3)
		img->img = mlx_xpm_file_to_image(game->mlx,
				"textures/handlebars/handlebars_right.xpm", &img->w_width,
				&img->w_height);
	if (!img->img)
		return (write_err("Error\nFailed to load textures\n"), free_all(game),
			exit(1), NULL);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
		return (write_err("Error\nFailed to get image data address\n"),
			free_all(game), exit(1), NULL);
	return (img);
}

static void get_handlebars_info(t_game *game)
{
    game->pics->straight = init_handlebars(game, game->pics->straight, 1);
    game->pics->left = init_handlebars(game, game->pics->left, 2);
    game->pics->right = init_handlebars(game, game->pics->right, 3);
    if (game->keys.west == 1 || game->keys.view_west == 1)
        game->choice_pic = game->pics->left;
    else if (game->keys.east == 1 || game->keys.view_east == 1)
        game->choice_pic = game->pics->right;
    else
        game->choice_pic = game->pics->straight;
}

void	render_handlebars(t_game *game)
{
	t_player	pic;
	int			start;
	int			end;
	int			i;
	int			j;
	int			color;

    get_handlebars_info(game);
	ft_bzero(&pic, sizeof(t_player));
	start = (game->win_width - game->choice_pic->w_width) / 2;
	end = (game->win_width + game->choice_pic->w_width) / 2;
	i = start;
	while (i < end)
	{
		j = 0;
		while (j < game->win_height)
		{
			if (j >= (game->win_height - game->choice_pic->w_height))
			{
				color = get_pixel_color(game->choice_pic, pic.x, pic.y);
				if ((color & 0x00FFFFFF) != 0) 
					put_pixel_to_img(game, i, j, color);
				pic.y++;
				if (pic.y > game->choice_pic->w_height - 1)
					pic.y = 0;
			}
			j++;
		}
		pic.x++;
		if (pic.x > game->choice_pic->w_width - 1)
			pic.x = 0;
		i++;
	}
}

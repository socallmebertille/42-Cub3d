/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:31:33 by saberton          #+#    #+#             */
/*   Updated: 2025/03/12 12:31:42 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	*init_handlebars(t_game *game, t_img *img, int id)
{
	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		return (write_err(MALLOC), free_all(game), exit(1), NULL);
	ft_bzero(img, sizeof(t_img));
	if (id == 1)
		img->img = mlx_xpm_file_to_image(game->mlx, STRAIGHT, &img->w, &img->h);
	else if (id == 2)
		img->img = mlx_xpm_file_to_image(game->mlx, LEFT0, &img->w, &img->h);
	else if (id == 3)
		img->img = mlx_xpm_file_to_image(game->mlx, LEFT1, &img->w, &img->h);
	else if (id == 4)
		img->img = mlx_xpm_file_to_image(game->mlx, RIGHT0, &img->w, &img->h);
	else if (id == 5)
		img->img = mlx_xpm_file_to_image(game->mlx, RIGHT1, &img->w, &img->h);
	if (!img->img)
		return (write_err("Error\nFailed to load textures\n"), free(img),
			free_all(game), exit(1), NULL);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
		return (write_err("Error\nFailed to get image data address\n"),
			free(img), free_all(game), exit(1), NULL);
	return (img);
}

static t_img	*init_wall(t_game *game, t_img *img, int id)
{
	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		return (write_err(MALLOC), free_all(game), exit(1), NULL);
	ft_bzero(img, sizeof(t_img));
	if (id == 1)
		img->img = mlx_xpm_file_to_image(game->mlx, game->param->no, &img->w,
				&img->h);
	else if (id == 2)
		img->img = mlx_xpm_file_to_image(game->mlx, game->param->so, &img->w,
				&img->h);
	else if (id == 3)
		img->img = mlx_xpm_file_to_image(game->mlx, game->param->we, &img->w,
				&img->h);
	else if (id == 4)
		img->img = mlx_xpm_file_to_image(game->mlx, game->param->ea, &img->w,
				&img->h);
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

static t_img	*init_door(t_game *game, t_img *img, int id)
{
	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		return (write_err(MALLOC), free_all(game), exit(1), NULL);
	ft_bzero(img, sizeof(t_img));
	if (id == 5)
		img->img = mlx_xpm_file_to_image(game->mlx,
				"textures/barrier/barrier_close.xpm", &img->w, &img->h);
	else if (id == 6)
		img->img = mlx_xpm_file_to_image(game->mlx,
				"textures/barrier/barrier_open.xpm", &img->w, &img->h);
	else if (id == 7)
		img->img = mlx_xpm_file_to_image(game->mlx,
				"textures/barrier/barrier_semi_open.xpm", &img->w, &img->h);
	else if (id == 8)
		img->img = mlx_xpm_file_to_image(game->mlx,
				"textures/barrier/barrier_semi2_open.xpm", &img->w, &img->h);
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

static void	init_pic(t_game *game)
{
	game->pics = (t_pics *)malloc(sizeof(t_pics));
	if (!game->pics)
		return (write_err(MALLOC), free_all(game), exit(1));
	ft_bzero(game->pics, sizeof(t_pics));
	game->pics->wall_n = init_wall(game, game->pics->wall_n, 1);
	game->pics->wall_s = init_wall(game, game->pics->wall_s, 2);
	game->pics->wall_w = init_wall(game, game->pics->wall_w, 3);
	game->pics->wall_e = init_wall(game, game->pics->wall_e, 4);
	game->pics->straight = init_handlebars(game, game->pics->straight, 1);
	game->pics->left_0 = init_handlebars(game, game->pics->left_0, 2);
	game->pics->left_1 = init_handlebars(game, game->pics->left_1, 3);
	game->pics->right_0 = init_handlebars(game, game->pics->right_0, 4);
	game->pics->right_1 = init_handlebars(game, game->pics->right_1, 5);
	game->pics->bar_close = init_door(game, game->pics->bar_close, 5);
	game->pics->bar_open = init_door(game, game->pics->bar_open, 6);
	game->pics->bar_semiopen = init_door(game, game->pics->bar_semiopen, 7);
	game->pics->bar_opopen = init_door(game, game->pics->bar_opopen, 8);
	// game->barrier_o_c = 0;
}

void	mlx_initialize(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (write_err(MALLOC), free_all(game), exit(1));
	mlx_get_screen_size(game->mlx, &game->win_width, &game->win_height);
	game->win = mlx_new_window(game->mlx, game->win_width, game->win_height,
			"Cub3D");
	if (!game->win)
		return (write_err(MALLOC), free_all(game), exit(1));
	game->img.img = mlx_new_image(game->mlx, game->win_width, game->win_height);
	if (!game->img.img)
		return (write_err("Error\nDisplay window failed\n"), free_all(game),
			exit(1));
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	init_pic(game);
	mlx_mouse_move(game->mlx, game->win, game->win_width / 2, game->win_height
		/ 2);
	game->mouse.x = game->win_width / 2;
	game->mouse.y = game->win_height / 2;
}

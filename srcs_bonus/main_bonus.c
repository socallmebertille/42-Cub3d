/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertille <bertille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:52:35 by kepouliq          #+#    #+#             */
/*   Updated: 2025/03/05 17:09:12 by bertille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	ft_keypress(int keypress, t_game *game)
{
	if (keypress == XK_Escape)
		quite_game(game);
	else if (keypress == XK_w)
		game->keys.north = 1;
	else if (keypress == XK_s)
		game->keys.south = 1;
	else if (keypress == XK_a)
		game->keys.west = 1;
	else if (keypress == XK_d)
		game->keys.east = 1;
	else if (keypress == XK_Left)
		game->keys.view_west = 1;
	else if (keypress == XK_Right)
		game->keys.view_east = 1;
	return (0);
}

static int	ft_keyrelease(int keypress, t_game *game)
{
	if (keypress == XK_Escape)
		quite_game(game);
	if (keypress == XK_w)
		game->keys.north = 0;
	else if (keypress == XK_s)
		game->keys.south = 0;
	else if (keypress == XK_a)
		game->keys.west = 0;
	else if (keypress == XK_d)
		game->keys.east = 0;
	else if (keypress == XK_Left)
		game->keys.view_west = 0;
	else if (keypress == XK_Right)
		game->keys.view_east = 0;
	return (0);
}

static t_img	*init_pic(t_game *game, t_img *img, int id)
{
	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		return (write_err(MALLOC), free_all(game), exit(1), NULL);
	ft_bzero(img, sizeof(t_img));
	if (id == 1)
		img->img = mlx_xpm_file_to_image(game->mlx, game->param->no,
				&img->w_width, &img->w_height);
	else if (id == 2)
		img->img = mlx_xpm_file_to_image(game->mlx, game->param->so,
				&img->w_width, &img->w_height);
	else if (id == 3)
		img->img = mlx_xpm_file_to_image(game->mlx, game->param->we,
				&img->w_width, &img->w_height);
	else if (id == 4)
		img->img = mlx_xpm_file_to_image(game->mlx, game->param->ea,
				&img->w_width, &img->w_height);
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

static void	mlx_initialize(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (write_err(MALLOC), free_all(game), exit(1));
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
		return (write_err(MALLOC), free_all(game), exit(1));
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img.img)
		return (write_err("Error\nDisplay window failed\n"), free_all(game),
			exit(1));
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	game->pics = (t_pics *)malloc(sizeof(t_pics));
	if (!game->pics)
		return (write_err(MALLOC), free_all(game), exit(1));
	ft_bzero(game->pics, sizeof(t_pics));
	game->pics->wall_n = init_pic(game, game->pics->wall_n, 1);
	game->pics->wall_s = init_pic(game, game->pics->wall_s, 2);
	game->pics->wall_w = init_pic(game, game->pics->wall_w, 3);
	game->pics->wall_e = init_pic(game, game->pics->wall_e, 4);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (write_err(RED "Error\nIncorrect number of args\n" RESET), 1);
	ft_bzero(&game, sizeof(game));
	if (check_map_file(argv[1], &game))
		return (1);
	map_file_parse(&game);
	mlx_initialize(&game);
	mlx_loop_hook(game.mlx, &render_game, &game);
	mlx_hook(game.win, 2, 1L << 0, &ft_keypress, &game);
	mlx_hook(game.win, 3, 1L << 1, &ft_keyrelease, &game);
	mlx_hook(game.win, 33, 0, (void *)quite_game, &game);
	mlx_loop(game.mlx);
	free_all(&game);
	return (0);
}

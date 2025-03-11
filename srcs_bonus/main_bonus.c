/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:52:35 by kepouliq          #+#    #+#             */
/*   Updated: 2025/03/11 11:39:27 by saberton         ###   ########.fr       */
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
	mlx_hook(game.win, KeyPress, KeyPressMask, &ft_keypress, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, &ft_keyrelease, &game);
	mlx_hook(game.win, MotionNotify, PointerMotionMask, &mouse_move, &game);
	mlx_hook(game.win, 33, 0, (void *)quite_game, &game);
	mlx_loop(game.mlx);
	free_all(&game);
	return (0);
}

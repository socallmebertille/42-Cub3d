/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:16:05 by kepouliq          #+#    #+#             */
/*   Updated: 2025/03/12 12:38:37 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	free_one_param(char *param)
{
	if (param)
	{
		free(param);
		param = NULL;
	}
}

static void	free_one_img(t_game *game, t_img *img)
{
	if (img)
	{
		mlx_destroy_image(game->mlx, img->img);
		free(img);
		img = NULL;
	}
}

static void	free_pics_and_param(t_game *game)
{
	if (game->pics)
	{
		free_one_img(game, game->pics->wall_n);
		free_one_img(game, game->pics->wall_s);
		free_one_img(game, game->pics->wall_w);
		free_one_img(game, game->pics->wall_e);
		free_one_img(game, game->pics->straight);
		free_one_img(game, game->pics->left_0);
		free_one_img(game, game->pics->left_1);
		free_one_img(game, game->pics->right_0);
		free_one_img(game, game->pics->right_1);
		free_one_img(game, game->pics->bar_close);
		free_one_img(game, game->pics->bar_open);
		free_one_img(game, game->pics->bar_opopen);
		free_one_img(game, game->pics->bar_semiopen);
	}
	if (game->param)
	{
		free_one_param(game->param->no);
		free_one_param(game->param->so);
		free_one_param(game->param->we);
		free_one_param(game->param->ea);
		free_one_param(game->param->floor_color);
		free_one_param(game->param->ceiling_color);
	}
}

void	free_all(t_game *game)
{
	if (game->map_file)
		ft_free_tab(game->map_file);
	if (game->map)
		ft_free_tab(game->map);
	if (game->check_map)
		ft_free_tab(game->check_map);
	free_pics_and_param(game);
	if (game->param)
	{
		free(game->param);
		game->param = NULL;
	}
	if (game->pics)
	{
		free(game->pics);
		game->pics = NULL;
	}
	if (game->barrier_nb)
	{
		// while (game->barrier_nb)
		// {
		// 	free(game->door[game->barrier_nb - 1]);
		// 	game->door[game->barrier_nb - 1] = NULL;
		// 	game->barrier_nb--;
		// }
		free(game->door);
		game->door = NULL;
	}
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	quite_game(t_game *game)
{
	free_all(game);
	exit(0);
}

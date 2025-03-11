/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:16:05 by kepouliq          #+#    #+#             */
/*   Updated: 2025/03/11 14:13:00 by saberton         ###   ########.fr       */
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
		free(game->pics);
		game->pics = NULL;
	}
	if (game->param)
	{
		free_one_param(game->param->no);
		free_one_param(game->param->so);
		free_one_param(game->param->we);
		free_one_param(game->param->ea);
		free_one_param(game->param->floor_color);
		free_one_param(game->param->ceiling_color);
		free(game->param);
		game->param = NULL;
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
	// mlx_mouse_show(game->mlx, game->win);
	free_all(game);
	exit(0);
}

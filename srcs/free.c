/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:16:05 by kepouliq          #+#    #+#             */
/*   Updated: 2025/02/10 15:33:36 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_param2(t_param *param)
{
	if (param->floor_color)
	{
		free(param->floor_color);
		param->floor_color = NULL;
	}
	if (param->ceiling_color)
	{
		free(param->ceiling_color);
		param->ceiling_color = NULL;
	}
	free(param);
	param = NULL;
}

static void	free_param(t_param *param)
{
	if (param->no)
	{
		free(param->no);
		param->no = NULL;
	}
	if (param->so)
	{
		free(param->so);
		param->so = NULL;
	}
	if (param->we)
	{
		free(param->we);
		param->we = NULL;
	}
	if (param->ea)
	{
		free(param->ea);
		param->ea = NULL;
	}
	free_param2(param);
}

static void	free_pics(t_game *game)
{
	if (game->pics->wall_n)
	{
		mlx_destroy_image(game->mlx, game->pics->wall_n->img);
		free(game->pics->wall_n);
		game->pics->wall_n = NULL;
	}
	if (game->pics->wall_s)
	{
		mlx_destroy_image(game->mlx, game->pics->wall_s->img);
		free(game->pics->wall_s);
		game->pics->wall_s = NULL;
	}
	if (game->pics->wall_w)
	{
		mlx_destroy_image(game->mlx, game->pics->wall_w->img);
		free(game->pics->wall_w);
		game->pics->wall_w = NULL;
	}
	if (game->pics->wall_e)
	{
		mlx_destroy_image(game->mlx, game->pics->wall_e->img);
		free(game->pics->wall_e);
		game->pics->wall_e = NULL;
	}
	free(game->pics);
}

void	free_all(t_game *game)
{
	if (game->map_file)
		ft_free_tab(game->map_file);
	if (game->map)
		ft_free_tab(game->map);
	if (game->check_map)
		ft_free_tab(game->check_map);
	if (game->pics)
	{
		free_pics(game);
		game->pics = NULL;
	}
	if (game->param)
		free_param(game->param);
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

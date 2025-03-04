/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:59:04 by saberton          #+#    #+#             */
/*   Updated: 2025/03/04 17:08:50 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel_to_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static int	get_pixel_color(t_img *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x > 48 || y < 0 || y > 48)
		return (0xFFFFFF);
	pixel = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	return (*(unsigned int *)pixel);
}

static void	draw_wall_column(t_game *game, int col, t_player *pic)
{
	int	start;
	int	end;
	int	y;
	int	color;

	start = (HEIGHT - game->ray.lineheight) / 2;
	if (start < 0)
		start = 0;
	end = (HEIGHT + game->ray.lineheight) / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	y = 0;
	while (y < start)
		put_pixel_to_img(&game->img, col, y++, game->param->c_colors.dec);
	game->ray.text_step = 48.0 / game->ray.lineheight;
	game->ray.text_pos = (start - HEIGHT / 2 + game->ray.lineheight / 2)
		* game->ray.text_step;
	while (y <= end)
	{
		pic->y = (int)game->ray.text_pos;
		color = get_pixel_color(game->choice_pic, pic->x, pic->y);
		put_pixel_to_img(&game->img, col, y++, color);
		game->ray.text_pos += game->ray.text_step;
	}
	while (y < HEIGHT - 1)
		put_pixel_to_img(&game->img, col, y++, game->param->f_colors.dec);
}

void	init_data_pic(t_game *game, int x, float ray_angle)
{
	game->ray.camera = 2 * x / (double)WIDTH - 1;
	game->ray.ray_dir.x = cos(ray_angle);
	game->ray.ray_dir.y = sin(ray_angle);
	game->ray.player = (t_player){(int)game->player.x, (int)game->player.y};
	game->ray.delta.x = fabs(1 / game->ray.ray_dir.x);
	game->ray.delta.y = fabs(1 / game->ray.ray_dir.y);
	if (game->ray.ray_dir.x < 0)
	{
		game->ray.step.x = -1;
		game->ray.side_dist.x = (game->player.x - game->ray.player.x)
			* game->ray.delta.x;
	}
	else
	{
		game->ray.step.x = 1;
		game->ray.side_dist.x = ((game->ray.player.x + 1.0) - game->player.x)
			* game->ray.delta.x;
	}
	if (game->ray.ray_dir.y < 0)
	{
		game->ray.step.y = -1;
		game->ray.side_dist.y = (game->player.y - game->ray.player.y)
			* game->ray.delta.y;
	}
	else
	{
		game->ray.step.y = 1;
		game->ray.side_dist.y = ((game->ray.player.y + 1.0) - game->player.y)
			* game->ray.delta.y;
	}
}

static t_img	*choice_pic(t_game *game, t_player *pic)
{
	if (game->side == 0)
	{
		game->ray.perpwalldist = (game->ray.player.x - game->player.x + (1
					- game->ray.step.x) / 2) / game->ray.ray_dir.x;
		pic->x = game->player.y + game->ray.perpwalldist * game->ray.ray_dir.y;
		if (game->ray.ray_dir.x > 0)
			return (game->pics->wall_w);
		else
			return (game->pics->wall_e);
	}
	else
	{
		game->ray.perpwalldist = (game->ray.player.y - game->player.y + (1
					- game->ray.step.y) / 2) / game->ray.ray_dir.y;
		pic->x = game->player.x + game->ray.perpwalldist * game->ray.ray_dir.x;
		if (game->ray.ray_dir.y > 0)
			return (game->pics->wall_n);
		else
			return (game->pics->wall_s);
	}
}

void	dda_loop(t_game *game)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (game->ray.side_dist.x < game->ray.side_dist.y)
		{
			game->ray.side_dist.x += game->ray.delta.x;
			game->ray.player.x += game->ray.step.x;
			game->ray.side = 0;
			game->side = 0;
		}
		else
		{
			game->ray.side_dist.y += game->ray.delta.y;
			game->ray.player.y += game->ray.step.y;
			game->ray.side = 1;
			game->side = 1;
		}
		if (game->map[(int)game->ray.player.y][(int)game->ray.player.x] == '1')
			hit = 1;
	}
}

void	put_img(t_game *game)
{
	int			col;
	float		angle_step;
	float		angle_start;
	t_player	pic;
	t_ray		ray;
	float		ray_angle;

	col = 0;
	angle_step = (M_PI / 3) / WIDTH;
	angle_start = (float)game->angle - (M_PI / 6);
	ft_bzero(&pic, sizeof(t_player));
	while (col < WIDTH)
	{
		ray_angle = angle_start + col * angle_step;
		ft_bzero(&ray, sizeof(t_ray));
		ft_bzero(&pic, sizeof(t_player));
		init_data_pic(game, col, ray_angle);
		dda_loop(game);
		game->choice_pic = choice_pic(game, &pic);
		pic.x = (int)((pic.x - floor(pic.x))
				* (double)game->choice_pic->w_width);
		game->ray.lineheight = (int)(HEIGHT / (game->ray.perpwalldist));
		draw_wall_column(game, col, &pic);
		col++;
	}
}

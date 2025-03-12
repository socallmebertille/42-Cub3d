/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_barrier_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:35:19 by memotyle          #+#    #+#             */
/*   Updated: 2025/03/12 17:41:49 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	wich_door(t_game *game, int x, int y)
{
	int	count;

	count = 0;
	while (count < game->barrier_nb)
	{
		if (x == (int)game->door[count].pos.x
			&& y == (int)game->door[count].pos.y)
			return (game->door[count].id);
		count++;
	}
	return (-1);
}

static t_img	*choice_pic(t_game *game, t_player *pic)
{
	int	id;

	if (game->ray.side == 0)
	{
		game->ray.perpwalldist = (game->ray.map.x - game->player.x + (1
					- game->ray.step.x) / 2) / game->ray.ray_dir.x;
		pic->x = game->player.y + game->ray.perpwalldist * game->ray.ray_dir.y;
	}
	else
	{
		game->ray.perpwalldist = (game->ray.map.y - game->player.y + (1
					- game->ray.step.y) / 2) / game->ray.ray_dir.y;
		pic->x = game->player.x + game->ray.perpwalldist * game->ray.ray_dir.x;
	}
	id = wich_door(game, (int)game->ray.map.x, (int)game->ray.map.y);
	if (game->door[id].barrier_o_c == 0 && id != -1)
		return (game->pics->bar_close);
	else if (game->door[id].barrier_o_c == 1 && id != -1)
		return (game->pics->bar_semiopen);
	else if (game->door[id].barrier_o_c == 2 && id != -1)
		return (game->pics->bar_opopen);
	else if (game->door[id].barrier_o_c == 3 && id != -1)
		return (game->pics->bar_open);
	return (NULL);
}

static void	wall_or_door(t_game *game, t_player *pic)
{
	char	c;
	int		hit;

	hit = 0;
	while (!hit)
	{
		if (game->ray.side_dist.x < game->ray.side_dist.y)
		{
			game->ray.side_dist.x += game->ray.delta.x;
			game->ray.map.x += game->ray.step.x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_dist.y += game->ray.delta.y;
			game->ray.map.y += game->ray.step.y;
			game->ray.side = 1;
		}
		c = game->map[(int)game->ray.map.y][(int)game->ray.map.x];
		if (c == '1' || c == 'D')
			hit = 1;
	}
	if (c == 'D')
	{
		game->choice_pic = choice_pic(game, pic);
		game->ray.text_step = (float)game->choice_pic->h / game->ray.lineheight;
	}
	else
		game->choice_pic = NULL;
}

static void	draw_column(t_game *game, int col, t_player *pic)
{
	int	start;
	int	end;
	int	y;
	int	color;

	start = (game->win_height - game->ray.lineheight) / 2;
	if (start < 0)
		start = 0;
	end = (game->win_height + game->ray.lineheight) / 2;
	if (end >= game->win_height)
		end = game->win_height - 1;
	y = 0;
	while (y < start)
		y++;
	game->ray.text_step = (float)game->choice_pic->h / game->ray.lineheight;
	game->ray.text_pos = (start - game->win_height / 2 + game->ray.lineheight
			/ 2) * game->ray.text_step;
	while (y <= end)
	{
		pic->y = (int)game->ray.text_pos;
		color = get_pixel_color(game->choice_pic, pic->x, pic->y);
		if ((color & 0x00FFFFFF) != 0)
			put_pixel_to_img(game, col, y, color);
		y++;
		game->ray.text_pos += game->ray.text_step;
	}
	while (y < game->win_height - 1)
		y++;
}

void	put_img_door(t_game *game, float angle_step, float angle_start)
{
	int			col;
	float		ray_angle;
	t_player	pic;
	t_ray		ray;

	col = 0;
	while (col < game->win_width)
	{
		ray_angle = angle_start + col * angle_step;
		ft_bzero(&ray, sizeof(t_ray));
		ft_bzero(&pic, sizeof(t_player));
		game->ray.camera = 2 * col / (double)game->win_width - 1;
		game->ray.delta.x = fabs(1 / game->ray.ray_dir.x);
		game->ray.delta.y = fabs(1 / game->ray.ray_dir.y);
		game->ray.ray_dir = (t_player){cos(ray_angle), sin(ray_angle)};
		game->ray.map = (t_player){(int)game->player.x, (int)game->player.y};
		init_ray(game);
		game->ray.lineheight = (int)(game->win_height
				/ (game->ray.perpwalldist));
		wall_or_door(game, &pic);
		if (game->choice_pic)
		{
			pic.x = (int)((pic.x - floor(pic.x)) * (double)game->choice_pic->w);
			draw_column(game, col, &pic);
		}
		col++;
	}
}

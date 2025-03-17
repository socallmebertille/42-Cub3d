/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:37:53 by bertille          #+#    #+#             */
/*   Updated: 2025/03/04 17:04:29 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	intern_step(char *tmp, int color, t_colors *colors)
{
	if (!tmp)
		return (write_err(RED MALLOC RESET), 1);
	if (color == 1 && tmp[0])
		colors->r = ft_atol(tmp);
	else if (color == 2 && tmp[0])
		colors->g = ft_atol(tmp);
	else if (color == 3 && tmp[0])
		colors->b = ft_atol(tmp);
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	return (0);
}

static int	give_me_map_value(char *to_split, t_colors *colors)
{
	int	i;
	int	end;
	int	start;
	int	c;

	c = 0;
	i = -1;
	end = 0;
	start = 0;
	while (to_split[++i])
	{
		if (to_split[i] != ',' && to_split[i] != '\0')
			continue ;
		c++;
		end = i - start;
		if (intern_step(ft_substr(to_split, start, end), c, colors))
			return (1);
		start = i + 1;
	}
	if (c == 2 && intern_step(ft_substr(to_split, start, i - start), 3, colors))
		return (1);
	c++;
	if (c != 3 || colors->r == -1 || colors->g == -1 || colors->b == -1)
		return (write_err(RED "Error\nWrong format of colors\n" RESET), 1);
	return (0);
}

static void	init_rgb(t_colors *colors)
{
	colors->r = -1;
	colors->g = -1;
	colors->b = -1;
	colors->dec = -1;
}

int	check_value(t_game *game, t_param *param)
{
	init_rgb(&param->c_colors);
	init_rgb(&param->f_colors);
	if (give_me_map_value(param->ceiling_color, &param->c_colors)
		|| give_me_map_value(param->floor_color, &param->f_colors))
		return (1);
	if (param->f_colors.r > 255 || param->f_colors.r < 0
		|| param->f_colors.g > 255 || param->f_colors.g < 0
		|| param->f_colors.b > 255 || param->f_colors.b < 0)
		return (write_err(RED "Error\nFloor color isn't a valid one\n" RESET),
			1);
	if (param->c_colors.r < 0 || param->c_colors.r > 255
		|| param->c_colors.g < 0 || param->c_colors.g > 255
		|| param->c_colors.b < 0 || param->c_colors.b > 255)
		return (write_err(RED "Error\nCeiling color isn't a valid one\n" RESET),
			1);
	param->c_colors.dec = create_rgb(game, param->c_colors.r, param->c_colors.g,
			param->c_colors.b);
	param->f_colors.dec = create_rgb(game, param->f_colors.r, param->f_colors.g,
			param->f_colors.b);
	if (param->c_colors.dec == -1 || param->f_colors.dec == -1)
		return (write_err("Error\nIssue when converting rgb to decimal\n"), 1);
	return (0);
}

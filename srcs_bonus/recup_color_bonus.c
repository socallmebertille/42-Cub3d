/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_color_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:34:54 by bertille          #+#    #+#             */
/*   Updated: 2025/03/10 18:31:53 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	check_colors(t_game *game, t_param *param)
{
	int	i;

	i = 0;
	while (param->ceiling_color[i] == ' ')
		i++;
	while (param->ceiling_color[i])
	{
		if (!ft_isdigit(param->ceiling_color[i])
			&& param->ceiling_color[i] != ',')
			return (write_err(RED "Error\nProblem with ceiling color\n" RESET),
				1);
		i++;
	}
	i = 0;
	while (param->floor_color[i] == ' ')
		i++;
	while (param->floor_color[i])
	{
		if (!ft_isdigit(param->floor_color[i])
			&& param->floor_color[i] != ',')
			return (write_err(RED "Error\nProblem with floor color\n" RESET), 1);
		i++;
	}
	return (check_value(game, param));
}

static int	get_color(int letter, char *str, t_param *param)
{
	if (letter == 1 && !param->floor_color)
	{
		param->floor_color = ft_substr(str, 2, ft_strlen(str) - 2);
		if (!param->floor_color)
			return (0);
	}
	if (letter == 2 && !param->ceiling_color)
	{
		param->ceiling_color = ft_substr(str, 2, ft_strlen(str) - 2);
		if (!param->floor_color)
			return (0);
	}
	return (1);
}

int	map_color(t_game *game, t_param *param)
{
	int	f;
	int	c;
	int	i;

	i = 0;
	f = 0;
	c = 0;
	while (game->map_file[i])
	{
		if (!ft_strncmp(game->map_file[i], "F ", 2))
			f += get_color(1, game->map_file[i], param);
		else if (!ft_strncmp(game->map_file[i], "C ", 2))
			c += get_color(2, game->map_file[i], param);
		i++;
	}
	if (!f || f > 1 || !param->floor_color)
		return (write_err(RED "Error\nChoose only one floor color\n" RESET), 1);
	if (!c || c > 1 || !param->ceiling_color)
		return (write_err(RED "Error\nChoose only one ceiling color\n" RESET), 1);
	return (check_colors(game, param));
}

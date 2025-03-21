/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_parse_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:22:12 by kepouliq          #+#    #+#             */
/*   Updated: 2025/03/14 14:06:52 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	map_parse(char **file, t_game *game)
{
	if (recup_map(file, game) || check_char(game->map, game)
		|| flood_fill_check(game))
		return (1);
	return (0);
}

void	map_file_parse(t_game *game)
{
	t_param	*param;

	param = malloc(sizeof(t_param));
	if (!param)
	{
		write_err(RED MALLOC RESET);
		quite_game(game);
	}
	ft_bzero(param, sizeof(t_param));
	game->param = param;
	if (map_texture(game, game->param) || map_texture2(game, game->param)
		|| path_texture(game->param) || map_color(game, game->param)
		|| map_parse(game->map_file, game))
	{
		free_all(game);
		exit(1);
	}
}

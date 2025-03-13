/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinaaam <melinaaam@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:23:14 by saberton          #+#    #+#             */
/*   Updated: 2025/03/13 15:37:34 by melinaaam        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	malloc_map(char **file, t_game *game)
{
	int	i;
	int	len;

	i = 0;
	while (file[i] && !ft_find_others(file[i], "1 "))
		i++;
	len = 0;
	while (file[i + len])
	{
		if ((int)ft_strlen(file[i + len]) > MAX_MAP_WIDTH
			|| len > MAX_MAP_HEIGHT)
			return (write_err(RED "Error\nMap too tall (max 100)\n" RESET));
		if ((int)ft_strlen(file[i + len]) == ft_count_chars(file[i + len],
				"\n\0\t\r\f\v "))
			break ;
		len++;
	}
	game->map = (char **)malloc(sizeof(char *) * (len + 1));
	if (!game->map)
		write_err(RED MALLOC RESET);
	game->check_map = (char **)malloc(sizeof(char *) * (len + 1));
	if (!game->check_map)
		write_err(RED MALLOC RESET);
}

int	recup_map(char **file, t_game *game)
{
	int	i;
	int	len;

	malloc_map(file, game);
	if (!game->map || !game->check_map)
		return (1);
	i = 0;
	while (file[i] && !ft_find_others(file[i], "1 "))
		i++;
	len = 0;
	while (file[i + len])
	{
		if ((int)ft_strlen(file[i + len]) == ft_count_chars(file[i + len],
				"\n\0\t\r\f\v "))
			break ;
		game->map[len] = ft_strdup(file[i + len]);
		game->check_map[len] = ft_strdup(file[i + len]);
		if (!game->map[len] || !game->check_map[len])
			return (write_err(RED MALLOC RESET), 1);
		len++;
	}
	game->map[len] = NULL;
	game->check_map[len] = NULL;
	return (0);
}

static void	recup_player(char *map, t_game *game, int y)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] == 'N' || map[i] == 'S' || map[i] == 'W' || map[i] == 'E')
		{
			game->player.y = y + 0.5;
			game->player.x = i + 0.5;
			if (map[i] == 'N')
				game->degree = 270;
			else if (map[i] == 'S')
				game->degree = 90;
			else if (map[i] == 'W')
				game->degree = 180;
			else if (map[i] == 'E')
				game->degree = 0;
			game->angle = (float)game->degree * M_PI / 180.0;
			game->angle -= (0 - (2 * M_PI));
			break ;
		}
		i++;
	}
}

static void	recup_door(char **map, t_game *game)
{
	int	i;
	int	j;
	int	count;

	if (!game->door)
		return (write_err(RED MALLOC RESET));
	ft_bzero(game->door, sizeof(t_door) * game->barrier_nb);
	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D')
			{
				game->door[count].pos.y = i;
				game->door[count].pos.x = j;
				game->door[count].id = count;
				count++;
			}
			j++;
		}
		i++;
	}
}

int	check_char(char **map, t_game *game)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (map[++i])
	{
		recup_player(map[i], game, i);
		if (!ft_find_others(map[i], "01 NSEWD"))
			return (write_err(RED WRONG_CHAR RESET), 1);
		count += ft_count_chars(map[i], "NSEW");
	}
	if (count < 1)
		return (write_err(RED "Error\nA player is missing in map\n" RESET), 1);
	if (count > 1)
		return (write_err(RED "Error\nToo many players in map\n" RESET), 1);
	i = 0;
	while (map[i])
		game->barrier_nb += ft_count_chars(map[i++], "D");
	if (game->barrier_nb)
	{
		game->door = malloc(sizeof(t_door) * (game->barrier_nb));
		if (!game->door)
			return (write_err(RED MALLOC RESET), 1);
		recup_door(map, game);
		if (door_surrounded(game))
			return (1);
	}
	return (0);
}

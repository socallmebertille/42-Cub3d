/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barrier_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinaaam <melinaaam@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:57:42 by memotyle          #+#    #+#             */
/*   Updated: 2025/03/13 15:21:33 by melinaaam        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// static void	counter(t_game *game, int id)
// {
// 	int	count;

// 	count = 0;
// 	while (count < 50)
// 		count++;
// 	// if (open == 1)
// 	// 	game->door[id].barrier_o_c++;
// 	// else if (!open)
// 	// 	game->door[id].barrier_o_c--;
// }

void	toggle_barrier(t_game *game, int x, int y)
{
	int	id;

	id = wich_door(game, x, y);
	if (!game->barrier_open || id == -1)
		return ;
	if (game->door[id].barrier_o_c == 0)
		game->door[id].step = 1;
	else if (game->door[id].barrier_o_c == 3)
		game->door[id].step = 0;
	if (game->door[id].barrier_o_c < 3 && game->door[id].step)
	{
		usleep(50000);
		game->door[id].barrier_o_c++;
		if (game->door[id].barrier_o_c == 3)
			game->barrier_open = 0;
	}
	else if (game->door[id].barrier_o_c > 0)
	{
		usleep(50000);
		game->door[id].barrier_o_c--;
		if (game->door[id].barrier_o_c == 0)
			game->barrier_open = 0;
	}
}

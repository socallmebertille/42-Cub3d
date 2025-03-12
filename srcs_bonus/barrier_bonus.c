/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barrier_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:57:42 by memotyle          #+#    #+#             */
/*   Updated: 2025/03/12 17:39:33 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	toggle_barrier(t_game *game, int x, int y)
{
	int	id;

	id = wich_door(game, x, y);
	if (!game->barrier_open || id == -1)
		return ;
	if (game->door[id].barrier_o_c == 0)
		game->door[id].barrier_o_c = 1;
	else if (game->door[id].barrier_o_c == 1)
		game->door[id].barrier_o_c = 2;
	else if (game->door[id].barrier_o_c == 2)
		game->door[id].barrier_o_c = 3;
	else
		game->door[id].barrier_o_c = 0;
	game->barrier_open = 0;
}

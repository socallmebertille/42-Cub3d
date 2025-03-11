/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:19:48 by saberton          #+#    #+#             */
/*   Updated: 2025/03/11 11:44:19 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int get_mouse_position(t_game *game, int *x, int *y)
{
	
}
int mouse_move(t_game *game)
{
    int x, y;
	if (get_mouse_position(game, &x, &y))
		printf("Position de la souris : %d, %d\n", x, y);
	else
		printf("Erreur lors de la récupération de la position du curseur\n");
    return (0);
}
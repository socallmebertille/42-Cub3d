/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barrier_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:57:42 by memotyle          #+#    #+#             */
/*   Updated: 2025/03/10 18:14:35 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void draw_barrier_state(t_game *game, int screen_x, int screen_y)
{
    t_img  *tex;

    if (game->barrier_o_c == 0)
        tex = game->pics->bar_close;
    else if (game->barrier_o_c == 1)
        tex = game->pics->bar_semiopen;
    else if (game->barrier_o_c == 2)
        tex = game->pics->bar_opopen;
    else
        tex = game->pics->bar_open;

    // On parcourt les pixels de la texture
    int y = 0;
    while (y < tex->w_height)
    {
        int x = 0;
        while (x < tex->w_width)
        {
            int color = get_pixel_color(tex, x, y);
            if ((color & 0x00FFFFFF) != 0xFF00FF)
                put_pixel_to_img(game, screen_x + x, screen_y + y, color);
            x++;
        }
        y++;
    }
}

void toggle_barrier(t_game *game)
{
    if (game->barrier_o_c == 0)
        game->barrier_o_c = 1;
    else if (game->barrier_o_c == 1)
        game->barrier_o_c = 2;
    else if (game->barrier_o_c == 2)
        game->barrier_o_c = 3;
    else
        game->barrier_o_c = 0;
}


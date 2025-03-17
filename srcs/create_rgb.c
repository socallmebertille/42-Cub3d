/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:48:42 by saberton          #+#    #+#             */
/*   Updated: 2025/03/04 17:04:33 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*recup_color(t_game *game, int color, char *concate, int step)
{
	char	*tmp;
	char	*c;

	c = ft_itoa(color);
	if (!c)
		return (write_err(MALLOC), free_all(game), exit(1),
			NULL);
	tmp = ft_convert_base(c, "0123456789", "0123456789abcdef");
	if (!tmp)
		return (write_err(MALLOC), free(c), free_all(game),
			exit(1), NULL);
	if (step == 1)
		return (free(c), tmp);
	free(c);
	c = ft_strjoin(concate, tmp);
	if (!c)
		return (write_err(MALLOC), free(concate), free(tmp),
			free_all(game), exit(1), NULL);
	free(concate);
	free(tmp);
	return (c);
}

int	create_rgb(t_game *game, int r, int g, int b)
{
	char	*res;
	int		color;

	res = NULL;
	res = recup_color(game, r, res, 1);
	res = recup_color(game, g, res, 2);
	res = recup_color(game, b, res, 3);
	color = ft_atoi_base(res, "0123456789abcdef");
	free(res);
	return (color);
}

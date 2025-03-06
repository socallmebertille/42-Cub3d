/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertille <bertille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:33:20 by kepouliq          #+#    #+#             */
/*   Updated: 2025/03/05 17:09:54 by bertille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_pixel_to_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel_color(t_img *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x > 48 || y < 0 || y > 48)
		return (0xFFFFFF);
	pixel = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	return (*(unsigned int *)pixel);
}

void	write_err(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

char	*substring_until_char(const char *str, char delimiter)
{
	int		length;
	char	*pos;
	char	*result;

	pos = ft_strchr(str, delimiter);
	if (pos == NULL)
		return (ft_strdup(str));
	length = pos - str;
	result = malloc(length + 1);
	ft_strncpy(result, str, length);
	result[length] = '\0';
	return (result);
}

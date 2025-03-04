/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:33:20 by kepouliq          #+#    #+#             */
/*   Updated: 2025/01/24 16:43:25 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

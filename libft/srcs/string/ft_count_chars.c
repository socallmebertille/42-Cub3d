/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:20:37 by saberton          #+#    #+#             */
/*   Updated: 2025/01/24 15:34:22 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_chars(char *str, char *c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		j = 0;
		while (c[j])
		{
			if (str[i] == c[j])
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

// count how many times we find each character
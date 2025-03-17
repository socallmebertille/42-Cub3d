/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:06:18 by saberton          #+#    #+#             */
/*   Updated: 2025/01/24 15:10:02 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_others(char *str, char *c)
{
	int	i;
	int	j;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		j = 0;
		while (c[j])
		{
			if (str[i] == c[j])
				break ;
			j++;
		}
		if (!c[j])
			return (0);
		i++;
	}
	return (1);
}

//to find if there are others characters than the one in c string
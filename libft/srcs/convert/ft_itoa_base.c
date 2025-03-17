/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:39:40 by saberton          #+#    #+#             */
/*   Updated: 2025/02/10 11:40:04 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_itoa_base(long nb, char *base_to, char *str, int i)
{
	int	len;

	len = ft_conf_base(base_to);
	if (nb < 0)
	{
		str[i] = '-';
		i++;
		nb = -nb;
	}
	if (nb < len)
	{
		str[i] = base_to[nb];
		str[i + 1] = '\0';
	}
	else
	{
		ft_itoa_base(nb / len, base_to, str, i);
		ft_itoa_base(nb % len, base_to, str, ft_strlen(str));
	}
}

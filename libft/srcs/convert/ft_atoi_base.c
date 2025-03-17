/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:39:44 by saberton          #+#    #+#             */
/*   Updated: 2025/02/10 11:40:31 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(char *nbr, char *base_from)
{
	int		i;
	int		len;
	long	sign;
	long	nb;

	i = 0;
	while (nbr[i] == ' ' || (nbr[i] >= '\t' && nbr[i] <= '\r'))
		i++;
	sign = 1;
	while (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			sign *= (-1);
		i++;
	}
	len = ft_conf_base(base_from);
	if (len == 0 || ft_conf_str(nbr, base_from, i) == 0)
		return (0);
	nb = ft_nbr(nbr, base_from, i, len);
	return (sign * nb);
}

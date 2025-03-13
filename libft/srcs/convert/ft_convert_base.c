/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinaaam <melinaaam@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:37:44 by saberton          #+#    #+#             */
/*   Updated: 2025/03/13 11:33:52 by melinaaam        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbr(char *nbr, char *base, int i, int len)
{
	long	nb;
	int		j;

	nb = 0;
	j = 0;
	while (base[j])
	{
		if (nbr[i] == base[j])
		{
			nb *= len;
			nb += j;
			i++;
			j = -1;
		}
		j++;
	}
	return (nb);
}

int	ft_conf_base(char *base)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		j = 0;
		while (base[j])
		{
			if (base[i] == base[j])
				count += 1;
			j++;
		}
		i++;
	}
	if (count != i)
		return (0);
	if (i < 2)
		return (0);
	return (i);
}

int	ft_conf_str(char *str, char *base, int i)
{
	int	j;
	int	count;

	count = i;
	while (str[i])
	{
		j = 0;
		while (base[j])
		{
			if (str[i] == base[j])
				count += 1;
			j++;
		}
		i++;
	}
	if (count != i)
		return (0);
	return (1);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	long	nb;
	char	*res;

	res = (char *)malloc(32 * sizeof(char));
	if (ft_conf_base(base_from) == 0 || ft_conf_base(base_to) == 0)
	{
		res = NULL;
		return (res);
	}
	if (res == NULL)
		return (NULL);
	nb = ft_atoi_base(nbr, base_from);
	ft_itoa_base(nb, base_to, res, 0);
	return (res);
}

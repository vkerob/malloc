/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkerob <vkerob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:33:52 by vkerob            #+#    #+#             */
/*   Updated: 2022/11/06 17:47:30 by vkerob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lenn(long int n)
{
	long int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	n = n / 10;
	len++;
	return (len);
}

static int	sign(long int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	nb;
	int			i;

	nb = n;
	i = ft_lenn(n);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (sign(nb))
	{
		str[0] = '-';
		nb = -nb;
	}
	str[i] = '\0';
	i--;
	while (nb > 9)
	{
		str[i] = (nb % 10) + 48;
		nb = nb / 10;
		i--;
	}
	str[i] = (nb % 10) + 48;
	return (str);
}

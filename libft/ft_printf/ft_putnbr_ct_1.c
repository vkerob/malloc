/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ct_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkerob <vkerob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:23:21 by vkerob            #+#    #+#             */
/*   Updated: 2022/11/14 12:47:57 by vkerob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	ft_putnbr_ct_1(long nbr, char *base)
{
	int	len_base;
	int	ct;

	ct = 0;
	len_base = ft_strlen(base);
	if (nbr < 0)
	{
		ct += ft_putchar_ct('-');
		nbr = -nbr;
	}
	if (nbr < len_base)
		ct += ft_putchar_ct(base[nbr % len_base]);
	else
	{
		ct += ft_putnbr_ct_1(nbr / len_base, base);
		ct += ft_putchar_ct(base[nbr % len_base]);
	}
	return (ct);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adress.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkerob <vkerob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:20:11 by vkerob            #+#    #+#             */
/*   Updated: 2022/11/22 13:37:06 by vkerob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

static int	ft_putnbr_lunsigned_base_ct(unsigned long nbr, char *base)
{
	unsigned int	len_base;
	int				ct;

	ct = 0;
	len_base = ft_strlen(base);
	if (nbr < len_base)
		ct += ft_putchar_ct(base[nbr]);
	else
	{
		ct += ft_putnbr_lunsigned_base_ct(nbr / len_base, base);
		ct += ft_putchar_ct(base[nbr % len_base]);
	}
	return (ct);
}

int	ft_adress(unsigned long nbr)
{
	int	ct;

	ct = 0;
	if (nbr == 0)
	{
		ct += ft_putstr_ct("(nil)");
		return (5);
	}
	ct += ft_putstr_ct("0x");
	ct += ft_putnbr_lunsigned_base_ct(nbr, "0123456789abcdef");
	return (ct);
}

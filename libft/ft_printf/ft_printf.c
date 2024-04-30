/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neweth <neweth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:12:19 by vkerob            #+#    #+#             */
/*   Updated: 2022/12/06 22:32:53 by neweth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

static int	ft_forest(char c2, va_list va)
{
	int	ct;

	ct = 0;
	if (c2 == 'c')
		ct += ft_putchar_ct((char)va_arg(va, int));
	else if (c2 == 's')
		ct += ft_putstr_ct((char *)va_arg(va, char *));
	else if (c2 == 'p')
		ct += ft_adress(va_arg(va, unsigned long));
	else if (c2 == 'd' || c2 == 'i')
		ct += ft_putnbr_ct_1((long)va_arg(va, int), "0123456789");
	else if (c2 == 'u')
		ct += ft_putnbr_ct_2((unsigned)va_arg(va, int), "0123456789");
	else if (c2 == 'x')
		ct += ft_putnbr_ct_2((unsigned)va_arg(va, int), "0123456789abcdef");
	else if (c2 == 'X')
		ct += ft_putnbr_ct_2((unsigned)va_arg(va, int), "0123456789ABCDEF");
	else if (c2 == '%')
		ct += ft_putchar_ct('%');
	return (ct);
}

int	ft_check(char c)
{
	if (c == 'c' || c == 's' || c == 'd' || c == 'i')
		return (1);
	if (c == 'u' || c == 'p' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int	ft_parcours(const char *s, va_list va)
{
	int	i;
	int	ct;

	i = 0;
	ct = 0;
	while (s[i])
	{
		if (s[i] == '%' && ft_check(s[i + 1]) == 1)
		{
			ct += ft_forest(s[i + 1], va);
			i++;
		}
		else
			ct += ft_putchar_ct(s[i]);
		i++;
	}
	return (ct);
}

int	ft_printf(const char *s, ...)
{
	va_list	va;
	int		ct;

	ct = 0;
	if (!s)
		return (-1);
	va_start (va, s);
	ct = ft_parcours(s, va);
	va_end (va);
	return (ct);
}

/*
#include<stdio.h>

int	main(void)
{
	printf("%d\n", ft_printf("je test d'ecrire%"));
}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkerob <vkerob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:29:34 by vkerob            #+#    #+#             */
/*   Updated: 2022/11/09 16:18:33 by vkerob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	c2;
	size_t			i;

	i = 0;
	c2 = (unsigned char) c;
	str = (unsigned char *) s;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (str[i] == c2)
			return ((char *) &str[i]);
		i++;
	}
	return (NULL);
}

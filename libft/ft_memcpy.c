/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkerob <vkerob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:46:17 by vkerob            #+#    #+#             */
/*   Updated: 2022/11/06 17:47:43 by vkerob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*s1;
	char		*s2;

	if (!dest && !src)
		return (dest);
	i = 0;
	s1 = (const char *) src;
	s2 = (char *) dest;
	while (i != n)
	{
		*s2 = *s1;
		s2++;
		s1++;
		i++;
	}
	return (dest);
}

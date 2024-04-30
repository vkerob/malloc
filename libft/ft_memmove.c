/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkerob <vkerob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:08:09 by vkerob            #+#    #+#             */
/*   Updated: 2022/11/06 17:47:44 by vkerob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dest1;
	char		*src1;

	if (!dest && !src && n != 0)
		return (NULL);
	i = 0;
	dest1 = (char *) dest;
	src1 = (char *) src;
	if (n == 0)
		return (dest);
	if (src < dest)
	{
		while (n > 0)
		{
			n--;
			dest1[n] = src1[n];
		}
	}
	while (i < n)
	{
		dest1[i] = src1[i];
		i++;
	}
	return (dest);
}

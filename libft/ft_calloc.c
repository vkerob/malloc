/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkerob <vkerob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 08:45:12 by vkerob            #+#    #+#             */
/*   Updated: 2022/11/21 08:45:15 by vkerob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t nmenb, size_t size)
{
	char	*str;
	size_t	i;

	if (nmenb == 0)
	{
		str = malloc(0);
		if (!str)
			return (NULL);
		return (str);
	}
	if (nmenb * size / nmenb != size)
		return (NULL);
	i = 0;
	str = malloc(nmenb * size);
	if (!str)
		return (0);
	while (i < nmenb * size)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkerob <vkerob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:50:49 by vkerob            #+#    #+#             */
/*   Updated: 2022/11/06 17:48:02 by vkerob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	c2;

	c2 = (unsigned char) c;
	i = ft_strlen(s);
	if (s[i] == c2)
		return ((char *) &s[i]);
	while (i > 0)
	{
		i--;
		if (s[i] == c2)
			return ((char *) &s[i]);
	}
	return (NULL);
}

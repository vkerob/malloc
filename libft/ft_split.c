/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkerob <vkerob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:19:42 by neweth            #+#    #+#             */
/*   Updated: 2022/11/06 17:47:50 by vkerob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static void	ft_clear(char **array, int k)
{
	while (k > 0)
	{
		free(array[k]);
		k--;
	}
	free(array);
}

static int	ft_nbstr(const char *s, char c)
{
	int		i;
	int		ct;

	i = 0;
	ct = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			ct++;
		while (s[i] != c && s[i])
			i++;
	}
	return (ct);
}

static void	ft_make_str(char const *s, char c, char **array, int k)
{
	int		i;
	int		start;
	int		len;

	i = 0;
	while (k < ft_nbstr(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		len = 0;
		while (s[i] != c && s[i])
		{
			len++;
			i++;
		}
		array[k] = ft_substr(s, start, len);
		if (!array[k])
		{
			ft_clear(array, k);
			return ;
		}
		k++;
	}
	return ;
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		k;

	if (!s)
		return (NULL);
	k = ft_nbstr(s, c);
	array = malloc((k + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array[k] = NULL;
	ft_make_str(s, c, array, 0);
	return (array);
}

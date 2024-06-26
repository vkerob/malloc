/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkerob <vkerob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:06:13 by neweth            #+#    #+#             */
/*   Updated: 2022/11/06 17:47:40 by vkerob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_lstsize(t_list *lst)
{
	int	ct;

	if (!lst)
		return (0);
	ct = 0;
	while (lst != NULL)
	{
		ct++;
		lst = lst->next;
	}
	return (ct);
}

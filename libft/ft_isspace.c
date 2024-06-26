/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkerob <vkerob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:16:41 by vkerob            #+#    #+#             */
/*   Updated: 2023/02/08 23:08:29 by vkerob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_ispace(int c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

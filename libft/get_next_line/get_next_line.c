/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkerob <vkerob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:14:40 by vkerob            #+#    #+#             */
/*   Updated: 2023/02/12 18:54:25 by vkerob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

static char	*join_and_free(char *buf, char *tmp)
{
	char	*buf_tmp;

	buf_tmp = ft_strjoin_gnl(buf, tmp);
	free(buf);
	return (buf_tmp);
}

static char	*read_and_stash_all_buffer(char *buf, int fd)
{
	char	*tmp;
	int		nb_c;

	if (!buf)
		buf = ft_calloc_gnl(1, sizeof(char));
	nb_c = 1;
	while (nb_c > 0 && !ft_strchr_gnl(buf, '\n'))
	{
		tmp = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
		if (!tmp)
			return (NULL);
		nb_c = read(fd, tmp, BUFFER_SIZE);
		if (nb_c < 0)
		{
			free(buf);
			free(tmp);
			return (NULL);
		}
		buf = join_and_free(buf, tmp);
		free(tmp);
	}
	return (buf);
}

static char	*stash_line(char *buf)
{
	char	*stash;
	int		i;

	i = 0;
	if (!buf[i])
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	stash = ft_calloc_gnl(i + 1, sizeof(char));
	if (!stash)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		stash[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		stash[i] = buf[i];
	return (stash);
}

static char	*new_buf(char *buf)
{
	char	*new_buf;
	int		i;
	int		j;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i])
	{
		free(buf);
		return (NULL);
	}
	new_buf = ft_calloc_gnl(ft_strlen_gnl(buf) - i + 1, sizeof(char));
	if (!new_buf)
		return (NULL);
	j = 0;
	i++;
	while (buf[i])
		new_buf[j++] = buf[i++];
	free(buf);
	return (new_buf);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*stash;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	buf = read_and_stash_all_buffer(buf, fd);
	if (!buf)
		return (NULL);
	stash = stash_line(buf);
	buf = new_buf(buf);
	if (!buf || buf[0] == '\0')
	{
		free(buf);
		buf = NULL;
	}
	return (stash);
}

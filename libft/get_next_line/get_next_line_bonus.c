/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkerob <vkerob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:14:40 by vkerob            #+#    #+#             */
/*   Updated: 2022/12/12 14:55:10 by vkerob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

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
	static char	*buf[1024];
	char		*stash;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	buf[fd] = read_and_stash_all_buffer(buf[fd], fd);
	if (!buf[fd])
		return (NULL);
	stash = stash_line(buf[fd]);
	buf[fd] = new_buf(buf[fd]);
	if (!buf[fd])
	{
		free(buf[fd]);
		buf[fd] = NULL;
	}
	return (stash);
}

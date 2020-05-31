/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cspare <cspare@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 23:33:33 by cspare            #+#    #+#             */
/*   Updated: 2020/03/08 23:34:02 by cspare           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_prep_line(t_fd *file, void *newline)
{
	int		offset;
	char	*ret;

	if (!file || !newline)
		return (NULL);
	offset = (char *)newline - file->buf;
	if (!(ret = ft_strsub(file->buf, 0, offset)))
		return (NULL);
	ft_memmove(file->buf, file->buf + offset + 1, file->buf_size - offset);
	file->bytes_read = file->bytes_read - offset - 1;
	ft_bzero(file->buf + file->bytes_read, file->buf_size - file->bytes_read);
	file->ret_flag = 1;
	return (ret);
}

static char		*ft_last_line(t_fd *file)
{
	char	*ret;

	if (!file)
		return (NULL);
	file->open_flag = 0;
	if (file->buf && ft_strlen(file->buf))
	{
		if (!(ret = ft_strsub(file->buf, 0, file->bytes_read)))
			return (NULL);
		ft_strdel(&(file->buf));
		file->ret_flag = 1;
		return (ret);
	}
	return (ft_strnew(1));
}

static t_fd		*ft_realloc(t_fd *file)
{
	char	*tmp;

	if (!file || !(tmp = ft_strnew(file->buf_size * 2)))
		return (NULL);
	ft_memcpy(tmp, file->buf, file->bytes_read);
	ft_strdel(&(file->buf));
	file->buf = tmp;
	file->buf_size *= 2;
	return (file);
}

static char		*ft_getline(t_fd *arr, const int fd)
{
	int		read_ret;
	void	*newline;
	t_fd	*file;

	newline = NULL;
	file = arr + fd;
	if (file->bytes_read && file->buf)
		newline = ft_memchr(file->buf, '\n', file->bytes_read);
	while (!newline)
	{
		if (file->bytes_read + BUFF_SIZE_GNL > file->buf_size)
		{
			if (!(ft_realloc(file)))
				return (NULL);
		}
		read_ret = read(fd, file->buf + file->bytes_read, BUFF_SIZE_GNL);
		if (read_ret == 0 || read_ret == -1)
		{
			file->ret_flag = read_ret;
			return (read_ret == 0 ? ft_last_line(file) : NULL);
		}
		file->bytes_read += read_ret;
		newline = ft_memchr(file->buf, '\n', file->bytes_read);
	}
	return (ft_prep_line(file, newline));
}

int				get_next_line(const int fd, char **line)
{
	static	t_fd	array[10000];

	if (fd < 0 || fd >= 10000 || !line)
		return (-1);
	if (array[fd].open_flag == 0)
	{
		array[fd].open_flag = 1;
		array[fd].bytes_read = 0;
		if (!(array[fd].buf = ft_strnew(BUFF_SIZE_GNL + 1)))
			return (-1);
		array[fd].buf_size = BUFF_SIZE_GNL;
	}
	if (!(*line = ft_getline(array, fd)))
		return (-1);
	return (array[fd].ret_flag);
}

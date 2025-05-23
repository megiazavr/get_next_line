/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megiazar <megiazar@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:07:34 by megiazar          #+#    #+#             */
/*   Updated: 2025/05/23 17:05:35 by megiazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_buf(int fd, char *tail, char *buf)
{
	int	bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (!ft_strchr(tail, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (free (buffer), NULL);
		buf[bytes_read] = '\0';
		tmp = ft_strjoin(tail, buf);
		free(tail);
		tail = tmp;
	}
	return (tail);
}

char	*get_next_line(int fd)
{
	static char	*tail;
	char		*buf;
	char		*line;
	char		*tmp;
	int			len;

	if (fd < 0 || BUFFER_SIZE <= 0 || !buf)
		return (NULL);
	if (!tail)
		tail = ft_strdup("");
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	tail = fill_buf(fd, tail, buf);
	free(buf);
	if (!tail || (tail[0] == '\0'))
		return (free(tail), tail = NULL, NULL);
	len = 0;
	while (tail[len] && tail[len] != '\n')
		len++;
	if (tail[len] == '\n')
		len++;
	line = ft_substr(tail, 0, len);
	if (!line)
		return (free(tail), tail = NULL, NULL)
	tmp = ft_strdup(tail + len);
	free(tail);
	tail = tmp;
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;
	int		next = 0;
	int		i;

	int next_fd = open(".next", O_RDONLY);
	if (next_fd >= 0)
	{
		char buf[8] = {0};
		read(next_fd, buf, 7);
		next = atoi(buf);
		close(next_fd);
	}
	fd = open("example.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	i = 0;
	while (i < next)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
	line = get_next_line(fd);
	if (line)
	{
		printf(">> %s", line);
		int next_fd2 = open(".next", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (next_fd2 >= 0)
		{
			char num[8];
			sprintf(num, "%d", next + 1);
			write(next_fd2, num, ft_strlen(num));
			close(next_fd2);
		}
		free(line);
	}
	else
	{
		printf(">>NULL\n");
		int next_fd2 = open(".next", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (next_fd2 >= 0)
		{
			write(next_fd2, "0", 1);
			close(next_fd2);
		}
	}
	close(fd);
	return (0);
}


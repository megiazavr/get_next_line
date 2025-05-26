/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megiazar <megiazar@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:07:34 by megiazar          #+#    #+#             */
/*   Updated: 2025/05/26 18:49:03 by megiazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char				tmp[BUFFER_SIZE + 1];
	int					read_bytes;
	char				*line;
	static char			*store;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_bytes = 1;
	while (!has_newline(store) && read_bytes > 0)
	{
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(store), store = NULL, NULL);
		tmp[read_bytes] = '\0';
		store = str_join_and_free(store, tmp);
		if (!store)
			return (NULL);
	}
	line = get_line(store);
	if (!line)
		return (free(store), store = NULL, NULL);
	store = cut_tail(store);
	return (line);
}
/*
int main(int ac, char **av)
{
	(void)ac;
	char *line;
	int fd1 = open(av[1], O_RDONLY);

	if (fd1 < 0)
	{
		perror("NOOOOOO ERROR!!!!!!");
		return (1);
	}
	while ((line = get_next_line(fd1)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd1);
	return (0);
}*/
/* 
char	*fill_buf(char *tail, char *buf)
{
	int	i;
	char	*tmp;

	i = 1;
	while (tail[i] != '\n' && tail[i])
		i++;
	while (!ft_strchr(tail, '\n') && i > 0)
	{
		i = read(buf, BUFFER_SIZE);
		if (i <= 0)
			return (tail);
		buf[i] = '\0';
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

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!tail)
		tail = ft_strdup("");
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	tail = fill_buf(fd, tail, buf);
	free(buf);
	if (!tail || (tail[0] == '\0'))
	{
		free(tail);
		tail = NULL;
		return (NULL);
	}
	len = 0;
	while (tail[len] && tail[len] != '\n')
		len++;
	if (tail[len] == '\n')
		len++;
	line = ft_substr(tail, 0, len);
	if (!line)
	{
		free(tail);
		tail = NULL;
		return (NULL);
	}
	tmp = ft_strdup(tail + len);
	free(tail);
	tail = tmp;
	return (line);
}  */

/* int   main(int ac, char **av)
{
  char  *line;
  int   fd1;
  int   fd2;

  fd1 = open(av[1], O_RDONLY);
  fd2 = open(av[2], O_RDONLY);
  get_next_line(fd1);
  printf("%s\n", line);
  get_next_line(fd1);
  printf("%s\n", line);
  get_next_line(fd1);
  printf("%s\n", line);
  get_next_line(fd1);
  printf("%s\n", line);
  return (0);
}
 */
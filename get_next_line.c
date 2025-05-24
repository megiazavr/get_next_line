/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megiazar <megiazar@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:07:34 by megiazar          #+#    #+#             */
/*   Updated: 2025/05/24 18:19:52 by megiazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	has_newline(char *s)
{
	int i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*str_join_and_free(char *a, char *b)
{
	int i;
	int	j;
	char *new_str;

	while (a && a[i])
		i++;
	while (b && b[j])
		j++;
	new_str = malloc(i + j + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (a && a[i])
		new_str[i++] = a[i];
	j = 0;
	while (b && b[j])
		new_str[i++] = b[j++];
	new_str[i] = '\0';
	if (a)
		free(a);
	return (new_str);
}

static char	*get_line(char *s)
{
	int i = 0;
	char *line;

	if (!s || s[0] == '\0')
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	line = malloc(i + (s[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*cut_tail(char *s)
{
	int i;
	int	j;
	char *new_s;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
		return (free(s), NULL);
	new_s = malloc((strlen(s) - i) + 1);
	if (!new_s)
		return (NULL);
	i++;
	j = 0;
	while (s[i])
		new_s[j++] = s[i++];
	new_s[j] = '\0';
	free(s);
	return (new_s);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		tmp[BUFFER_SIZE + 1];
	int			rd;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rd = 1;
	while (!has_newline(store) && rd > 0)
	{
		rd = read(fd, tmp, BUFFER_SIZE);
		if (rd <= 0)
			break ;
		tmp[rd] = 0;
		store = str_join_and_free(store, tmp);
	}
	line = get_line(store);
	store = cut_tail(store);
	return (line);
}

/* char	*fill_buf(char *tail, char *buf)
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
}
 */

int main(int ac, char **av)
{
	(void)ac;
	char *line;
	int fd1 = open(av[1], O_RDONLY);

	while ((line = get_next_line(fd1)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd1);
	return (0);
}

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
} */

/* int	main(void)
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
} */


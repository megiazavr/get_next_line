/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megiazar <megiazar@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:07:34 by megiazar          #+#    #+#             */
/*   Updated: 2025/05/29 16:08:38 by megiazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*store;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	store = half_gnl(fd, store);
	if (!store)
		return (NULL);
	line = next_line(store);
	if (!line)
		return (free(store), store = NULL, NULL);
	store = cut_tail(store);
	if (!store)
		return (line);
	return (line);
}

/* int main(int ac, char **av)
{
	int count;
	int fd;
	char *next_line;

	count = 0;
	if (ac < 2)
        fd = 0;
	else
        fd = open(av[1], O_RDONLY);
    if (fd < 0)
    {
        perror("EWWWWWWWWW an error by opening the file");
        return (1);
	}
    while ((next_line = get_next_line(0)) != NULL)
    {
        count++;
        printf("[%d]: %s\n", count, next_line);
        free(next_line);
    }
    close(fd);
    return 0;
} */

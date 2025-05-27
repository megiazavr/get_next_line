/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megiazar <megiazar@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:07:34 by megiazar          #+#    #+#             */
/*   Updated: 2025/05/27 17:04:32 by megiazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int				read_bytes;
	static char		*store;
	char			*line;
	char			*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (free(tmp), NULL);
	read_bytes = 1;
	while (!has_newline(store) && read_bytes > 0)
	{
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(tmp), free(store), store = NULL, NULL);
		tmp[read_bytes] = '\0';
		store = str_join_and_free(store, tmp);
		if (!store)
			return (free(tmp), NULL);
	}
	free(tmp);
	line = next_line(store);
	if (!line)
		return (free(store), store = NULL, NULL);
	store = cut_tail(store);
	return (line);
}

int main(int ac, char **av)
{
    (void)ac;
    char *line;
    int fd1 = open("example.txt", O_RDONLY);

    if (fd1 < 0)
    {
        perror("EEEW errors opening file\n");
        return (-1);
    }
/*     if (binary_or_bipolar(fd1))
    {
        printf("EEEEEWWWWW its a binary file\n");
        close(fd1);
        return (0);
    }  */
    while ((line = get_next_line(fd1)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd1);
    return (0);
} 
 
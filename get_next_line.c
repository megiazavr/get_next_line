/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megiazar <megiazar@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:07:34 by megiazar          #+#    #+#             */
/*   Updated: 2025/05/27 18:16:55 by megiazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int				count_bytes;
	static char		*store;
	char			*line;
	char			*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (free(tmp), NULL);
	count_bytes = 1;
	while (!has_newline(store) && count_bytes > 0)
	{
		count_bytes = read(fd, tmp, BUFFER_SIZE);
		if (count_bytes == -1)
			return (free(tmp), free(store), store = NULL, NULL);
		tmp[count_bytes] = '\0';
		store = str_join_and_free(store, tmp);
		if (!store)
			return (free(tmp), free(store), store = NULL, NULL);
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
    int fd1 = open(av[1], O_RDONLY);

    if (fd1 < 0)
    {
        perror("EEEW errors opening file\n");
        return (-1);
    }
	while ((line = get_next_line(fd1)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
	printf("%s", get_next_line(fd1));
    close(fd1);
    return (0);
} 
 
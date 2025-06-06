/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megiazar <megiazar@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:13:12 by megiazar          #+#    #+#             */
/*   Updated: 2025/05/29 16:08:53 by megiazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	has_newline(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*str_join_and_free(char *a, char *b)
{
	char	*new_str;
	int		len_a;
	int		len_b;
	int		i;
	int		j;

	len_a = 0;
	len_b = 0;
	while (a && a[len_a])
		len_a++;
	while (b && b[len_b])
		len_b++;
	new_str = malloc(len_a + len_b + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < len_a)
		new_str[i] = a[i];
	j = -1;
	while (++j < len_b)
		new_str[i + j] = b[j];
	new_str[i + j] = '\0';
	free(a);
	return (new_str);
}

char	*next_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = malloc(i + (str[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*cut_tail(char *s)
{
	char				*new_s;
	int					len;
	int					i;
	int					j;

	i = 0;
	j = 0;
	len = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
		return (free(s), NULL);
	i++;
	while (s[i + len])
		len++;
	if (len == 0)
		return (free(s), NULL);
	new_s = malloc(len + 1);
	if (!new_s)
		return (free(s), NULL);
	while (s[i])
		new_s[j++] = s[i++];
	new_s[j] = '\0';
	free(s);
	return (new_s);
}

char	*half_gnl(int fd, char *store)
{
	char	*tmp;
	int		count_bytes;

	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	count_bytes = 1;
	while (!has_newline(store) && count_bytes > 0)
	{
		count_bytes = read(fd, tmp, BUFFER_SIZE);
		if (count_bytes == -1)
			break ;
		tmp[count_bytes] = '\0';
		store = str_join_and_free(store, tmp);
		if (!store)
			break ;
	}
	free(tmp);
	if (count_bytes == -1 || !store || *store == '\0')
		return (free(store), NULL);
	return (store);
}

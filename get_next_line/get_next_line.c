/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:36:03 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/21 17:05:37 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../cub.h"

char	*get_next_line(int fd)
{
	static char	*text;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	if (read(fd, 0, 0) < 0)
		return (free (text), text = NULL, NULL);
	text = creat_text(fd, text);
	if (text == NULL)
		return (NULL);
	line = get_current_line(text);
	text = next_list(text);
	return (line);
}

char	*creat_text(int fd, char *text)
{
	char	*buffer;
	int		char_read;
	char	*temp;

	char_read = 1;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!text)
		text = ft_strdup("");
	while (char_read != 0 && (ft_strchr(text, '\n') == NULL))
	{
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read < 0)
		{
			free(buffer);
			free(text);
			return (NULL);
		}
		buffer[char_read] = '\0';
		temp = text;
		text = ft_strjoin(temp, buffer);
		free(temp);
	}
	free(buffer);
	return (text);
}

char	*get_current_line(char *text)
{
	size_t	i;
	char	*new_line;

	if (ft_strlen(text) == 0)
		return (NULL);
	i = 0;
	while (text[i] != '\n' && text[i])
		i++;
	if (text[i] == '\n')
		i++;
	new_line = ft_substr(text, 0, i);
	if (!new_line)
		return (NULL);
	return (new_line);
}

char	*next_list(char *text)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (text[i] && text[i] != '\n')
		i++;
	if (text[i] == '\n')
		i++;
	if (text[i] == '\0')
	{
		free(text);
		return (NULL);
	}
	tmp = malloc(sizeof(char) * (ft_strlen(text + i) + 1));
	if (!tmp)
		return (NULL);
	while (text[i])
		tmp[j++] = text[i++];
	tmp[j] = '\0';
	free(text);
	return (tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:43:00 by juagomez          #+#    #+#             */
/*   Updated: 2024/10/04 13:45:22 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_final_part_line(char *total_line)
{
	int		i_buffer;
	int		index_final_line;
	char	*final_line;

	i_buffer = 0;
	index_final_line = 0;
	while (total_line[i_buffer] != '\0' && total_line[i_buffer] != '\n')
		i_buffer++;
	if (!total_line[i_buffer])
	{
		free(total_line);
		return (NULL);
	}
	final_line = ft_calloc(ft_strlen(total_line) - i_buffer + 1, sizeof(char));
	if (!final_line)
		return (NULL);
	while (total_line[i_buffer] != '\0')
	{
		final_line[index_final_line] = total_line[i_buffer + 1];
		i_buffer++;
		index_final_line++;
	}
	final_line[index_final_line] = '\0';
	free(total_line);
	return (final_line);
}

static char	*get_cleaned_line(char *buffer)
{
	int		index;
	char	*new_line;

	index = 0;
	if (!buffer[index])
		return (NULL);
	while (buffer[index] != '\0' && buffer[index] != '\n')
		index++;
	new_line = ft_calloc(index + 1 + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	ft_strlcpy(new_line, buffer, index + 1 + 1);
	return (new_line);
}

static char	*ft_strjoin_buffer_src(char	*buffer, char	*partial_line)
{
	char	*dest;

	if (!buffer && !partial_line)
		return (NULL);
	dest = ft_strjoin(buffer, partial_line);
	free(buffer);
	return (dest);
}

static char	*read_file(int fd, char *total_line)
{
	int		char_to_read;
	char	*buffer;

	if (total_line == NULL)
		total_line = ft_calloc(1, 1);
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	char_to_read = 1;
	while (char_to_read > 0)
	{
		char_to_read = read(fd, buffer, BUFFER_SIZE);
		if (char_to_read == -1)
		{
			free(total_line);
			free(buffer);
			return (NULL);
		}
		buffer[char_to_read] = '\0';
		total_line = ft_strjoin_buffer_src(total_line, buffer);
		if (ft_strchr(total_line, '\n'))
			break ;
	}
	free(buffer);
	return (total_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free (buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	next_line = get_cleaned_line(buffer[fd]);
	buffer[fd] = get_final_part_line(buffer[fd]);
	return (next_line);
}

/* int main(void) 
{
    int     fd_0;
    int     fd_1;
    int     fd_2;
    char    *next_line;
    int     count_line;

    count_line = 0;
    fd_0 = open("text_00.txt", O_RDONLY);
    fd_1 = open("text_01.txt", O_RDONLY);
    fd_2 = open("text_02.txt", O_RDONLY);
	
    if (fd_0 == -1 || fd_1 == -1 || fd_2 == -1) 
    {
        printf("Error al abrir archivo");
        return (1);
    }

    while ((next_line = get_next_line(fd_0))) {
        count_line++;
        printf("[%d]-> %s\n", count_line, next_line);
        free(next_line);
    }
    while ((next_line = get_next_line(fd_1))) {
        count_line++;
        printf("[%d]-> %s\n", count_line, next_line);
        free(next_line);
    }
    while ((next_line = get_next_line(fd_2))) {
        count_line++;
        printf("[%d]-> %s\n", count_line, next_line);
        free(next_line);
    }

    if ((close(fd_0) == -1) || (close(fd_1) == -1) || (close(fd_2) == -1))
	{
        printf("Error al cerrar archivo");
        return (1);
    }
    return (0);
} */

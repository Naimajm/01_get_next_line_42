/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:43:32 by juagomez          #+#    #+#             */
/*   Updated: 2024/10/04 11:54:27 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlcpy(char *dest, const char *src, unsigned int destsize)
{
	int	index;
	int	src_len;

	index = 0;
	src_len = ft_strlen(src);
	if (destsize != 0)
	{
		while (src[index] != 0 && index - (destsize - 1))
		{
			dest[index] = src[index];
			index++;
		}
		dest[index] = '\0';
	}
	return (src_len);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	index;

	index = 0;
	ptr = (char *) malloc(count * size);
	if (!ptr)
		return (NULL);
	while (index < (count * size))
	{
		ptr[index] = 0;
		index++;
	}
	return ((void *)ptr);
}

char	*ft_strjoin(char const *str1, char const *str2)
{
	char	*str;
	int		str1_index;
	int		str2_index;
	int		str_joined_index;

	str1_index = 0;
	str2_index = 0;
	str_joined_index = 0;
	str = malloc((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
	if (!str || (!str1 && !str2))
		return (NULL);
	while (str1[str1_index] != '\0')
	{
		str[str_joined_index] = str1[str1_index];
		str_joined_index++;
		str1_index++;
	}
	while (str2[str2_index] != '\0')
	{
		str[str_joined_index] = str2[str2_index];
		str_joined_index++;
		str2_index++;
	}
	str[str_joined_index] = '\0';
	return (str);
}

int	ft_strlen(const char	*str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*ft_strchr(const char *str, int character)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == (char)character)
			return ((char *)(str + index));
		index++;
	}
	if (str[index] != '\0' && str[index] == (char)character)
		return ((char *)(str + index));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:43:20 by juagomez          #+#    #+#             */
/*   Updated: 2024/10/04 14:04:11 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		ft_strlcpy(char *dest, const char *src, unsigned int destsize);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin(char const *str1, char const *str2);
int		ft_strlen(const char *str);
char	*ft_strchr(const char *str, int character);

#endif
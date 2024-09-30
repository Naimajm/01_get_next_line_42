/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:19:01 by juagomez          #+#    #+#             */
/*   Updated: 2024/09/30 19:32:55 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// DEFINITION OF BUFFER SIZE IF IT IS NOT DEFINED IN THE COMPILATION
#ifndef	BUFFER_SIZE
#  define	BUFFER_SIZE 10
#endif

// EXTERNAL LIBRARY
#include <fcntl.h> // open
#include <stdlib.h> // malloc(), free()
#include <unistd.h> // sleep write read
// #include <stdio.h> // printf 

// NODE OF LINKED LIST
typedef struct s_list
{
	char			*str_buffer;
	struct	s_list	*next;
}				t_list;

// INTERNAL FUNCTIONS 'get_next_line.c'

char	*get_next_line(int fd);

/* void	polish_list(t_list **list);
char	*get_line(t_list *list);
void	create_list(t_list **list, int	fd);
void append_buffer_to_list(t_list **list, char *buffer); */

// INTERNAL FUNCTIONS 'get_next_line_utils.c'

void dealloc(t_list **list, t_list *clean_node, char *buffer);

void	copy_string(t_list *list, char *buffer_str);

int	len_to_newline(t_list *list);

t_list	*find_last_node(t_list *list);

int	found_newline(t_list *list);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:19:01 by juagomez          #+#    #+#             */
/*   Updated: 2024/09/29 21:22:34 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// DEFINITION OF BUFFER SIZE IF IT IS NOT DEFINED IN THE COMPILATION
# ifndef	BUFFER_SIZE
#  define	BUFFER_SIZE 10
# endif

// EXTERNAL LIBRARY
# include <fcntl.h> // open
# include <stdlib.h> // malloc(), free()
# include <unistd.h> // sleep write read

// NODE OF LINKED LIST
typedef struct s_list
{
	char			*str_buffer;
	struct	s_list	*next;	// pointer to next node
}				t_list;

// INTERNAL FUNCTIONS 'get_next_line_utils.c'

void dealloc(t_list **list, t_list *clean_node, char *buffer);

void	copy_string(t_list *list, char *buffer_str);

int	len_to_newline(t_list *list);

t_list	*find_last_node(t_list *list);


# endif
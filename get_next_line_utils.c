/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:00:10 by juagomez          #+#    #+#             */
/*   Updated: 2024/09/29 22:11:53 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// LIMPIAR TODOS LOS NODOS DE LISTA VINCULADA + VINCULO LISTA CON NUEVO NODO
void dealloc(t_list **list, t_list *clean_node, char *buffer)
{
	t_list *tmp_list;

	// VALIDACION CONTROL
	if (list ==  NULL)
		return ;
	
	// CICLO PARA RECORRER PTR Listas y LIMPIARLAS
	while (*list != NULL)
	{
		tmp_list = (*list)->next;
		free((*list)->str_buffer);
		free(*list);
		*list = tmp_list;
	}
	*list = NULL;
	// SI EXISTE CHARS EN BUFFER CLEAN_NODE -> COPIA EN LISTA
	if (clean_node->str_buffer[0] != 0)
		*list = clean_node;
	// LIBERAR MEMORIA BUFFER + CLEAN_NODE
	else
	{
		free(buffer);
		free(clean_node);
	}
}

// copiar string dentro de list hasta salto linea '\n'
void	copy_string(t_list *list, char *buffer_str)
{
	int	index_list;
	int	index_str;

	// VALIDACION CONTROL
	if (list == NULL)
		return ;	
	index_str = 0;
	// CICLO LIST
	while (list)
	{
		index_list = 0; // inicializado en 0 para cada nodo
		while (list->str_buffer[index_list] != 0)
		{
			// copiar en buffer hasta salto linea
			if (list->str_buffer[index_list] == '\n')
			{
				buffer_str[index_str] = '\n';
				buffer_str[index_str + 1] = '\0';
				return ;
			}
			buffer_str[index_str] = list->str_buffer[index_list];
			index_list++;
			index_str++;
		}
		list = list-> next;		
	}
	buffer_str[index_str] = '\0';	
}

// CALCULAR LONGITUD LINEA HASTA ENCONTRAR UN SALTO LINEA '\n'
int	len_to_newline(t_list *list)
{
	int	index;
	int	len;

	// VALIDACION CONTROL INPUT
	if (list == NULL)
		return (0);
	len = 0;
	// CICLO LIST != NULL
	while (list)
	{
		index = 0; // inicializar en 0 para comienzo al nuevo nodo
		// ciclo por caracter de cada buffer guardado
		while (list->str_buffer[index] != 0)
		{
			// VERIFICAR CARACTER '\n'
			if (list->str_buffer[index] == '\n')
			{
				len++; // longitud incluye l salto de linea
				return (len);
			}
			len++;
			index++;
		}
		// ptr que apuunta al siguiente nodo
		list = list->next;
	}
	return (len);	
}

t_list	*find_last_node(t_list *list)
{
	// VALIDACION CONTROL
	if (list == NULL)
		return (NULL);
	while (list->next != NULL)
		list = list->next; // moverse al ptr que direcciona al siguiente nodo
	return (list);
}

int	found_newline(t_list *list)
{
	int	index_list;

	// VALIDACION CONTROL
	if (list == NULL)
		return (0);
	
	while (list != NULL)
	{
		index_list = 0;

		while (list->str_buffer[index_list] != 0 && index_list < BUFFER_SIZE)
		{
			if (list->str_buffer[index_list] == '\n')
				return (1);
			index_list++;
		}
		list = list->next;	
	}
	return (0);
}
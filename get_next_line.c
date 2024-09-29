/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:59:55 by juagomez          #+#    #+#             */
/*   Updated: 2024/09/29 23:04:03 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	polish_list(t_list **list);
char	*get_line(t_list *list);
void	create_list(t_list **list, int	fd);
void append_buffer_to_list(t_list **list, char *buffer);

char	*get_next_line(int fd)
{
	// VARIABLE ESTATICA !! FINAL VIDEO https://www.youtube.com/watch?v=8E9siq7apUU&ab_channel=Oceano
	static t_list	*list = NULL;	// pointer to the list / static variables (global variable with local scope)
	char	*next_line; // Buffer

	// VALIDATION -> positive number with fd // control to che if file(buffer) can't be open -> return -1) // Size Buffer_size 0 or negative
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);

	// CREAR LISTA DE BUFFERS CON CHARS YA LEIDOS
	create_list(&list, fd); // &list -> direccion de la lista

	// VALIDATION
	if (list == NULL)
		return (NULL); // no hay siguiente linea

	// BUSCAR LINEA DE LISTA ENLAZADA
	next_line = get_line(list);

	// PREPARA LISTA PARA LA SIGUINTE LLAMADA 
	polish_list(&list);
	return (next_line);
}

// PREPARAR LISTA VINCULADA PARA LA SIGUIENTE LINEA
// vincular nuevo nodo donde meter el resto de los caracteres no utilizados en el buffer con el salto linea '\n'
void	polish_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int	index_list;
	int	index_buffer;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	// VALIDACION CONTROL
	if (buffer == NULL || clean_node == NULL)
		return ;

	last_node =  find_last_node(*list); 
	index_list = 0;
	index_buffer = 0;
	// 1º FASE -> CARACTERES HASTA SALTO LINEA O FINAL
	while (last_node->str_buffer[index_list] != '\0' &&
			last_node->str_buffer[index_list] != '\n')
		index_list++;
	// 2º FASE -> COPIAR CHARS DESPUES DE SALTO LINEA EN BUFFER
	while (last_node->str_buffer[index_list] != '\0' &&
			last_node->str_buffer[index_list++] != '\0')
	{
		buffer[index_buffer] = last_node->str_buffer[index_list];
		index_buffer++;

	}
	buffer[index_buffer] = '\0';
	// asigno buffer en el str_buffer del nuevo nodo
	clean_node->str_buffer = buffer;
	clean_node->next = NULL; // inicializar ptr hacia terminador nulo	

	// LIMPIAR TODOS LOS NODOS DE LISTA VINCULADA + VINCULO LISTA CON NUEVO NODO
	dealloc(list, clean_node, buffer);
}

// CONSEGUIR LINEA HASTA SALTO DE LINEA -> UNION DE BUFFER_STR DE CADA NODO HASTA '\n'
char	*get_line(t_list *list)
{
	int	str_len;
	char	*next_str; // ptr al siguiente string

	// VALIDACION LISTA NULA
	if (list == NULL)
		return (NULL);
	
	// FUNCION AUXILIAR -> CONTAR CHARS HASTA final linea '\n' para reservar espacio de ese tamaño con malloc
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	// validacion reserva malloc
	if (next_str == NULL)
		return (NULL);
	
	// Copiar string en el buffer 'next_str' y retornarlo
	copy_string(list, next_str);
	return (next_str);
}

// CREAR LISTA DE BUFFERS CON CHARS YA LEIDOS HASTA LA SIGUIENTE LINEA '\n'
void	create_list(t_list **list, int	fd)
{	
	int	read_cursor; // numero de caracteres leidos (INDICE posicion ultimo caracter leido)
	char	*buffer; // string + \0

	// escanear line por si existe salto linea '\n' presente
	// itera por cada nueva linea -> lee linea con tamaño buffer hasta que encuentre linea + guarda buffer leido en nodo de lista
	while (!found_newline(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1); // reserva memoria con tamaño buffer + \0
		// VALIDATION -> control si buffer creado
		if (buffer == NULL)
			return ;
		// funcion devuelver num caracteres leidos
		read_cursor = read(fd, buffer, BUFFER_SIZE);

		// VALIDATION char_read = 0 -> no ha leido nada (no queda nada por leer) -> FICHERO TERMINADO DE LEER
		if (!read_cursor)
		{
			free(buffer);
			return ;
		}
		buffer[read_cursor] = '\0';
		// FUNCION APPEND -> AÑADIR BUFFER EN EL NODO DE LISTA
		append_buffer_to_list(list, buffer);
	}	
}

// AÑADIR BUFFER leido EN EL NODO DE LISTA
void append_buffer_to_list(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	// CREACION NUEVO NODO y encontrar ultimo nodo lista para conectar nuevo nodo
	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	// VALIDATION reserva memoria
	if(new_node == NULL)
		return ;
	// VALIDACION 1º LINEA -> si last_node es nulo (no hay guardado ningun buffer leido)
	if(last_node == NULL)
		*list = new_node; // apunta puntero *list al nuevo nodo creado
	else
		last_node->next = new_node; // conecta puntero next al nuevo nodo

	// ASIGNA BUFFER LEIDO AL NUEVO NODO + inicializa puntero next en nulo
	new_node->str_buffer = buffer;
	new_node->next = NULL;	
}

/* #include <stdio.h> // printf

int	main(void)
{
	int		fd;
	char	*line;
	int		lines;	

	lines = 1;
	fd = open("file.txt", O_RDONLY);

	// TEST BASICO
	char	buffer[256];
	int	chars_read;	
	//printf("%ld \n", read(fd, buffer, 20)); 
	while ((chars_read = read(fd, buffer, 25)))
	{
		buffer[chars_read] = '\0';
		printf("buffer -> %s \n", buffer);
	}

	// TEST 1
	while ((line = get_next_line(fd)))
	{
		printf("%d->%s \n", lines++, line);
	}	
	return (0);
} */


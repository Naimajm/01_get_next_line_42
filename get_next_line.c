/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:59:55 by juagomez          #+#    #+#             */
/*   Updated: 2024/10/04 20:43:47 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/** 
* @brief Conseguir linea texto desde salto linea incluida hasta final del buffer.
* @param buffer	char*: linea bruta.
* @returns -> Si check es correcto, devuelve linea texto restante.
Si check es incorrecto, devuelve NULL.
*/
static char	*get_final_part_line(char *total_line)
{	
	int		index_buffer;
	int		index_final_line;
	char	*final_line;

	index_buffer = 0;
	index_final_line = 0;
	// LLEGAR HASTA SALTO LINEA
	while (total_line[index_buffer] != '\0' && total_line[index_buffer] != '\n')
		index_buffer++;
	//VALIDACION BUFFER -> si no hay nada despues del salto linea
	if (!total_line[index_buffer])
	{
		free(total_line);
		return (NULL);
	}
	// RESERVA MEMORIA TAMAÑO (TOTAL - INDEX + '\0')
	final_line = ft_calloc(ft_strlen(total_line) - index_buffer + 1, sizeof(char));
	// VALIDACION CONTROL
	if(!final_line)
		return (NULL);
	// COPIAR CHARS BUFFER DESDE '\n' en FINAL_LINE
	while (total_line[index_buffer] != '\0')
	{
		final_line[index_final_line] = total_line[index_buffer + 1]; // incrementar indice para no copiar salto linea
		index_buffer++;
		index_final_line++;
	}
	final_line[index_final_line] = '\0';
	free(total_line);
	return (final_line);
}

/** 
* @brief Conseguir linea completa neta con salto linea incluida.
* @param buffer	char*: linea bruta.
* @returns -> Si check es correcto, devuelve linea texto neta.
Si check es incorrecto, devuelve NULL.
*/
static char	*get_cleaned_line(char *buffer)
{
	int	index;
	char	*new_line;

	index = 0;
	// VALIDACION CONTROL
	if (!buffer[index])
		return (NULL);
	// AVANZAR HASTA SALTO LINEA
	while (buffer[index] != '\0' && buffer[index] != '\n')
		index++;
	// reserva memoria para string anterior a salto de linea +salto linea + terminador nulo
	new_line = ft_calloc(index + 1 + 1, sizeof(char));
	// VALIDACION 
	if (!new_line)
		return (NULL);
	// copiar en newline la linea bruta hasta el indice + salto linea incluido +  terminado nulo
	ft_strlcpy(new_line, buffer, index + 1 + 1);
	return (new_line);	
}

/** 
* @brief Une en nuevo string los caracteres del buffer y del string 'src'.
Libera bufffer despues de la union.
* @param char	*buffer: string para almacenamiento temporal .
* @param char	*partial_line: string.
* @returns -> char *-> devuelve string con la union de ambos string.
Si check es incorrecto, devuelve NULL.
*/
static char	*ft_strjoin_buffer_src(char	*buffer, char	*partial_line)
{
	char	*dest;
	
	if (!buffer && !partial_line)
		return (NULL);
	dest = ft_strjoin(buffer, partial_line);
	free(buffer);
	return (dest);
}

/** 
* @brief Copia linea completa hasta salto linea '\n' en buffers con tamaño BUFFER_SIZE.
* @param fd		fd: identicador id del file descriptor.
* @param text	*total_line: texto .
* @returns -> Si check es correcto, devuelve linea texto en bruto.
Si check es incorrecto, devuelve NULL.
*/
static char	*read_file(int	fd, char *total_line)
{
	int	char_to_read;  // caracter donde se ha quedado la lectura del archivo de la funcion 'read'
	char	*buffer;

	// VALIDACION 
	if (total_line == NULL)
		total_line = ft_calloc(1, 1); // string con terminador nulo '/0'
	// RESERVA MEMORIA EN BUFFER
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	// validacion reserva memoria
	if (!buffer)
		return (NULL);
	char_to_read = 1;
	// GUARDA STRING DEL BUFFER EN TEXTO HASTA ENCONTRAR SALTO LINEA O NO LEER NADA (char_to_read = 0)
	while (char_to_read > 0)
	{
		// lee contenido hasta tamaño BUFFER_SIZE
		char_to_read = read(fd, buffer, BUFFER_SIZE); // indice caracter leido del texto
		// VALIDACION -> NO LECTURA DE CARACTERES O FINAL TEXTO
		if (char_to_read == -1)
		{
			free(total_line);
			free(buffer);
			return (NULL);
		}
		buffer[char_to_read] = '\0'; // terminador nulo string
		//printf("%d -> %s \n", char_to_read, buffer);
		// GUARDA CONTENIDO BUFFER + EL RESTO DE TEXTO ANTERIOR EN NUEVO CHAR!!!
		total_line = ft_strjoin_buffer_src(total_line, buffer);
		// CONDICION -> CORTA CUANDO SE ENCUENTRE CARACTER SALTO LINEA '\N' EN EL TEXTO
		if (ft_strchr(total_line, '\n'))
			break ;
	}
	free(buffer);
	return (total_line);	
}

/** 
* @brief Comprueba si un carácter determinado es un carácter alfabético.
* @param charac: carácter a comprobar.
* @returns -> Si check es correcto, devuelve valor distinto de cero.
Si check es incorrecto, devuelve 0.
*/
char	*get_next_line(int fd)
{
	// VARIABLE ESTATICA !! FINAL VIDEO https://www.youtube.com/watch?v=8E9siq7apUU&ab_channel=Oceano
	static char	*buffer;
	char	*next_line; 

	// VALIDATION -> positive number with fd // control to check if file(buffer) can't be open -> return -1) // Size Buffer_size 0 or negative
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free (buffer);
		buffer = NULL;
		return (NULL);
	}
	// CONSEGUIR LINEA BRUTA CON SALTO LINEA Y RESTO DEL BUFFER
	buffer = read_file(fd, buffer);
	// VALIDATION
	if (!buffer)
		return (NULL);
	// CONSEGUIR LINEA NETA CON SALTO LINEA INCLUIDO
	next_line = get_cleaned_line(buffer);
	// CONSEGUIR TEXTO DESDE SALTO LINEA
	buffer = get_final_part_line(buffer);
	return (next_line);
}

/* # include <stdio.h>

int	main(void)
{
	int		fd = open("text_00.txt", O_RDONLY);
	
	int index_read;
	char	*buffer;
	char	*new_line;
	char	*final_line;

	// 1º COPIAR LINEA COMPLETA HASTA L BUFFER QUE INCLUYE SALTO LINEA -> READ_FILE()
	index_read = read(fd, malloc(10 + 1), 10);
	buffer = read_file(fd, buffer);
	//printf("tamaño buffer -> %d \n", index_read);
	//printf("Linea bruta -> %s<-final\n", buffer);

	// 2º CONSEGUIR LINEA NETA HASTA SALTO LINEA -> GIVE_LINE()
	new_line = give_line(buffer);
	//printf("Linea neta -> %s \n", new_line);

	// 3º CONSEGUIR FINAL LINEA TEXTO DESPUES DE SALTO LINEA
	final_line = get_final_line(buffer);
	printf("final linea -> %s \n", final_line);

	free(buffer);
	free(new_line);
	free(final_line);

	// 4º TEST FUNCION GET_NEXT_LINE COMPLETA
	char	*next_line;
	int     count_line;

	count_line = 0;
	if (fd == -1) 
    {
        printf("Error al abrir archivo");
        return (1);
    }
	while ((next_line = get_next_line(fd)))
	{
		count_line++;
		printf("[%d]-> %s\n",count_line, next_line);
		free(next_line);
	}
	if (close(fd) == -1)
	{
        printf("Error al cerrar archivo");
        return (1);
    }
	return (0);
} */

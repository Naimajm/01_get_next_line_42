/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:43:00 by juagomez          #+#    #+#             */
/*   Updated: 2024/10/04 22:18:44 by juagomez         ###   ########.fr       */
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

/* // VERSION LECTURA EN CADENA ARCHIVOS -> 1 LINEA POR CADA ARCHIVO
# include <stdio.h>
int main(int argc, char **argv)
{
	// CAMBIAR -sttttatic -> PROBLEMA TESTEO
	-sttttatic char **lines;
	int *fds;
	int index_fds;
	int	count_line;
	int line_remaining_to_read_flag;	

	// VALIDACION NUJMERO ARCHIVOS MAYOR QUE 2
	if (argc < 2)
	{
		printf("Uso: %s \n Se necesitan mas archivos para testeo", argv[1]);
		return (1);
	}

	// RESERVA MEMORIA PARA LISTA FILES DESCRIPTORS + VARIABLE ESTATICA LINEAS
	fds = malloc((argc - 1) * sizeof(int));
	lines = malloc((argc - 1) * sizeof(char *));
	if (!fds || !lines)
	{
		printf("error reserva memoria -> malloc");
		return (1);
	}

	// GUARDAR RELACION FILES DESCRIPTORS de ARCHIVOS ABIERTOS
	index_fds = 0;
	while (index_fds < (argc - 1))
	{
		fds[index_fds] = open(argv[index_fds + 1], O_RDONLY);
		// VALIDACION FUNCION APERTURA ARCHIVOS
		if (fds[index_fds] == -1)
		{
			printf("error funcion open");
			return (1);
		}
		printf("lista [%i]: archivo %s -> file descryptor: %i \n",
			index_fds, argv[index_fds + 1], fds[index_fds]);
		index_fds++;
	}
	printf("\n ------------------ \n");

	// 1º GUARDAR PRIMERA LINEA PARA DE CADA FILE DESCRIPTOR -------------
	index_fds = 0;	
	while ((index_fds < (argc - 1)))
	{		
		lines[index_fds] = get_next_line(fds[index_fds]);
		index_fds++;
	}

	// 2º -> IMPRIMIR 1º LINEA GUARDADA + 
		// ITERAR E IMPRIMIR SOBRE LAS SIGUIENTES FDS ------
	count_line = 1;
	line_remaining_to_read_flag = 1; 
	while (line_remaining_to_read_flag > 0)
	{
		line_remaining_to_read_flag = 0;
		index_fds = 0;
		
		// CICLO DE LECTURA E IMPRESION DE 1 LINEA POR CADA FILE DESCRIPTOR
		while (index_fds < (argc - 1))
		{
			// 2º -> EXISTE 1º LINEA DEL FD ACTIVO -> 
				// IMPRIME Y CONSIGUE SIGUIENTE LINEA de ese FD
			if (lines[index_fds])
			{
				// imprimir linea							
				printf("fd:[%d] line:[%d]-> %s\n",
					fds[index_fds], count_line, lines[index_fds]);				
				free(lines[index_fds]);
				count_line++;
				
				// conseguir siguiente linea fd actual
				lines[index_fds] = get_next_line(fds[index_fds]);
				
				// SI EXISTE LINEA -> REINICIA CONTADOR PARA REINICIAR 1º BUCLE
				if (lines[index_fds])
					line_remaining_to_read_flag = 1;				
			}			
			index_fds++;			
		}
	}	
	// CERRAR ARCHIVOS -------------------------------
	index_fds = 0;
	while (index_fds < (argc - 1))
	{
		close(fds[index_fds]);
		index_fds++;
	}
	// LIBERAR LIST FDS Y MATRIZ DE STRINGS -----------
	free(fds);
	free(lines);
	return (0);
} */

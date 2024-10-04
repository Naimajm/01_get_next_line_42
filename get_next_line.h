/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:19:01 by juagomez          #+#    #+#             */
/*   Updated: 2024/10/04 10:52:28 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// DEFINITION OF BUFFER SIZE IF IT IS NOT DEFINED IN THE COMPILATION
#ifndef	BUFFER_SIZE
#  define	BUFFER_SIZE 42
#endif

// EXTERNAL LIBRARY
#include <fcntl.h> // open
#include <stdlib.h> // malloc(), free()
#include <unistd.h> // sleep write read

#include <stdio.h> // printf (solo para DESARROLLO)

// INTERNAL FUNCTIONS 'get_next_line.c' ----------------------------

char	*get_next_line(int fd);

// INTERNAL FUNCTIONS 'get_next_line_utils.c'  ----------------------

/** 
* @brief Copia una cadena terminada en nulo de src a destino, 
asegurando una terminación nula adecuada dentro de un tamaño limitado de n. 
Devuelve la longitud de la cadena fuente.
* @param dest:  puntero a la cadena de destino.
* @param src:  puntero a la cadena de origen.
* @param size:  límite de tamaño del búfer de destino.
* @returns unsigned int -> longitud de la cadena de origen.
*/
int	ft_strlcpy(char *dest, const char *src, unsigned int destsize);

/** 
* @brief Asigna memoria para una matriz de elementos con un recuento
 específico y un tamaño n. Comprueba si hay desbordamiento, 
 asigna memoria usando malloc y pone a cero la memoria 
 antes de devolver el puntero a la memoria asignada.
* @param count: número de elementos a asignar.
* @param size: tamaño de cada elemento.
* @returns void -> Si la asignación de memoria se realiza correctamente, 
se devuelve un puntero al bloque de memoria asignado.
Si el recuento o n es cero o si falla la asignación de memoria, 
se devuelve NULL.
*/
void	*ft_calloc(size_t count, size_t size);

/** 
* @brief Reserva con malloc() y devuelve una nueva
string, formada por la concatenación de str1 y str2.
* @param str1: 1º string.
* @param str2: string a añadir a str1.
* @returns char *-> nueva string.
NULL si falla la reserva de memoria.
*/
char	*ft_strjoin(char const *str1, char const *str2);

/** 
* @brief Devuelve número de caracteres antes del terminado nulo '\0'
* @param str: puntero a la cadena terminada en nulo.
* @returns int -> longitud de la cadena de entrada, excluyendo '\0'
*/
int	ft_strlen(const char *str);

/** 
* @brief Busca la primera aparición de un carácter específico en una cadena.
* @param str:  puntero a la cadena terminada en nulo 
en la que se realiza la búsqueda.
* @param character:  El caracter a buscar.
* @returns char * -> Puntero a la primera aparición del carácter en la cadena.
NULL si no se encuentra el carácter.
*/
char	*ft_strchr(const char *str, int character);

#endif
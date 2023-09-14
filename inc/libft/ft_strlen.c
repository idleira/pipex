/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:18:34 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/09/13 20:34:35 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* get string length */
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// int main() {
//     char str[] = "A noisy noise annoys an oyster most.";
//     size_t length = ft_strlen(str);
//     printf("Length of the string: %zu\n", length);
//     return 0;
// }
//
//size_t is guaranteed to be big enough to contain the size
//of the biggest object system can handle.
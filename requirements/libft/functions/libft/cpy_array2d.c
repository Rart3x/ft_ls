/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_array2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:56:03 by jduval            #+#    #+#             */
/*   Updated: 2023/03/10 14:56:47 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**cpy_array2d(char **array2d)
{
	int		i;
	char	**cpy;

	i = 0;
	if (array2d == NULL)
		return (NULL);
	cpy = malloc (sizeof(char *) * (count_args_2d(array2d) + 1));
	if (!cpy || !array2d)
		return (NULL);
	while (array2d[i])
	{
		cpy[i] = malloc(sizeof(char) * ft_strlen(array2d[i]) + 1);
		ft_strcpy(cpy[i], array2d[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

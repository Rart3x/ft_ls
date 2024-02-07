/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_array2d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramjatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:15:48 by kramjatt          #+#    #+#             */
/*   Updated: 2023/03/17 14:20:58 by kramjatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	find_in_array2d(char **array, char *str)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (!ft_strcmp(array[i], str))
			return (1);
		i++;
	}
	return (0);
}

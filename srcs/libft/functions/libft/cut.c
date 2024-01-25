/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramjatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:45:52 by kramjatt          #+#    #+#             */
/*   Updated: 2023/03/16 13:46:12 by kramjatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*cut(char *str, char c)
{
	char	*cut;
	int		i;
	int		j;
	int		length;

	i = 0;
	length = 0;
	while (str[length])
		length++;
	while (str[i] != c)
		i++;
	i++;
	cut = malloc(sizeof(char) * (length - i) + 1);
	j = 0;
	while (str[i])
	{
		cut[j] = str[i];
		i++;
		j++;
	}
	cut[j] = '\0';
	return (cut);
}

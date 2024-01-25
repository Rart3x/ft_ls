/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_fs2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:25:20 by jduval            #+#    #+#             */
/*   Updated: 2023/05/02 10:48:20 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_s2(char *s1, char *s2)
{
	size_t	size_alloc;
	char	*new_s;
	size_t	size_srcs;

	size_alloc = ft_strlen(s1) + ft_strlen(s2);
	new_s = malloc(size_alloc * (sizeof(char) + 1));
	if (!new_s)
	{
		free (s2);
		return (NULL);
	}
	if (!s2)
	{
		ft_strlcpy(new_s, s1, size_alloc + 1);
		return (new_s);
	}
	size_alloc = ft_strlen(s1) + 1;
	ft_strlcpy(new_s, s1, size_alloc);
	size_alloc = ft_strlen(new_s);
	size_srcs = ft_strlen(s1) + ft_strlen(s2) + 1;
	ft_strlcpy(&new_s[size_alloc], s2, size_srcs);
	free (s2);
	return (new_s);
}

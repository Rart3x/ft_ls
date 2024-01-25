/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:55:20 by jduval            #+#    #+#             */
/*   Updated: 2023/04/04 16:34:14 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static unsigned long long	do_the_change(const char *nptr, int i, int sign)
{
	unsigned long long	value;

	value = 0;
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		value = value * 10 + (nptr[i] - '0');
		if (sign == 1 && value > 9223372036854775807U)
			return (0);
		else if (sign == -1 && value > 9223372036854775808U)
			return (0);
		else
		i++;
	}
	return (value);
}

int	ft_atoll(const char *nptr)
{
	int			i;
	long long	value;
	long long	a;

	a = 1;
	i = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			a = -1;
		i++;
	}
	value = do_the_change(nptr, i, a);
	return (value * a);
}

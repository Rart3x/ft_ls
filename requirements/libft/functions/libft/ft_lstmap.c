/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:17:58 by jduval            #+#    #+#             */
/*   Updated: 2022/10/13 13:49:33 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*tmp;
	t_list	*pos;

	if (!lst || !del || !f)
		return (NULL);
	new_list = ft_lstnew(lst->content);
	if (!new_list)
		return (NULL);
	new_list->content = (*f)(lst->content);
	pos = lst->next;
	while (pos)
	{
		tmp = ft_lstnew(pos->content);
		if (!tmp)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		tmp->content = (*f)(pos->content);
		pos = pos->next;
		ft_lstadd_back(&new_list, tmp);
	}
	return (new_list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:07:07 by jinhkim           #+#    #+#             */
/*   Updated: 2020/04/27 22:49:17 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*lst_tmp;
	t_list	*tmp;

	new = 0;
	if (lst == 0)
		return (0);
	else
	{
		lst_tmp = lst;
		while (lst_tmp)
		{
			if (!(tmp = ft_lstnew(f(lst_tmp->content))))
			{
				ft_lstclear(&new, del);
				return (0);
			}
			ft_lstadd_back(&new, tmp);
			lst_tmp = lst_tmp->next;
		}
		return (new);
	}
}

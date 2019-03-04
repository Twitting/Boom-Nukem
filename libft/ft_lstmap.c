/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 20:07:06 by twitting          #+#    #+#             */
/*   Updated: 2018/12/12 14:05:58 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ftt_lstclear(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		tmp = lst->next;
		free(lst->content);
		lst->content = NULL;
		free(lst);
		lst = NULL;
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlst;
	t_list	*tmp;

	if (lst == NULL || f == NULL)
		return (NULL);
	if (!(newlst = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (f(lst) == NULL)
		return (NULL);
	newlst = f(lst);
	tmp = newlst;
	while (lst->next)
	{
		lst = lst->next;
		if (f(lst) == NULL)
		{
			ftt_lstclear(newlst);
			return (NULL);
		}
		tmp->next = f(lst);
		tmp = tmp->next;
	}
	return (newlst);
}

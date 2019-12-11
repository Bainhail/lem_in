/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_contentsize.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 01:58:12 by nabih             #+#    #+#             */
/*   Updated: 2019/12/11 02:12:55 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_lstdel_contentsize(t_list **lst, size_t cs)
{
	t_list		*tmp1;
	t_list		*tmp2;

	if (lst && *lst && cs > 0)
	{
		tmp1 = *lst;
		if (tmp1->content_size == cs)
		{
			*lst = tmp1->next;
			ft_memdel((void**)&tmp1);
		}
		else
		{
			while (tmp1->next && tmp1->next->content_size != cs)
				tmp1 = tmp1->next;
			if (tmp1->next)
			{
				tmp2 = tmp1->next;
				tmp1->next = tmp2->next;
				ft_memdel((void**)&tmp2);
			}
		}
	}
}

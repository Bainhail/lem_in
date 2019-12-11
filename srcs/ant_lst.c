/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 00:41:56 by nabih             #+#    #+#             */
/*   Updated: 2019/12/11 00:50:58 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

t_list					*init_ant_lst(int32_t nb)
{
	t_list			*tmp;
	t_list			*lst;

	lst = NULL;
	while (nb > 0)
	{
		tmp = ft_lstnew(NULL, 0);
		tmp->content_size = nb;
		ft_lstadd(&lst, tmp);
		nb--;
	}
	tmp = NULL;
	return (lst);
}

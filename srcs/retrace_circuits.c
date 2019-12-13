/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrace_circuits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:34:02 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/04 13:34:12 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

t_node			*get_parent_addr(t_node *enter)
{
	t_path		*p;

	p = enter->path_lst;
	while(p)
	{
		if (p->flow == 2)
			return (p->addr);
		p = p->next;
	}
	return (NULL);
}

uint8_t		retrace_one_circuit_and_modif_flow(t_lemin *lem, t_circuits *cir, t_list **used)
{
	t_node			*child;
	t_node			*parent;
	uint32_t		nb_floor;

	child = lem->end;
	nb_floor = 0;
	while (child != lem->start)
	{
		parent = get_parent_addr(child);
		if (!parent || not_in_address_lst(*used, parent) == LM_FALSE)
			return (LM_FALSE);
	 	if (ft_lstadd_top(&(cir->addr), address_list_new(&parent)) == 0)
			return (LM_FALSE);
		if (parent != lem->start)
		{
			if (ft_lstadd_top(used, address_list_new(&parent)) == 0)
				return (LM_FALSE);
		}
		flow_plus_modif(child, parent, -1);
		flow_plus_modif(parent, child, 1);
		child = parent;
		nb_floor++;
	}
	cir->nb_floor = nb_floor;
	return (LM_TRUE);
}

/*
** circuits are array of circuits found, array len = tab_len
** value stored in array is address of poiter of t_node
*/

uint8_t		retrace_circuits(t_lemin *lem,
							uint32_t *tab_len, t_circuits** cir_tab)
{
	uint32_t		i;
	t_list			*used;

	i = 0;
	used = NULL;
	while (i < *tab_len)
	{
		cir_tab[i]->addr = address_list_new(&(lem->end));
		if (cir_tab[i]->addr == NULL)
		{
			del_address_lst(used);
			return (LM_FALSE);
		}
		if (retrace_one_circuit_and_modif_flow(lem, cir_tab[i], &used))
			i++;
		else
		{
			(*tab_len) -= 1;
			del_address_lst(cir_tab[i]->addr);
		}
	}
	del_address_lst(used);
	return (LM_TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_anthill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:06:30 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/11 06:33:41 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

/*
*/
void		check_if_exit(t_node *end, t_node **node, t_anthill *h)
{
	if (h != NULL && node != NULL && end == *node)
		h->total_exit++;
}

t_node		**get_node_in_circuit(t_list *cir, uint32_t floor)
{
	t_node	**node;

	node = NULL;
	while (cir && (floor != 0))
	{
		cir = cir->next;
		floor--;
	}
	if (cir)
	{
		node = ((t_node**)(cir->content));
		return (node);
	}
	return (NULL);
}


/*
** h->send_size == tab_len of cir_tab
*/
static void		print_one_floor_in_cir(uint32_t floor, t_circuits **cir_tab,
									   t_anthill *h, t_lemin *lem)
{
	t_node			**node;
	int32_t			i;
	uint32_t		nb;//

	i = 0;
	node = NULL;
	nb = h->max_ant_index - h->send_size + 1;//
	while (i < h->send_size && h->print_nb > 0)
	{
		node = get_node_in_circuit(cir_tab[i]->addr, floor);
		/* printf("print_anthill.c >>>> node_addr = %p , i = %d, floor = %d , nb = %d <<<<\n", node, i, floor, nb + i); */
		/* printf("print_anthill.c >>>> nb_FLOOR = %d & FLOOR = %d <<<<\n", cir_tab[i]->nb_floor, floor % cir_tab[i]->nb_floor); */
		/* printf("print_anthill.c >>>> FLOOR - (NB + i) = %d <<<<\n", floor - (nb + i)); */
		/* if (floor == 90) */
		/* 	exit(0); */
		if (node)
		{
//			print_line(nb + i, (*node)->name);//
			check_if_exit(lem->end, node, h);
			h->max_ant_index--;
			h->print_nb--;
		}
		i++;
	}
}

void		print_anthill_one(t_lemin *lem, t_circuits **cir_tab, t_anthill *h)
{
	uint32_t		floor;

	if (h->activated == LM_FALSE)
		return ;
	floor = h->start_floor;
	while (h->print_nb > 0)
	{
//		printf("%d\n", h->print_nb);
		print_one_floor_in_cir(floor, cir_tab, h, lem);
		floor++;
	}
}

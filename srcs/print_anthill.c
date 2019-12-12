/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_anthill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:06:30 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/08 06:28:35 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void		print_line(uint32_t ant_index, char *node_name, int last)
{
	ft_putchar('L');
	ft_putnbr(ant_index);
	ft_putchar('-');
	ft_putstr(node_name);
	if (last != 1)
		ft_putchar(' ');
}

/*
*/
void		check_if_exit(t_node *end, t_node **node, t_anthill *h)
{
	if (end != NULL && h != NULL)
		if (node != NULL && end == *node)
			h->total_exit++;
}

t_node		**get_node_in_circuit(t_list *cir, uint32_t floor)
{
	t_node **node;

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
	int32_t			i;
	t_node			**node;

	i = 0;
	node = NULL;
	while (i < h->send_size && h->print_nb > 0)
	{
		node = get_node_in_circuit(cir_tab[i]->addr, floor);
		if (node)
		{
			print_line(h->max_ant_index, (*node)->name, h->print_nb);
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
		print_one_floor_in_cir(floor, cir_tab, h, lem);
		floor++;
	}
}

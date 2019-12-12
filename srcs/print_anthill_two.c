/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_anthill_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:13:26 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/04 19:13:29 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static uint32_t		not_already_in_best_cir(int32_t *best_cir,
											int32_t len, int32_t chosen)
{
	int32_t	i;

	i = 0;
	while (i < len)
	{
		if (best_cir[i] == chosen)
			return (LM_FALSE);
		i++;
	}
	return (LM_TRUE);
}

static int32_t		choose_shortest(t_circuits **cir_tab, int32_t tab_len,
										int32_t *best_cir, int32_t len)
{
	int32_t	choose;
	uint32_t shortest;
	int32_t min;

	choose = 0;
	min = 0;
	while (choose < tab_len)
	{
		if (choose == 0)
			shortest = cir_tab[choose]->nb_floor;
		if (cir_tab[choose]->nb_floor < shortest
			&& not_already_in_best_cir(best_cir, len, choose))
		{
			shortest = cir_tab[choose]->nb_floor;
			min = choose;
		}
		choose++;
	}
	return (min);
}

static int32_t		*fill_best_circuits(t_circuits **cir_tab, int32_t tab_len,
										int32_t best_cir_len)
{
	int32_t			*best_cir;
	int32_t			i;

	i = 0;
	best_cir = (int32_t*)malloc(sizeof(int32_t) * best_cir_len);
	if (!best_cir)
		return (NULL);
	while (i < best_cir_len)
	{
		best_cir[i] = choose_shortest(cir_tab, tab_len, best_cir, best_cir_len);
		i++;
	}
	return (best_cir);
}

static t_node		**print_one_node(int32_t index, t_circuits **cir_tab,
									t_anthill *h2, uint32_t floor)
{
	t_node			**node;

	node = get_node_in_circuit(cir_tab[index]->addr, floor);
	if (node)
	{
		print_line(h2->max_ant_index, (*node)->name, h2->print_nb);
		h2->max_ant_index--;
		h2->print_nb--;
	}
	return (node);
}

void				print_anthill_two(t_lemin *lem, t_circuits **cir_tab,
									int32_t tab_len, t_anthill *h2)
{
	int32_t			i;
	uint32_t		floor;
	int32_t			*best_cir;
	t_node			**node;

	if (h2->activated == LM_FALSE)
		return ;
	best_cir = fill_best_circuits(cir_tab, tab_len, h2->send_size);
	if (!best_cir)
		return ;
	i = 0;
	floor = h2->start_floor;
	while (h2->print_nb > 0)
	{
		while (i < h2->send_size && h2->print_nb > 0)
		{
			node = print_one_node(best_cir[i], cir_tab, h2, floor);
			check_if_exit(lem->end, node, h2);
			i++;
		}
		i = 0;
		floor++;
	}
	free(best_cir);
}

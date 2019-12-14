/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:32:10 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/12 12:35:19 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void		debug_print_anttab(t_circuits **c, uint32_t *tab, uint32_t len)
{
	uint32_t ants = 0;

	for (uint32_t i = 0; i < len; i++)
	{
		printf("Floor[%d] => ants[%d] + node[%d] = %d\n", i, tab[i],
				c[i]->nb_floor, tab[i] + c[i]->nb_floor - 1);
		ants += tab[i];
	}
	printf("Ants = %d\n", ants);
}

void		debug_print_circuits(t_circuits **cir_tab, uint32_t tab_len)
{
	uint32_t		i;
	t_node	*node;
	t_list	*cp;

	i = 0;
	while (i < tab_len)
	{
		if (cir_tab[i])
		{
			printf("circuit[%d] has length of [%d]:\n", i, cir_tab[i]->nb_floor);
			cp = cir_tab[i]->addr;
			while (cp)
			{
				node = *(t_node**)(cp->content);
				// printf("%s\n", node->name);
				cp = cp->next;
			}
		}
		i++;
	}
}

/*
** Cherche le meilleure ratio pour le nombre
** de ligne a afficher a chaque tour
*/
/* static void				next_how_many(t_circuits **c, uint32_t len, uint32_t ants, t_manypth *mp) */
/* { */
/* 	mp->old = 0; */
/* 	mp->not_use = 0; */
/* 	while (--len + 1 > 0) */
/* 	{ */
/* 		mp->ratio = ants / (len + 1); */
/* 		if (mp->ratio > 0) */
/* 		{ */
/* 			mp->new = c[len]->nb_floor + (mp->ratio - 1); */
/* 			if ((mp->new < mp->old || mp->old == 0)) */
/* 			{ */
/* 				if (mp->old != 0) */
/* 					mp->not_use++; */
/* 				mp->old = mp->new; */
/* 			} */
/* 		} */
/* 		else */
/* 			mp->not_use++; */
/* 	} */
/* } */

/* uint32_t				how_many_path(t_circuits **c, uint32_t len, uint32_t ants) */
/* { */
/* 	uint32_t		len_tmp; */
/* 	t_manypth		mp; */
/* //	t_manypth		next; */

/* 	mp.old = 0; */
/* 	mp.not_use = 0; */
/* 	len_tmp = len; */
/* 	while (--len + 1 > 0) */
/* 	{ */
/* 		mp.ratio = ants / (len + 1); */
/* 		if (mp.ratio > 0) */
/* 		{ */
/* 			mp.new = c[len]->nb_floor + (mp.ratio - 1); */
/* 			if ((mp.new <= mp.old || mp.old == 0)) */
/* 			{ */
/* 				if (mp.old != 0) */
/* 					mp.not_use++; */
/* 				mp.old = mp.new; */
/* 			} */
/* 		} */
/* 		else */
/* 			mp.not_use++; */
/* 	} */
/* //	if ((ants = ants - (len_tmp - mp.not_use)) > 0) */
/* //	next_how_many(c, len_tmp, ants, &next); */
/* 	/\* 		printf("new = %u, old = %u ===> NOT_USE = %u\n", mp.new, mp.old, mp.not_use); *\/ */
/* 	/\* 		printf("next_new = %u, next_old = %u ===> next_NOT_USE = %u\n", next.new, next.old, next.not_use); *\/ */
/* 	/\* printf("%u\n", (mp.old < next.old) ? mp.not_use : next.not_use); *\/ */
/* 	return (/\* (mp.old <= next.old) ?  *\/mp.not_use /\* : next.not_use *\/); */
/* } */

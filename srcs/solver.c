/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:25:51 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/13 22:40:15 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

int8_t					flow_plus_modif(t_node *enter, t_node *exit,
										int8_t modif)
{
	t_path			*p;

	p = enter->path_lst;
	while (p)
	{
		if (ft_strcmp(p->name, exit->name) == 0)
		{
			p->flow += modif;
			return (LM_SUCCESS);
		}
		p = p->next;
	}
	return (LM_ERROR);
}

static t_circuits		**init_cir_tab(uint32_t tab_len)
{
	t_circuits		**cir_tab;
	uint32_t		i;

	i = 0;
	if ((cir_tab = (t_circuits**)malloc(sizeof(t_circuits*) * tab_len)) == NULL)
		return (NULL);
	while (i < tab_len)
	{
		if ((cir_tab[i] = (t_circuits*)malloc(sizeof(t_circuits))) == NULL)
		{
			free_cir_tab(cir_tab, tab_len);
			return (NULL);
		}
		ft_bzero(cir_tab[i], sizeof(t_circuits));
		i++;
	}
	return (cir_tab);
}

static void				remove_duplicated(t_circuits **c, uint32_t pos)
{
	// while (pos < len - 1)
	// {
	// 	ft_swap_ptr((void**)&(c[pos]), (void**)&(c[pos + 1]));
	// 	pos++;
	// }
	// ft_memdel((void**)&(c[pos]));
	del_address_lst(c[pos]->addr);
	free(c[pos]);
	c[pos] = NULL;
}

static void				looking_for_duplicated_node(t_circuits **c, uint32_t i,
													uint32_t j)
{
	t_list			*lst1;
	t_list			*lst2;
	t_node			*n1;
	t_node			*n2;

	if (c[i] == NULL ||  c[j] == NULL)
		return ;
	lst1 = c[i]->addr;
	while (lst1->next)
	{
		n1 = *(t_node**)lst1->content;
		lst2 = ((t_list*)c[j]->addr)->next;
		while (lst2->next)
		{
			n2 = *(t_node**)lst2->content;
			// if (ft_strcmp(n1->name, n2->name) == 0)
			if (n1 == n2)
			{
				if ( c[i]->nb_floor < c[j]->nb_floor)
					remove_duplicated(c, j);
				else
					remove_duplicated(c, i);
				return ;
			}
			lst2 = lst2->next;
		}
		lst1 = lst1->next;
	}
}

static uint32_t			sort_path(t_circuits **c, uint32_t len)
{
	uint32_t		i;
	uint32_t		j;

	i = 0;
	while (i < len)
	{
		j = len - 1;
		while (j > i)
		{
			if (c[j] && c[i]->nb_floor > c[j]->nb_floor)
				ft_swap_ptr((void**)&(c[i]), (void**)&(c[j]));
			// looking_for_duplicated_node(c, i, j, &len);
			--j;
		}
		++i;
	}
	return (len);
}

static void			duplicate_check(t_circuits **c, uint32_t len)
{
	uint32_t		i;
	uint32_t		j;

	i = 0;
	while (i < len)
	{
		j = len - 1;
		while (j > i)
		{
			// if (c[j] && c[i]->nb_floor > c[j]->nb_floor)
			// 	ft_swap_ptr((void**)&(c[i]), (void**)&(c[j]));
			looking_for_duplicated_node(c, i, j);
			--j;
		}
		++i;
	}
}

static uint32_t				clean_cirtab(t_circuits **c, uint32_t len)
{
	uint32_t		i;
	uint32_t		j;
	uint32_t		ret;

	i = 0;
	ret = len;
	while (i < len)
	{
		if (c[i] == NULL)
		{
			j = i;
			while (j < len - 1)
			{
				ft_swap_ptr((void**)&(c[j]), (void**)&(c[j + 1]));
				j++;
			}
			ret--;
		}
		i++;
	}
	return (ret);

}

uint32_t				choose_wanted_flow(t_lemin *lem)
{
	uint32_t		wanted_flow;

	if (lem->start->nb_paths > lem->end->nb_paths)
		wanted_flow = lem->end->nb_paths;
	else
		wanted_flow = lem->end->nb_paths;
	if ((uint32_t)lem->nb_ants < wanted_flow)
		wanted_flow = (uint32_t)lem->nb_ants;
	return (wanted_flow);
}

// decommente pour voir le temps utilisé
void					solver(t_lemin *lem)
{
	uint32_t		wanted_flow;
	uint32_t			tab_len;
>>>>>>> testNabih
	t_circuits		**cir_tab;
	t_list			*ants;

	/* clock_t	start_t, finish_t; */
	/* start_t = clock(); */
	wanted_flow = choose_wanted_flow(lem);
	if ((tab_len = fulkerson_algo(lem, wanted_flow)) == 0)
		return ;
	if ((cir_tab = init_cir_tab(tab_len)) == NULL)
		return ;
	// finish_t = clock() - start_t;
	// printf("fulkerson_algo time%f\n", (double)finish_t / CLOCKS_PER_SEC);
	// start_t = clock();

	//!!! si il y a croisement, tab_len va diminuer dans retrace_circuit
	keep_tab_len = tab_len;
	if (retrace_circuits(lem, &tab_len, cir_tab))
	{
		/* finish_t = clock() - start_t; */
		/* printf("retrace_circuits time%f\n", (double)finish_t / CLOCKS_PER_SEC); */
		/* start_t = clock(); */
		printf("tab_len first%d\n", tab_len);
		debug_print_circuits(cir_tab, tab_len);

		duplicate_check(cir_tab, tab_len);

		printf("tab_len after duplicate_check%d\n", tab_len);
		debug_print_circuits(cir_tab, tab_len);

		tab_len = clean_cirtab(cir_tab, tab_len);
		printf("tab_len after clean_cirtab[%d]\n", tab_len);
		debug_print_circuits(cir_tab, tab_len);


		tab_len = sort_path(cir_tab, tab_len);
		printf("3[%d]\n", tab_len);

		ants = init_ant_lst(lem->nb_ants);

		/* finish_t = clock() - start_t; */
		/* printf("sort+antlst time%f\n", (double)finish_t / CLOCKS_PER_SEC); */
		/* start_t = clock(); */

		// print_ants(lem, &ants, cir_tab, tab_len);
//		printf("%d\n", tab_len);

		/* finish_t = clock() - start_t; */
		/* printf("print path time%f\n", (double)finish_t / CLOCKS_PER_SEC); */
	}
	printf("\n====================\n");
	debug_print_circuits(cir_tab, keep_tab_len); 

	free_cir_tab(cir_tab, keep_tab_len);
}

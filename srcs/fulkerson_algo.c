/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fulkerson_algo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:45:10 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/12 11:33:15 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static t_node		**get_top_elem(t_list *lst)
{
	t_node	**ret;

	ret = NULL;
	if (lst != NULL)
	{
		ret = (t_node**)(lst->content);
	}
	return (ret);
}

static uint8_t		iter_adja_of_current(t_node *current, t_list **visited,
									t_list **open)
{
	t_node		*adjacen_node;
	t_path		*p;

	p = current->path_lst;
	while (p)
	{
		adjacen_node = p->addr;
		if (!adjacen_node)
			return (LM_FALSE);
		if (p->flow > 0 && not_in_address_lst(*visited, adjacen_node))
		{
			ft_lstadd_top(visited, address_list_new(&adjacen_node));
			ft_lstadd_bot(open, address_list_new(&adjacen_node));
			adjacen_node->parent_addr = current;
		}
		p = p->next;
	}
	return (LM_TRUE);
}

static void			free_open_and_visited(t_list *open, t_list *visited)
{
	del_address_lst(visited);
	del_address_lst(open);
}


/*
** In this function, t_list stores, in lst->conente,
** the address of pointer of node.
** "open" are nodes to be evaluate, elements are always added to the end,
** and taken from the top to be evaluated,
** then delete top elem after evaluation.
** "visited" are nodes already visited,
** if inside, we don't evaluate this node.
*/
static uint8_t		breadth_first_search(t_lemin *lem)
{
	t_list	*open;
	t_list	*visited;
	t_node	**current;

	visited = NULL;
	open = address_list_new(&(lem->start));
	while (open && (current = get_top_elem(open)))
	{
//		current = get_top_elem(open);
		if (!current)
			break ;
		if (not_in_address_lst(visited, *current))
			ft_lstadd_top(&visited, address_list_new(current));
		if (*current == lem->end)
		{
			free_open_and_visited(open, visited);
			return (LM_TRUE);
		}
		if (iter_adja_of_current(*current, &visited, &open) == LM_FALSE)
			break ;
		del_top_elem(&open);
	}
	free_open_and_visited(open, visited);
	return (LM_FALSE);
}

/*
** wanted_flow is the maximum flow that we want,
** it will limite max_flow returned
** if lem->nb_ants < max_flow, then the flow returned is wanted_flow,
** else, the flow returned is the maximum flow that anthill can provide.
** but if wanted_flow == 0, it will return the actual maximum flow
*/

uint32_t		fulkerson_algo(t_lemin *lem, uint32_t wanted_flow)
{
	uint32_t	max_flow;
	t_node		*parent;
	t_node		*child;

	max_flow = 0;
	while (breadth_first_search(lem))
	{
		max_flow++;
		child = lem->end;

		while (child != lem->start)
		{
			parent = child->parent_addr;
			flow_plus_modif(parent, child, -1);
			flow_plus_modif(child, parent, 1);
			child = parent;
		}
		if (wanted_flow > 0 && max_flow == wanted_flow)
			return (wanted_flow);
	}
	return (max_flow);
}

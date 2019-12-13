/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:36:05 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/13 17:53:59 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SOLVER_H
# define SOLVER_H

# include "lem_in.h"

typedef	struct	s_circuits
{
	uint32_t	nb_floor;
	t_list		*addr;
}				t_circuits;

typedef struct	s_manypth
{
	uint32_t	not_use;
	uint32_t	ratio;
	uint32_t	old;
	uint32_t	new;
	uint32_t	diff;
	uint32_t	old_diff;
}				t_manypth;

typedef	struct	s_anthill
{
	int32_t		unsent;
	int32_t		send_size;
	uint32_t	total_exit;
	uint32_t	total_enter;
	uint32_t	print_nb;
	uint32_t	start_floor;
	uint32_t	max_ant_index;
	uint8_t		activated;
}				t_anthill;

t_list			*address_list_new(t_node ** const new);
void			del_top_elem(t_list **alst);
void			del_address_lst(t_list *lst);
uint8_t			not_in_address_lst(t_list *lst, t_node const *address);
t_node			**get_node_in_circuit(t_list *cir, uint32_t floor);
/* void			print_ants(t_lemin *lem, t_circuits **cir_tab, */
/* 								int32_t tab_len); */
void			print_ants(t_lemin *lem, t_list **ants,
							t_circuits **cir_tab, int32_t tab_len);
uint32_t		fulkerson_algo(t_lemin *lem, uint32_t wanted_flow);
int8_t			flow_plus_modif(t_node *enter, t_node *exit, int8_t modif);
uint8_t			retrace_circuits(t_lemin *lem, uint32_t tab_len,
								t_circuits** cir_tab);
void			print_anthill_one(t_lemin *lem, t_circuits **cir_tab,
								t_anthill *h);
void			print_anthill_two(t_lemin *lem, t_circuits **cir_tab,
								int32_t tab_len, t_anthill *h2);
void			free_cir_tab(t_circuits **cir_tab, uint32_t tab_len);
//void			print_line(uint32_t ant_index, char *node_name);
void			check_if_exit(t_node *end, t_node **node, t_anthill *h);
void			init_anthill_one(t_anthill *h, int32_t nb_ants,
								int32_t max_flow);
void			init_anthill_two(t_anthill *h, int32_t nb_ants,
								int32_t max_flow);
uint32_t		how_many_path(t_circuits **c, uint32_t len,
								uint32_t ants);

//à supprimer functions debug à la fin
void			debug_print_circuits(t_circuits **cir_tab, uint32_t tab_len);
void			debug_print_address_lst(t_list **alst);
void			debug_print_anttab(t_circuits **c, uint32_t *tab, uint32_t len);// A Delete

# endif

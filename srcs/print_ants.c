/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:45:26 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/10 06:04:09 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static int32_t	send_ants(t_anthill *h)
{
	int32_t		send;

	if (h->unsent)
	{
		send = h->send_size;
		h->unsent -= send;
	}
	else
		send = 0;
	return (send);
}

/*
** max_ant_index and print_nb will decrease at each turn in print_one_floor
*/
void		prepare_print_one_data(t_anthill *h, uint32_t send1)
{
	if (h->activated == LM_FALSE)
		return ;
	if (send1 == 0)
		h->start_floor++;
	h->total_enter += send1;
	h->print_nb = h->total_enter - h->total_exit;
	h->max_ant_index = h->total_enter;
	// printf("\n\nsend1[%d]total_exit[%d], total_enter[%d]\n\n",send1, h->total_exit, h->total_enter );

}

void		prepare_print_two_data(t_anthill *h2, uint32_t send2, t_anthill *h)
{
	if (h2->activated == LM_FALSE)
		return ;
	if (send2 == 0)
		h2->start_floor++;
	h2->total_enter += send2;
	h2->print_nb = h2->total_enter - h2->total_exit;
	h2->max_ant_index = h2->total_enter + h->max_ant_index;

}

/*
** in init anthill, h1 is activated, h2 not.
** In loop, h2 will be activated when h1 finish sending.
** Note that send2 has a non-zero value only once,
** that is when send1 becomes zero for the first time.
*/
uint32_t				how_many_path(t_circuits **c, uint32_t len, uint32_t ants);// Dans debug

void		print_ants(t_lemin *lem, t_circuits **cir_tab, int32_t tab_len)
{
	t_anthill	h1;
	t_anthill	h2;
	int32_t		send1;
	int32_t		send2;
	uint32_t	n_use;//

	n_use = how_many_path(cir_tab, tab_len, lem->nb_ants);//
	init_anthill_one(&h1, lem->nb_ants, tab_len - n_use);//
	init_anthill_two(&h2, lem->nb_ants, tab_len - n_use);//
	send2 = 0;
	while (h1.activated || h2.activated)
	{
		printf("no use[%d]\n", n_use );
		if (tab_len - n_use <= (uint32_t)h1.unsent)
			h1.send_size = (int32_t)(tab_len - n_use);
		send1 = send_ants(&h1);
		if (send1 == 0)
		{
//			h2.send_size = (lem->nb_ants - (h1.total_enter + h2.total_enter)) % h1.send_size;
			send2 = send_ants(&h2);
		}
		if (send2 > 0)
			h2.activated = LM_TRUE;
		prepare_print_one_data(&h1, send1);
		prepare_print_two_data(&h2, send2, &h1);
		print_anthill_two(lem, cir_tab, tab_len /* - n_use */, &h2);//
		print_anthill_one(lem, cir_tab, &h1);
		if (h1.total_enter - h1.total_exit == 0)
			h1.activated = LM_FALSE;
		if (h2.total_enter - h2.total_exit == 0)
			h2.activated = LM_FALSE;
		ft_putchar('\n');
		if (lem->nb_ants - (h1.total_enter + h2.total_enter) > 0)//
			n_use = how_many_path(cir_tab, tab_len, lem->nb_ants - (h1.total_enter + h2.total_enter));//
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_address.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:55:27 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/08 10:24:26 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

/* void		debug_print_address_lst(t_list **alst) */
/* { */
/* 	t_list *cp; */
/* 	t_node **node; */

/* 	cp = *alst; */
/* 	while (cp) */
/* 	{ */
/* 		node = (t_node**)(cp->content); */
/* 		printf("[%s]", (*node)->name); */
/* 		cp = cp->next; */
/* 	} */
/* 	printf("\n"); */
/* } */

t_list		*address_list_new(t_node ** const new)
{
	t_list *lst;

	lst = ft_lstnew((void const *)new, sizeof(t_node*));
	return (lst);
}

uint8_t		not_in_address_lst(t_list *lst, t_node const *address)
{
	while (lst != NULL)
	{
		if (address == *(t_node**)(lst->content))
			return (LM_FALSE);
		lst = lst->next;
	}
	return (LM_TRUE);
}

void		del_top_elem(t_list **alst)
{
	t_list	*cp;

	if (*alst)
	{
		cp = *alst;
		*alst = (*alst)->next;
		free(cp->content);
		cp->content = NULL;
		free(cp);
		cp = NULL;
	}
}

void		del_address_lst(t_list **alst)
{
	t_list *keep;


	while (*alst)
	{
		keep = (*alst)->next;
		if ((*alst)->content)
		{
			free((*alst)->content);
			(*alst)->content = NULL;
		}
		free(*alst);
		*alst = keep;
	}
	*alst = NULL;
}

void		free_cir_tab(t_circuits **cir_tab, uint32_t tab_len)
{
	uint32_t	i;

	i = 0;
	if (cir_tab)
	{
		while (i < tab_len)
		{
			if (cir_tab[i])
			{
				del_address_lst(&(cir_tab[i]->addr));
				free(cir_tab[i]);
				cir_tab[i] = NULL;
			}
			i++;

		}
		free(cir_tab);
		cir_tab = NULL;
	}
}

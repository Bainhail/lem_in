/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_many_path.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:39:30 by nabih             #+#    #+#             */
/*   Updated: 2019/12/12 12:44:28 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		GET_MANY_PATH_H
# define	GET_MANY_PATH_H

# include <solver.h>

uint32_t			*init_ants_tab(uint32_t *tab, uint32_t len);
uint32_t			get_appro_max(t_circuits **c, uint32_t len,
									uint32_t ants);

#endif

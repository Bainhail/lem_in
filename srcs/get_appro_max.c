/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_appro_max.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:42:56 by nabih             #+#    #+#             */
/*   Updated: 2019/12/12 12:44:18 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_many_path.h>

static void			update_mp(t_manypth *mp, uint32_t diff,
								uint32_t new, uint32_t ratio)
{
	mp->diff = diff;
	mp->old = new;
	mp->old_diff = ratio;
}

static uint32_t		calc_appro_max(t_circuits **c, uint32_t len,
									   t_manypth *mp)
{
	uint32_t		i;
	uint32_t		appro_max;

	i = mp->diff;
	appro_max = 0;
	mp->old -= (mp->old_diff / 2);
	if (appro_max == 0)
	{
		while (i < len && c[i]->nb_floor <= mp->old)
			i++;
		i--;
		appro_max = c[i]->nb_floor;
	}
	return (appro_max);
}

uint32_t			get_appro_max(t_circuits **c, uint32_t len,
									  uint32_t ants)
{
	t_manypth		mp;
	uint32_t		i;

	i = 0;
	mp.old = 0;
	while ((mp.ratio = ants / (i + 1)) > 0 && i < len)
	{
		mp.new = c[i]->nb_floor + mp.ratio;
		if (mp.new < mp.old || mp.old == 0)
			update_mp(&mp, i, mp.new, mp.ratio);
		else if (mp.new == mp.old && mp.old != 0)
		{
			if (c[i - 1]->nb_floor + (ants / i) == mp.new)
				update_mp(&mp, i, mp.new, mp.ratio);
		}
		i++;
	}
	return (calc_appro_max(c, len, &mp));
}

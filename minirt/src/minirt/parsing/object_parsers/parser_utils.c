/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:04:52 by maecarva          #+#    #+#             */
/*   Updated: 2025/04/16 16:56:34 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minirt.h"

bool	check_only_valid_float(char **tab, int maxindex)
{
	int	i;

	i = 0;
	if (!tab)
		return (false);
	while (tab[i] && i < maxindex)
	{
		if (!ft_is_double(tab[i]))
			return (false);
		i++;
	}
	return (true);
}

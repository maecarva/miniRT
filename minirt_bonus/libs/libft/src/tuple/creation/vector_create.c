/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:49:24 by maecarva          #+#    #+#             */
/*   Updated: 2025/04/11 11:07:11 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/tuple.h"

t_tuple	vector_create(double x, double y, double z)
{
	return (tuple_create(x, y, z, 0));
}

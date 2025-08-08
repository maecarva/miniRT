/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:08:39 by ebonutto          #+#    #+#             */
/*   Updated: 2025/04/01 13:33:25 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/long.h"

long	ft_atol(const char *str)
{
	long	nb;
	int		count;
	int		sign;

	nb = 0;
	count = 0;
	sign = 1;
	while ((str[count] >= 9 && str[count] <= 13) || str[count] == ' ')
		count++;
	if (str[count] == '+')
		count++;
	else if (str[count] == '-')
	{
		sign = -1;
		count++;
	}
	while (ft_isdigit(str[count]))
	{
		nb = nb * 10 + (str[count] - '0') * sign;
		count++;
	}
	return (nb);
}

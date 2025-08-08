/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:13:33 by maecarva          #+#    #+#             */
/*   Updated: 2025/04/01 13:30:28 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/double_linked_list.h"

int	dll_size(t_dlist **dlist)
{
	t_dlist	*tmp;
	int		size;

	size = 0;
	if (!(*dlist))
		return (size);
	if ((*dlist)->next == *dlist)
		return (++size);
	tmp = *dlist;
	while (tmp->next != *dlist)
	{
		tmp = tmp->next;
		size++;
	}
	return (size + 1);
}

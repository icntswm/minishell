/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:27:58 by fkenned           #+#    #+#             */
/*   Updated: 2021/04/26 17:27:59 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*str;

	str = *lst;
	if (!(*lst))
		*lst = new;
	else
	{
		while (str->next != NULL)
			str = str->next;
		str->next = new;
	}
}

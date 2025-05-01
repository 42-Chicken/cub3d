/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:51:46 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/01 16:59:42 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

t_list	*ft_lstget(t_list *lst, bool (*f)(void *, void *), void *data)
{
	while (lst != NULL && f)
	{
		if (f(lst->content, data) == true)
			break ;
		lst = lst->next;
	}
	return (lst);
}

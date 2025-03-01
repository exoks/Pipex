/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:35:31 by oezzaou           #+#    #+#             */
/*   Updated: 2025/02/28 13:56:05 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

//====<[ gnl_lstnew: ]>======================================================
t_buff	*gnl_lstnew(char *buff)
{
	t_buff	*node;

	node = (t_buff *) malloc(sizeof(t_buff));
	if (!node)
		return (0);
	node->buff = buff;
	node->next = 0;
	return (node);
}

//====<[ gnl_lstlast: ]>=====================================================
t_buff	*gnl_lstlast(t_buff *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

//====<[ gnl_lstclear: ]>=======================================================
t_buff	*gnl_lstclear(t_buff **head)
{
	t_buff	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->buff);
		free(*head);
		*head = tmp;
	}
	head = 0;
	return (0);
}

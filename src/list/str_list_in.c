/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_list_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:27:27 by tmuranak          #+#    #+#             */
/*   Updated: 2025/02/26 17:27:34 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "libft.h"

#include <stdbool.h>
#include <stdlib.h>

bool	str_list_in(char *str, t_str_list *lst)
{
	return (str_list_search_node(lst, ft_streq, str) != NULL);
}

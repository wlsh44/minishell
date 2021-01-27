/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endline_condition_quote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:20:59 by schang            #+#    #+#             */
/*   Updated: 2021/01/27 21:21:15 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	endline_condition_quote(char c)
{
	if (c == 0 || ft_isseparator(c))
		return (1);
	return (0);
}

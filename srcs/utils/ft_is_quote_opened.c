/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_quote_closed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:03:54 by schang            #+#    #+#             */
/*   Updated: 2021/01/27 20:08:42 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_quote_opened(char *str)
{
	int	open;
	int	i;

	i = 0;
	open = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (i > 0 && str[i - 1] == '\\')
			;
		else if (open == 0 && str[i] == '\"')
			open = 1;
		else if (open == 0 && str[i] == '\'')
			open = 2;
		else if (open == 1 && str[i] == '\"')
			open = 0;
		else if (open == 2 && str[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}

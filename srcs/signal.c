/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 20:59:35 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 22:59:44 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bin_parent_sighandler(int code)
{
	if (code == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_exit_status = 130;
	}
	else if (code == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", 2);
		g_exit_status = 131;
	}
}

void	bin_child_sighandler(int code)
{
	if (code == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	else if (code == SIGQUIT)
		exit(0);
}

void	default_sighandler(int code)
{
	if (code == SIGINT)
	{
		ft_putstr_fd(" \b\b \b\b \b\n", STDOUT_FILENO);
		ft_putstr_fd("m$ ", STDOUT_FILENO);
		g_exit_status = 130;
	}
	else if (code == SIGQUIT)
	{
		ft_putstr_fd(" \b\b \b\b \b", STDOUT_FILENO);
		g_exit_status = 131;
	}
}

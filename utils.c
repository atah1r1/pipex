/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahiri <atahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:41:11 by atahiri           #+#    #+#             */
/*   Updated: 2021/06/28 21:53:33 by atahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_func(char *msg, int code)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(code);
}

void	free_d_p(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
}

void	free_all_func(void)
{
	free(g_all.input);
	free(g_all.output);
	free(g_all.cmd1_path);
	free(g_all.cmd2_path);
	free_d_p(g_all.cmd1);
	free_d_p(g_all.cmd2);
}

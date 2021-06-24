/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahiri <atahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 09:32:40 by atahiri           #+#    #+#             */
/*   Updated: 2021/06/24 11:31:27 by atahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_pipex {
	int		fd[2];
	char	*input;
	char	**cmd1;
	char	**cmd2;
	char	*output;
}				t_pipex;

char	**ft_split(const char *ss, char c);
int		ft_strlen(char *s);
#endif
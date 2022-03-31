/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 12:26:56 by akhachat          #+#    #+#             */
/*   Updated: 2021/07/31 16:42:41 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

void    child_p(char **argv, char **env, int *fd);
void    parent_p(char **argv, char **env, int *fd);
char    *env_path(char **env, char *ar);
int     get_index(char **env);

#endif

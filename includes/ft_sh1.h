/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 12:56:19 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/12 15:50:52 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH1_H
# define FT_SH1_H

# include "libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <signal.h>

typedef struct	s_env
{
	char		**path;
	int			nb_path;
	char		*home;
	char		*user;
	int			sz;
}				t_env;

void			disp_env(char **env, t_env var);


void			change_dir(char **arg, t_env var);

#endif

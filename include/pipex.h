/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:09:44 by oezzaou           #+#    #+#             */
/*   Updated: 2022/12/16 18:18:15 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//====<[ Include guards: ]>=====================================================
#ifndef PIPEX_H
# define PIPEX_H

//====<[ Headers: ]>============================================================
# include "ft_printf.h"
# include <fcntl.h>
# include <stdio.h>

//====<[ Macors: ]>=============================================================
# define PIPE 1
# define CLOSE 0
# define EXIT_ERROR 127
# define PERMISSION_DENIED 126
# define LEN(A, B) A * (A >= B) + B * (A < B)
# define NOT_FOUND "command not found"
# define P_DENIED "permission denied"
# define N_FILE "no such file or directory"
# define PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki"

//====<[ Struct: file & cmd ]>==================================================
typedef struct s_file
{
	char	*infile;
	char	*outfile;
	int		ncmds;	
}t_file;

typedef struct s_cmd
{
	int				id;
	char			*name;
	char			*path;
	char			**args;
	struct s_file	*files;
	int				hdoc;
	pid_t			pid;
}t_cmd;

//====<[ Functions: Prototypes ]>===============================================
void	ft_wait_child_ps(t_cmd *cmds, int *status);
t_cmd	*ft_extract_cmds(int ac, char **av, char **env, int is_hdoc);
int		*ft_manage_pipes(int *pipes, int ncmds, int flag);
int		ft_exec_cmds(t_cmd *cmds, char **env, int *pipes, int *inout_fd);
void	ft_clear(t_cmd *cmds, int *pipes, char **av, char **paths);
int		get_inout_files(t_cmd *cmds, int *inout_fd);
char	**ft_here_doc(int ac, char **av, int *pipes);
char	*get_next_line(int fd);
void	ft_close_all_fd(t_cmd *cmds, int *pipes, int *inout_fd);
int		ft_print_err_msg(t_cmd *cmds);

#endif
//==============================================================================

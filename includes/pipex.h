/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:52:49 by odessein          #+#    #+#             */
/*   Updated: 2022/07/30 21:39:03 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

# include "libft.h"

typedef struct s_info{
	t_list	*cmd;
	t_list	*opt;
	t_list	*path_cmd;
	char	*cmd_exec;
	char	*path;
	t_bool	infile;
	t_bool	here_doc;
	t_bool	end;
	int		fd[2];
	int		tmp_fd;
	int		ind;
	char	**arg;
}		t_info;

/*********************************************/
/*					Init					 */
/*********************************************/

t_bool	pp_handle_infile(t_info *info);

/*********************************************/
/*					Exec					 */
/*********************************************/

char	**pp_arg_for_exec(t_info *info, int i);
t_bool	pp_loop_exec(t_info *info, char **envp);

/*********************************************/
/*					parsing					 */
/*********************************************/

t_bool	pp_parse(int ac, char **av, t_info *info);
t_bool	pp_check_file(int ac, char **av, t_info *info);
t_bool	pp_check_cmd(int ac, char **av, t_info *info);
t_bool	pp_fill_lst(t_info *info, char *arg, char **cmd, char **option);
t_bool	pp_check_path(char **path_lst, char *cmd, t_bool *valid, t_info *info);
t_bool	pp_loop_arg(int ac, char **av, char **path_lst, t_info *info);

/*********************************************/
/*					getenv					 */
/*********************************************/

char	*pp_get_path(char **envp);

/*********************************************/
/*					utils					 */
/*********************************************/

void	pp_free_things(t_info *info);
void	pp_free_and_close(int pipe_fd[2], int *pid, t_info *info);
void	pp_free_double_arr(char **arr);
t_bool	pp_waitpid(int i, int *pid, t_info *info);
void	pp_close_pipe(int pipe[2]);
void	pp_check_end(t_info *info, int pipe_fd[2]);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:00:58 by nali              #+#    #+#             */
/*   Updated: 2022/06/30 11:43:34 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "LIBFT/libft.h"

extern int	g_err;

typedef struct s_cmd
{
	char			**cmd;
	char			*cmd_path;
	int				in_fd;
	int				out_fd;
	int				here_doc;
	int				here_fd;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_var
{
	char	prompt[11];
	char	**env_var;
	t_cmd	*cmd_lst;
	int		cmd_count;
	int		pipe_count;
	int		**pipe_fds;
	int		num;
}t_var;

//ft_lexer.c
int		ft_count_tokens(char *s);
void	ft_separate_tokens(char **t, char *s);
void	ft_lexer(char *input, t_var	*vars);
void	ft_check_if_quote(char *s, int i, int *qval, int *openq);
// ft_utils.c
int		ft_strcmp(char *s1, char *s2);
int		ft_chk_not_space_tab_newline(int ch);
void	ft_init_var_zero(int *i, int *j, int *q0, int *q1);
void	ft_print_list(t_cmd *cmd_lst);
void	ft_print_tokens(char **tokens);
//ft_free.c
void	ft_free_env(t_var *vars);
void	ft_free_tokens(char **tokens);
void	ft_free_list(t_var *vars);
void	ft_free_array(char **arr);
void	ft_free(char *buf, t_var *vars);
//ft_expander.c
void	ft_expander(char **tokens, t_var *vars);
void	ft_skip_till_next_quote(char *s, int *j, int *qval, int *open_quote);
char	**ft_remove_null_entries(char **t);
//void	ft_split_expander.c
char	**ft_split_expander(char **tokens);
//ft_strjoin_new.c
char	*ft_strjoin_new(char *s1, char *s2);
//ft_envp.c
char	*ft_envp(char *name, int l, t_var *vars, int *flag);
char	*ft_get_envp_val(char *name, t_var *vars, int *flag);
//ft_handle_dollar.c
char	*ft_handle_dollar(char *str, int p, t_var *vars);
char	*ft_substr_no_brace(char *str, int *p);
//ft_split_pipe.c
char	**ft_split_redirection_pipe(char **tokens);
// ft_split_helper.c 
int		ft_split_count(char **tokens);
int		ft_check_symbols(char *str, int *index, int count);
void	ft_handle_non_symbols(char *token, int *j, int *qv, int *open_quote);
//ft_trim.c
int		ft_count_quotes(char *input);
char	*ft_trim_2(char *token);
int		ft_trim_pipex(t_cmd	*cmd_node);
// int		ft_trim(t_var *vars);
//ft_syntax_check.c
int		ft_syntax_check(char **tokens);
int		ft_check_next_token(char *str);
// ft_parser.c
void	ft_parser(t_var *vars);
void	ft_free_paths(char **paths);
//ft_list.c
int		ft_create_list(char **tokens, t_var *vars);
//ft_redirections.c
t_cmd	*ft_redirections(t_cmd *cmd_node);
//ft_input_redirection.c
char	**ft_remove_redirection(char **cmd, int c, int index);
char	**ft_input_redirection(char **cmd, int index, int *fd);
//ft_heredoc.c
char	*ft_add_newline(char *buf);
char	**ft_heredoc(int index, t_cmd *node, t_var *vars, int count);
int		ft_handle_heredoc(t_cmd *node, t_var *vars);
//ft_herdoc_read.c
char	**ft_read_stdin(char *limiter);
//ft_heredoc_expansion.c
void	ft_heredoc_expansion(char **arr, t_var *vars);
// ft_output_redirection.c  
char	**ft_output(char **str, int index, t_cmd *lst_node);
//ft_error.c
void	ft_malloc_error(void);
void	ft_cmd_error(char *cmd);
//ft_utils2.c
int		ft_count_cmd(t_cmd *cmd_lst);
//ft_cmd_path.c
char	**ft_get_path_variable(char	**env_var);
char	*ft_get_cmd_path(t_cmd	*cmd_lst, char **paths);
int		ft_set_cmd_path(t_cmd *cmd_node, t_var *vars);
//ft_pipex.c
void	ft_pipex(t_var *vars);
// ft_pipex_utils.c
int		**ft_open_pipes(int p);
void	ft_close_pipes(int **fd, int p);
void	ft_close_fds(t_cmd *cmd_lst);
void	ft_free_pipes(int **fd, int p);
// ft_pipex_process.c  
void	ft_child_process(int i, t_var *vars);
//ft_dup.c
int		ft_dup(int i, t_cmd	*cmd_node, int	**pipe_fds);
//ft_handle_dollar_special
char	*ft_handle_special_cases(char *str, char *result, int i);
//ft_goto_builtin_parent.c
void	ft_goto_export_parent(t_cmd	*cmd_lst, t_var *vars);
void	ft_goto_cd_parent(t_cmd	*cmd_lst, t_var *vars);
void	ft_goto_unset_parent(t_cmd	*cmd_lst, t_var *vars);
//signal.c
void	ft_sig_handler(int signal);
void	ft_sig_handler2(int signal);
void	ft_sig_handler_child(int signal);
void	ft_sig_handler_heredoc(int signal);
// //Raj buitin.c
// void	built_in2(char **cmd, t_var *vars);
int		built_in1(char **cmd, t_var *vars);
void	built_in2(char **cmd, t_var *vars, int out_fd);
void	ft_echo(char **cmd, int fd);
// void	ft_echo(char **cmd);
void	ft_cd(char **cmd, t_var *vars);
void	ft_cd3(char **cmd, t_var *vars, char *dir, char *old_pwd);
void	ft_cd4(t_var *vars, char *new_pwd, char *old_pwd);
char	*ft_cd1(t_var *vars, char *old_pwd);
void	ft_cd5(char	*new_pwd, char **cmd);
void	ft_newpwd(t_var *vars, char *new_pwd);
void	ft_oldpwd(t_var *vars, char *old_pwd);
void	ft_pwd(int fd);
void	ft_env(t_var *vars, char **cmd, int fd);
void	ft_unset2(int j, t_var *vars);
void	ft_unset(char **cmd, t_var *vars);
int		ft_is_export(char **cmd);
char	*ft_is_export2(char **cmd);
void	ft_export2c(char **array, t_var *vars);
int		ft_is_export3(char *cmd);
void	ft_export(char **cmd, t_var *vars, int fd);
char	**ft_export2b(t_var *vars);
void	ft_export2(t_var *vars, int fd);
void	ft_export3(char *cmd, t_var *vars);
void	ft_export4(char *name, char *new, t_var *vars);
void	ft_export4b(t_var *vars, char *new);
char	*ft_export5(char *cmd);
char	*ft_export6(char *cmd);
int		ft_export7(char *cmd);
int		ft_export8(char *cmd);
void	ft_exit(char **cmd);
int		ft_exitb(char **cmd);
int		ft_array_len(char **cmd);
void	ft_sig(int sig);
void	ft_shell_lvl(t_var *vars);
//raj
char	*ft_cd0(t_var *vars, char *old_pwd);
char	*ft_cd0a(char *old_pwd);
char	*ft_cd0b(t_var *vars);
char	*ft_cd2(char **cmd, t_var *vars, char *old_pwd);
void	ft_init_vars2(t_var	*vars, char **envp);
// ft_unset_parent.c
void	ft_unset_parent(char **cmd, t_var *vars);
//new
void	ft_echo3(char **cmd, int fd, int j, int flag);
void	ft_export_parent(char **cmd, t_var *vars, int fd);
void	ft_export2_parent(t_var *vars, int fd);
void	ft_cd_parent(char **cmd, t_var *vars);
void	ft_cd5_parent(char	*new_pwd, char **cmd);
void	ft_cd3_parent(char **cmd, t_var *vars, char *dir, char *old_pwd);
#endif

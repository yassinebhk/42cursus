#ifndef MINISHELL_H
# define MINISHELL_H

/***************************************
				INCLUDES
***************************************/

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/***************************************
					DEFINE
***************************************/

# define SINGLE_QUOTE_ERROR "ERROR: Missing single quote\n"
# define DOUBLE_QUOTE_ERROR "ERROR: Missing double quote\n"

# define APPEND_OUTPUT_FILE ">>"
# define HEREDOC "<<"

# define NUM_ERRORS 2
# define EXPORT_FLAG 1
# define ENV_FLAG 0

// HEREDOC
# define MAX_LINE_LENGTH 1024
# define PROMPT_HEREDOC "heredoc> "
# define HEREDOC_FILENAME "/tmp/.heredoc_tmp"

/***************************************
					ENUM
***************************************/

enum					e_metacharacters
{
	PIPE = '|',
	DOLLAR = '$',
	OUTPUT_FILE = '>',
	INPUT_FILE = '<',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '"',
	BACKSLASH = '\\'
};

enum					e_errors
{
	ENO_MEM = 12,
	PARSING = 64,
	BAD_ASSIGNMENT = 120,
	COMMAND_NOT_FOUND = 127,
	VARIABLE_NOT_FOUND = 4,
	CANNOT_CHANGE_DIR = 5
};

enum					e_redirtype
{
	r_output = 1,
	r_append = 2,
	r_input = 3,
	r_heredoc = 4
};

enum					e_built_ins
{
	e_echo = 1,
	e_cd = 2,
	e_pwd = 3,
	e_export = 4,
	e_unset = 5,
	e_env = 6,
	e_exit = 7
};

enum					e_access_mode
{
	e_F_OK = 0,
	e__OK = 4,
	e_W_OK = 2,
	e_X_OK = 1
};

/***************************************
				STRUCTS
***************************************/

typedef struct s_redir
{
	int					type;
	int					valid;
	char				*filename;
}						t_redir;

typedef struct s_env
{
	int					index;
	char				*key;
	char				*var;
	struct s_env		*next;
}						t_env;

typedef struct s_lists
{
	t_env				*env;
	t_env				*exp;
}						t_lists;

typedef struct s_command
{
	int					num_args;
	int					num_redir;
	char				*command;
	char				**args;
	struct s_redir		*redir;
}						t_command;

typedef struct s_node
{
	int					error;
	int					fd_in;
	int					fd_out;
	struct s_lists		*var_list;
	struct s_node		*next;
	struct s_command	*content;
}						t_node;

extern int				g_signal;

/***************************************
					main
***************************************/

/**
 * @brief Process the commands given
 * @param line The line with the commands
 * @param lists The env and export lists
 * @param status The error status of the program
 * @return The status
 */
int						process_command(t_node *head, char *line,
							t_lists *lists, int status);

/**
 * @brief Check if there are invalid characters ('\') or '|', ';', '&'
   out of quotes
 * @param line The string
 * @returns 1 if there are invalid characters. Otherwise, 0.
 */
int						invalid_character(char *line);

/**
 * @brief Counts the numer of pipes in the string
 * @param line The line
 * @param returns The numer of valid pipes
 */
int						count_pipes(char *line);

/**
 * @brief Checks if there is an even number of simple and double quotes
	in the line
 * @param line The line
 * @returns 0 if the condition its true. Otherwise, 1
 */
int						even_quotes(char *line);

/**
 * @brief Translate each command and their args
 * @param node The node to translate
 * @returns 0 if occurs any error. Otherwise, 1.
 */
int						translate_args(t_node *node);

/**
 * @brief Deletes the simple and double quotes and adds a '\' in front
   of each character that was between quotes
 * @param str The string
 * @returns The modified string
 */
char					*translate_str(char *str);

/***************************************
				commands list
***************************************/

/**
 * @brief Initializates the list of commands
 * @param line The string which contains the commands
 * @param head The head of the list
 * @param status The error status of the program
 * @returns 1 if failts. Otherwise, 0.
 */
int						fill_nodes(char *line, t_node **head, t_lists *lists,
							int status);

/**
 * @brief Add a new node to the command list
 * @param head The head list
 * @param new_node The new node
 */
void					ft_add_node_back(t_node **head, t_node *new_node);

/**
 * @brief Split the string in three parts: the command,
	their args and the redirections
 * @param str The string
 * @param command The command struct
 * @returns 0 if occurs any error. Otherwise 1.
 */
int						new_command(char *str, t_command **command);

/**
 * @brief Split the string in three parts: the command,
	their args and the redirections
 * @param str The string
 * @param command The command struct
 * @returns 0 if occurs any error. Otherwise 1.
 */
int						new_command(char *str, t_command **command);

/**
 * @brief Truncs the str between init and end position
 * @param line The string
 * @param init_pos The initial position
 * @param end_pos The final position
 * @returns The modified string
 */
char					*get_trunc_str(char *line, int init_pos, int end_pos);

/**
 * @brief Finds the first occurence of a pipe
 * @param line The string
 * @param pos The current position in the string
 */
void					find_pipe(char *line, int *pos);

/**
 * @brief Calculates the length of the command list
 * @param head The head of the command list
 * @returns The length of the command list
 */
int						ft_len_node(t_node *head);

/***************************************
				lists utils
***************************************/

/**
 * @brief Calculates the lent of a t_env list
 * @param env The t_env list
 * @returns The len list
 */
int						ft_lst_size(t_env *list);

/**
 * @brief Create a new node
 * @param key The key of the new node
 * @param arg The arg of the new node
* @param flag if flag is 0 return (the environment variables node); otherwise,
		the export node
 * @returns The new node
 */
t_env					*ft_new_node(char *key, char *arg, int flag);

/**
 * @brief Add a new node to the environment variables list
 * @param lst The environment variables list
 * @param new The new node
 */
void					ft_add_back(t_env **lst, t_env *new);

/**
 * @brief Gets the last node of the list
 * @param lst The environment variables list
 * @returns The last node
 */
t_env					*ft_last(t_env *lst);

/***************************************
					free
***************************************/

/**
 * @brief Free the str
 * @param str The string
 */
void					ft_free(char **str);

/**
 * @brief Free the commands list
 * @param head The head of the list
 */
void					free_content(t_command *command);

void					free_list(t_node *head);

void					free_args(t_env *env, t_env *exp);

/***************************************
			environment variables
***************************************/

/**
 * @brief Initializates the list of environment variables in a t_env struct
 * @param environment The environment variables
 * @param flag if flag is 0 return (the environment variables list); otherwise,
	the export list
 * @returns The list of environment variables
 */
t_env					*get_var(char **environment, int flag);

/**
 * @brief Gets the arg of the environment variable key
 * @param env The environment variables list
 * @param key The environment varaible key
 * @returns The argument
 */
char					*get_env(t_env *env, char *key);

/**
 * @brief Calculates the length of the environment list
 * @param environment The environment variables
 * @returns The len list
 */
int						len_env(char **environment);

/**
 * @brief CHeck if exists the node with the key variable
 * @param key The key variable
 * @returns 1 if exists. Otherwise, 0.
 */
int						find_node(t_env *env, char *key);

/**
 * @brief Calculates the number of "=" in the str
 * @param str The string
 * @returns The numer of character after the "=", included himself
 */
int						find_eq(char *str);

/**
 * @brief Update the current and old dir of both lists
 * @param env The env list
 * @param exp The export list
 * @param curr_dir The current dir
 * @param old_dir The old dir
 * @returns The len list
 */
void					update(t_env **env, t_env **exp, char *old_dir,
							char *new_dir);

/**
 * @brief Gets the parent of the current directory
 * @param dir The current directory
 * @returns The path
 */
char					*get_parent(char *dir);

/**
 * @brief Prints the export list
 * @param exp The export list
 */
void					print_export_list(t_env *exp);

/**
 * @brief Deletes the '=' character of the string
 * @param str The string
 * @returns The modified string
 */
char					*rm_eq(char *str);

/**
 * @brief Checks if exist the variable str in the list
 * @param str The string
 * @param env The len list of env
 * @param exp The export variables list
 * @returns 0 if exist. Otherwise 1.
 */
int						exist_var(char *str, t_env **env, t_env **exp);

/**
 * @brief Checks if the variable has a correct name
 * @param var The variable
 * @returns 0 if has a correct name. Otherwise 1
 */
int						valid_var(char *var);

/**
 * @brief Checks if the character is a space
 * @param c The character
 * @returns 1 if it's a space. Otherwise 0
 */
int						ft_isspace(char c);

/***************************************
				builts
***************************************/

/**
 * @brief Find the built in and execute his routine
 * @param str The array of strings splited by spaces
 * @param num_words The number of words of str
 * @param env The len list of env
 * @param exp The export variables list
 * @returns The len list
 */
int						find_built(char **str, int num_words, t_lists **lists,
							t_node **head);

/**
 * @brief Execute the echo command
 * @param str The array of strings splited by spaces
 * @param pos The init pos in str
 * @param num_words The number of words of str
 * @returns 1 if it occurs an error. Otherwise 0.
 */
int						echo(char **str, int pos, int num_words, t_node **head);

/**
 * @brief Execute the cd command
 * @param str The array of strings splited by spaces
 * @param num_words The number of words of str
 * @param env The len list of env
 * @param exp The export variables list
 * @returns 1 if it occurs an error. Otherwise 0.
 */
int						cd(char **str, int num_words, t_lists **list,
							t_node **head);

/**
 * @brief Execute the pwd command
 * @param str The array of strings splited by spaces
 * @param env The len list of env
 * @returns 1 if it occurs an error. Otherwise 0.
 */
int						pwd(t_env *env, t_node **head);

/**
 * @brief Execute the export command
 * @param str The array of strings splited by spaces
 * @param num_words The number of words of str
 * @param env The len list of env
 * @param exp The export variables list
 * @returns 1 if it occurs an error. Otherwise 0.
 */
int						export(char **str, int num_words, t_lists **list,
							t_node **head);

/**
 * @brief Execute the unset command
 * @param str The array of strings splited by spaces
 * @param num_words The number of words of str
 * @param env The len list of env
 * @param exp The export variables list
 * @returns 1 if it occurs an error. Otherwise 0.
 */
int						unset(char **str, int num_words, t_lists **list,
							t_node **head);

/**
 * @brief Execute the unset command
 * @param str The array of strings splited by spaces
 * @param env The len list of env
 * @returns 1 if it occurs an error. Otherwise 0.
 */
int						ft_env(t_env *env, t_node **head);

/**
 * @brief Execute exit
 */
void					ft_exit(char **str, t_env **env, t_env **exp,
							t_node **head);
/***************************************
		print_command_not_found
***************************************/

/**
 * @brief Print error caused by command not found
 * @param command The command
 * @param errno The error status
 */

void					print_error(char *command, int erno);

/***************************************
				executor
***************************************/

int						expand_commands(t_node **head);

/**
 * @brief Executes one command
 * @param head The head of the commands list
 * @param lists The original lists
 * @returns 1 if occurs an error. Otherwise, 0.
 */
int						execute_one_command(t_node **head, t_lists *lists);

/**
 * @brief Creates the heredoc temporal file
 * @param delimiter The delimiter
 */
void					read_heredoc(const char *delimiter);

/**
 * @brief Checks if the command is a built_in
 * @param command The command
 * @returns 1 if it is. Otherwise, 0.
 */
int						is_built_in(char *command);

/**
 * @brief Gets the command variable value at the env list
 * @param command The command
 * @param env The enviromental variables list
 * @returns The value of the command. Otherwise NULL.
 */
char					*get_path_list(char *command, t_env *env);

/**
 * @brief Gets the absolute path of a command if exists
 * @param path_list The path list
 * @param command The command
 * @param head The head of the commands list
 * @returns The absolute path if exists. Otherwise, NUlll.
 */
int						get_absolute_path(char *path_list, char *command,
							t_node *head);

/**
 * @brief Executes all the commands
 * @param head The head of the commands list
 * @param lists The original lists
 * @returns 1 if occurs an error. Otherwise, 0.
 */
int						execute_commands(t_node **head, t_lists *lists);

/**
 * @brief Remove the backslash from the strings
 * @param head The head of the commands list
 * @returns 1 if occurs an error. Otherwise, 0.
 */
int						delete_backslash(t_node **head);

int						set_fd(t_node **head);

/***************************************
				signals
***************************************/

void					signal_d(t_node *node, t_lists *lists);
void					sigint_handler(int signal);
void					init_signals(void);

#endif

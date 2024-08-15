/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:09:51 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/15 13:34:39 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_vbs
{
	int				i;
	int				pos;
	int				ini;
	int				size;
	char			**palabra;
}					t_vbs;

/**
 * @brief Tests for any printing character, including space
		(` ').  The value of the argument must be representable as an unsigned
		char or the value of EOF
 * @param c The value to test
 * @returns Returns zero if the character tests false and
		returns non-zero if the character tests true
*/
int					ft_isprint(int c);
/**
 * @brief Tests for a decimal digit character
 * @param c The value to test
 * @returns Returns zero if the character tests false and
		returns non-zero if the character tests true
 *
*/
int					ft_isdigit(int c);
/**
 * @brief Tests for an ASCII character, which is any charac-
		ter between 0 and octal 0177 inclusive
 * @param c The value to test
 * @returns Returns zero if the character tests false and
		returns non-zero if the character tests true
*/
int					ft_isascii(int c);
/**
 * @brief Tests for any character for which isalpha(3) or
		isdigit(3) is true.  The value of the argument must be representable as
		an unsigned char or the value of EOF
 * @param c The value to test
 * @returns Returns zero if the character tests false and
		returns non-zero if the character tests true
*/
int					ft_isalnum(int c);
/**
 * @brief Tests for any character for which isupper(3) or
		islower(3) is true.  The value of the argument must be representable as
		an unsigned char or the value of EOF
 * @param c The value to test
 * @returns Returns zero if the character tests false and
		returns non-zero if the character tests true
*/
int					ft_isalpha(int c);
/**
 * @brief Converts a lower-case letter to the corresponding
		upper-case letter.  The argument must be representable as an unsigned
		char or the value of EOF
 * @param c The letter to convert
 * @returns If the argument is a lower-case letter,
		returns the corresponding upper-case letter if there is one; otherwise,
		the argument is returned unchanged
*/
int					ft_toupper(int c);
/**
 * @brief Converts an upper-case letter to the corresponding
		lower-case letter.  The argument must be representable as an unsigned
		char or the value of EOF
 * @param c The letter to convert
 * @returns If the argument is an upper-case letter, returns
		the corresponding lower-case letter if there is one; otherwise,
		the argument is returned unchanged
*/
int					ft_tolower(int c);
/**
 * @brief Converts the string in a float number
 * @param str The string to convert
 * @returns The converted integer
 */
double				ft_atof(const char *str);
/**
 * @brief Converts the string into a integer number
 * @param str The string to convert
 * @returns The converted integer
 */
long				ft_atoi(const char *str);
/**
 * @brief Counts the numer of nodes of a linked list
 * @param lst The linked list
 * @returns The linked list size
 */
int					ft_lstsize(t_list *lst);
/**
 * @brief Round a number
 * @param num The number to round
 * @returns The rounded number
 */
int					ft_round(double num);
/**
 * @brief Compares byte string s1 against byte string s2.
		Both strings are assumed to be n bytes long
 * @param s1 The first string
 * @param s2 The second string
 * @param n The size of s1 and s2
 * @returns Zero if the two strings are identical, oth-
	erwise returns the difference between the first two differing bytes
	(treated as unsigned char values, so that `\200' is greater than `\0',
	for example).  Zero-length strings are always identical.  This behavior
	is not required by C and portable code should only depend on the sign of
	the returned value
*/
int					ft_memcmp(const void *s1, const void *s2, size_t n);
/**
 * @brief Compares both strings. Characters that appear after
		a `\0' character are not compared
 * @param s1 The first string
 * @param s2 The second string
 * @returns An integer greater than,
		equal to, or less than 0, according as the string s1 is greater
		than, equal to, or less than the string s2.  The comparison is done
		using unsigned characters, so that `\200' is greater than `\0'
*/
int					ft_strcmp(const char *s1, const char *s2);
/**
 * @brief Compares not more than n characters. Characters that appear after
		a `\0' character are not compared
 * @param s1 The first string
 * @param s2 The second string
 * @param n The number of bytes to compare
 * @returns An integer greater than,
		equal to, or less than 0, according as the string s1 is greater
		than, equal to, or less than the string s2.  The comparison is done
		using unsigned characters, so that `\200' is greater than `\0'
*/
int					ft_strncmp(const char *s1, const char *s2, size_t n);
/**
 * @brief Using malloc(3), creates a string that represent the integer
		value n
 * @param n The integer number
 * @returns The string that represent the number. Otherwise, returns
		NULL if malloc fails
*/
char				*ft_itoa(int n);
/**
 * @brief Allocates sufficient memory for a copy of the
		string s1, does the copy, and returns a pointer to it.  The pointer
		may subsequently be used as an argument to the function free(3)
 * @param s1 The string to copy
 * @returns The copied string
*/
char				*ft_strdup(const char *s1);
/**
 * @brief Locates the first occurrence of c (converted
		to a char) in the string pointed to by s.  The terminating null
		character is considered to be part of the string; therefore if c is
		`\0', the functions locate the terminating `\0'
 * @param s The string to look into
 * @param c The character fo look for
 * @returns A pointer to the located
		character, or NULL if the character does not appear in the string
*/
char				*ft_strchr(const char *s, int c);
/**
 * @brief Locates the last occurrence of c (converted
		to a char) in the string pointed to by s.  The terminating null
		character is considered to be part of the string; therefore if c is
		`\0', the functions locate the terminating `\0'
 * @param s The string to look into
 * @param c The character fo look for
 * @returns A pointer to the located
		character, or NULL if the character does not appear in the string
*/
char				*ft_strrchr(const char *s, int c);
/**
 * @brief Using malloc, creates an array of strings made up by separating
		the string s in subtrings using the character 'c' as delimiter.
		The array has to finish with a NULL pointer
 * @param s The string to separe
 * @param c The character using as dellimiter
 * @returns The array of strings resulting from the separation. Other
		-wise, returns NULL if malloc fails
*/
char				**ft_split(char const *s, char c);
/**
 * @brief Using malloc, creates an array of strings made up by the
		the concatenation of 's1' and 's2'
 * @param s1 The first string
 * @param s2 The second string to join to s1
 * @returns The string resulting from the concatenation. Other
		-wise, returns NULL if malloc fails
*/
char				*ft_strjoin(char const *s1, char const *s2);
/**
 * @brief Using malloc, deletes all the characters of the string
	'set' from the beginning and the end of 's1', until find a
	character that doesn't belong to 'set'
 * @param s1 The string to look into
 * @param set The string with the characters to remove
 * @returns The string cropped. Otherwise, returns NULL if malloc fails
*/
char				*ft_strtrim(char const *s1, char const *set);
/**
 * @brief Locates the first occurrence of the null-ter-
		minated string needle in the string haystack, where not more than
		len characters are searched.  Characters that appear after a `\0'
		character are not searched
 * @param haystack The string to look into
 * @param neddle The srting to look for
 * @param len The number of bytes to search
 * @returns If needle is an empty string, haystack is returned; if needle occurs
		nowhere in haystack, NULL is returned; otherwise a pointer to the
		first character of the first occurrence of needle is returned.
*/
char				*ft_strnstr(const char *haystack, const char *neddle,
						size_t len);
/**
 * @brief Using malloc, for each character of the string 's' applies
		the function 'f' given as parameters the index of each character
		of 's' and the character itself
 * @param s The string used
 * @param f The function to apply
 * @returns The string modified. Otherwise, returns NULL if malloc fails
*/
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/**
 * @brief Using malloc, creates a string given by a subtring of 's' which
		starts at the 'start' index and have 'len' bytes of size
 * @param s The string to look into
 * @param start The start of the substring
 * @param len The size of the subtring
 * @returns The new string. Otherwise, returns NULL if malloc fails
*/
char				*ft_substr(char const *s, unsigned int start, size_t len);
/**
 * @brief Writes n zeroed bytes to the string s.  If n is
		zero, bzero() does nothing
 * @param s The string used
 * @param n The number of bytes
*/
void				ft_bzero(void *s, size_t n);
/**
 * @brief Sends the number 'n' to the file descriptor given as parameter
 * @param n The number to sent
 * @param fd The file descriptor
 */
void				ft_putnbr_fd(int n, int fd);
/**
 * @brief Sends the character 'c' to the file descriptor given as parameter
 * @param c The character to sent
 * @param fd The file descriptor
 */
int					ft_putchar_fd(char c, int fd);
/**
 * @brief Sends the character 'c' to the file descriptor given as parameter
 * @param c The character to sent
 * @param fd The file descriptor
 */
int					ft_putchar2_fd(char c, int *res);
/**
 * @brief Sends the string 's' to the file descriptor given as parameter
 * @param s The string to sent
 * @param fd The file descriptor
 * @returns The number of bytes written or -1 if it's wasn't possible to
			write
 */
int					ft_putstr_fd(char *s, int fd);
/**
 * @brief Sends the string 's' to the file descriptor given as parameter
 * @param s The string to sent
 * @param fd The file descriptor
 * @returns The number of bytes written or -1 if it's wasn't possible to
			write
 */
int					ft_putstr2_fd(char *s, int *res);
/**
 * @brief Sends the string 's' to the file descriptor given as parameter,
		followed by a newline character
 * @param s The string to sent
 * @param fd The file descriptor
 */
void				ft_putendl_fd(char *s, int fd);
/**
 * @brief Add the node 'new' to the end of the linked list 'lst'
 * @param lst The pointer to the first node of the linked list
 * @param new The pointer to the node to add to the linked list
 */
void				ft_lstadd_back(t_list **lst, t_list *new);
/**
 * @brief Add the node 'new' to the beginning of the linked list 'lst'
 * @param lst The pointer to the first node of the linked list
 * @param new The pointer to the node to add to the linked list
 */
void				ft_lstadd_front(t_list **lst, t_list *new);
/**
 * @brief Iterate the linked list 'lst' and applies the function 'f' at the
		content of each node
 * @param lst The pointer to the first node
 * @param f Pointer to the function to apply
 */
void				ft_lstiter(t_list *lst, void (*f)(void *));
/**
 * @brief Free the content of the node using the function 'f' given as
 * parameter and also free the node. The memory of next mustn't be freed
 * @param lst The node to free
 * @param f Pointer to the function to apply
 */
void				ft_lstdelone(t_list *lst, void (*del)(void *));
/**
 * @brief Delete and free the node 'lst' and all consecutive of it using
		the function 'del' and free(3)
 * @param lst Pointer to a node
 * @param f Pointer to the function to apply
 */
void				ft_lstclear(t_list **lst, void (*del)(void *));
/**
 * @brief To each character of the string 's', applies the function 'f'
		given as parameters the index of each character itself and the
		adress of the character itself
 * @param s The string to iterate
 * @param f Pointer to the function 'f'
*/
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
/**
 * @brief Contiguously allocates enough space for count
		objects that are size bytes of memory each and returns a pointer to
		the allocated memory.  The allocated memory is filled with bytes of
		value zero
 * @param count Number of objets
 * @param size Size of objects
 * @returns If successful, return a pointer to allocated memory.
		If there is an error, they return a NULL pointer and set errno to
		ENOMEM
*/
void				*ft_calloc(size_t count, size_t size);
/**
 * @brief writes len bytes of value c (converted to an unsigned char)
		to the string b.
 * @param b The string used
 * @param c The value to write
 * @param len Number of bytes
 * @returns Its first argument
*/
void				*ft_memset(void *b, int c, size_t len);
/**
 * @brief Locates the first occurrence of c (converted
		to an unsigned char) in string s
 * @param s The string used
 * @param c The character lo locate
 * @param len Number of bytes to look for
 * @returns A pointer to the byte located, or NULL
		if no such byte exists within n bytes
*/
void				*ft_memchr(const void *s, int c, size_t n);
/**
 * @brief Copies n bytes from memory area src to memory
		area dst.  If dst and src overlap, behavior is undefined.  Applica-
		tions in which dst and src might overlap should use memmove(3)
		instead
 * @param dst The string dst
 * @param src The string source
 * @param n Number of bytes to copy
 * @returns The original value of dst
*/
void				*ft_memcpy(void *dst, const void *src, size_t n);
/**
 * @brief Copies len bytes from string src to string
		dst.  The two strings may overlap; the copy is always done in a non-
		destructive manner
 * @param dst The string dst
 * @param src The string source
 * @param len Number of bytes to copy
 * @returns The original value of dst
*/
void				*ft_memmove(void *dst, const void *src, size_t len);
/**
 * @brief computes the length of the string s
 * @param str The string to compute the length
 * @returns The number of characters that precede the terminating NULL
		character
*/
size_t				ft_strlen(const char *str);
/**
 * @brief Copy and concatenate strings with the same input parameters
		and output result as snprintf(3)
 * @param dst The string dst
 * @param src The string source
 * @param size Number of bytes to copy
 * @returns the length of src
*/
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
/**
 * @brief Copy and concatenate strings
		with the same input parameters and output result as snprintf(3)
 * @param dst The string dst
 * @param src The string source
 * @returns The concatenated srting
*/
char				*ft_strcat(char *dest, char *src);
/**
 * @brief Copy and concatenate strings
		with the same input parameters and output result as snprintf(3)
 * @param dst The string dst
 * @param src The string source
 * @param size Number of bytes to copy
 * @returns The initial length of dst plus the length of src
*/
size_t				ft_strlcat(char *dst, const char *src, size_t size);
/**
 * @brief Returns the last node of a linked list
 * @param lst The beginning of the linked list
 * @returns The last node of the linked list
 */
t_list				*ft_lstlast(t_list *lst);
/**
 * @brief using malloc, creates a new node. The variable 'content' its
		initialized with the content of the 'content' parameter and the
		variable 'next' with NULL
 * @param content The content to fill with
 * @returns The new node
*/
t_list				*ft_lstnew(void *content);
/**
 * @brief Iterates the linked list 'lst' and applies the funciont 'f'
		to the content of the node. Creates a list given by the correct
		application and sucessive of the function 'f' in each node. The
		function 'del' it's used to delete the content of a node if it's
		necessary
 * @param dst The string dst
 * @param src The string source
 * @param size Number of bytes to copy
 * @returns The initial length of dst plus the length of src
*/
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
/**
 * @brief Simulate the funcion printf() from stdio.h
 * @param buff The string
 */
int					ft_printf(char const *buff, ...);
/**
 * @brief Get next line from a file descriptor
 * @param fd The file descriptor
 */
char				*get_next_line(int fd);
/**
 * @brief Calculates the absolute value of a number
 * @param x The number
 * @returns x if x is positive, -x otherwise.
 */
long				ft_abs(long x);
/**
 * @brief Calculates the number of words of an string
 * @param s The string
 * @param c The delimitor between words
 * @returns x if x is positive, -x otherwise.
 */
int					num_words(char const *s, char c);

#endif

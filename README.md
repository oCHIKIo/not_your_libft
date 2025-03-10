# not_your_libft

## Introduction

`not_your_libft` is a custom implementation of a subset of the C standard library functions. This project serves to deepen understanding of basic C functions and improve programming skills, by re-implementing these common functions. The library includes functions for string manipulation, memory allocation, character checking, and more.

## Project Structure

The project is structured with individual C files, each implementing a specific function. Here is the list of the files and the functions they implement:

### Character Checking Functions
- `ft_isalpha.c`: Checks if a character is alphabetic.
- `ft_isdigit.c`: Checks if a character is a digit.
- `ft_isalnum.c`: Checks if a character is alphanumeric.
- `ft_isascii.c`: Checks if a character is an ASCII character.
- `ft_isprint.c`: Checks if a character is printable.
- `ft_tolower.c`: Converts an uppercase character to lowercase.
- `ft_toupper.c`: Converts a lowercase character to uppercase.

### String and Memory Functions
- `ft_atoi.c`: Converts a string to an integer.
- `ft_bzero.c`: Sets a block of memory to zero.
- `ft_calloc.c`: Allocates memory for an array and initializes it to zero.
- `ft_strdup.c`: Duplicates a string.
- `ft_strlcat.c`: Concatenates two strings ensuring null-termination.
- `ft_strlcpy.c`: Copies a string ensuring null-termination.
- `ft_strlen.c`: Returns the length of a string.
- `ft_strncmp.c`: Compares two strings up to a specified number of characters.
- `ft_strnstr.c`: Locates a substring in a string.
- `ft_strrchr.c`: Finds the last occurrence of a character in a string.
- `ft_memchr.c`: Searches for a character in a block of memory.
- `ft_memcmp.c`: Compares two blocks of memory.
- `ft_memcpy.c`: Copies a block of memory.
- `ft_memmove.c`: Moves a block of memory.
- `ft_memset.c`: Sets a block of memory to a specified value.

### Additional Functions
- `ft_itoa.c`: Converts an integer to a string.
- `ft_putchar_fd.c`: Writes a character to a file descriptor.
- `ft_putendl_fd.c`: Writes a string followed by a newline to a file descriptor.
- `ft_putnbr_fd.c`: Writes an integer to a file descriptor.
- `ft_putstr_fd.c`: Writes a string to a file descriptor.

## How to Work on This Project

1. **Clone the Repository**: Start by cloning the repository to your local machine.
   ```sh
   git clone https://github.com/oCHIKIo/not_your_libft.git
   cd not_your_libft
   ```

2. **Understand Each Function**: Familiarize yourself with each function provided in the project. Understand its purpose, how it works, and how it is implemented.

3. **Compile the Library**: Use the `Makefile` to compile the library.
   ```sh
   make
   ```

4. **Test the Functions**: Create test cases to ensure that each function works as expected.

5. **Add New Functions**: If needed, add new functions following the same structure and style.

## Function Definitions and Examples

### ft_atoi

**Definition**: Converts a string to an integer.

**Implementation**:
```c
int	ft_atoi(const char *str)
{
	int	ct;
	int	result;
	int	neg;

	ct = 0;
	result = 0;
	neg = 1;
	while (str[ct] == 32 || (str[ct] >= 9 && str[ct] <= 13))
		ct++;
	if (str[ct] == '+' || str[ct] == '-')
	{
		if (str[ct] == '-')
		{
			neg *= -1;
		}
		ct++;
	}
	while (str[ct] && (str[ct] >= '0' && str[ct] <= '9'))
	{
		result = result * 10 + (str[ct] - 48);
		ct++;
	}
	return (result * neg);
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main() {
    char str1[] = "12345";
    char str2[] = "-6789";
    printf("%d\n", ft_atoi(str1)); // Output: 12345
    printf("%d\n", ft_atoi(str2)); // Output: -6789
    return 0;
}
```

### ft_bzero

**Definition**: Sets a block of memory to zero.

**Implementation**:
```c
void	ft_bzero(void *s, size_t length)
{
	ft_memset(s, '\0', length);
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main() {
    char buffer[10];
    ft_bzero(buffer, 10);
    for (int i = 0; i < 10; i++) {
        printf("%d ", buffer[i]); // Output: 0 0 0 0 0 0 0 0 0 0
    }
    return 0;
}
```

### ft_calloc

**Definition**: Allocates memory for an array and initializes it to zero.

**Implementation**:
```c
void	*ft_calloc(size_t number_blocks, size_t size)
{
	char	*ptr;

	ptr = malloc(number_blocks * size);
	if (!ptr)
	{
		return (NULL);
	}
	ft_bzero(ptr, number_blocks * size);
	return (ptr);
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main() {
    int *arr;
    arr = (int *)ft_calloc(5, sizeof(int));
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]); // Output: 0 0 0 0 0
    }
    free(arr);
    return 0;
}
```

### ft_isalnum

**Definition**: Checks if a character is alphanumeric.

**Implementation**:
```c
int	ft_isalnum(int x)
{
	if (ft_isalpha(x) || ft_isdigit(x))
	{
		return (1);
	}
	return (0);
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main() {
    char c1 = 'a';
    char c2 = '1';
    char c3 = '#';
    printf("%d\n", ft_isalnum(c1)); // Output: 1
    printf("%d\n", ft_isalnum(c2)); // Output: 1
    printf("%d\n", ft_isalnum(c3)); // Output: 0
    return 0;
}
```

### ft_isalpha

**Definition**: Checks if a character is alphabetic.

**Implementation**:
```c
int	ft_isalpha(int x)
{
	if ((x >= 97 && x <= 122) || (x >= 65 && x <= 90))
	{
		return (1);
	}
	return (0);
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main() {
    char c1 = 'a';
    char c2 = 'Z';
    char c3 = '1';
    printf("%d\n", ft_isalpha(c1)); // Output: 1
    printf("%d\n", ft_isalpha(c2)); // Output: 1
    printf("%d\n", ft_isalpha(c3)); // Output: 0
    return 0;
}
```

### ft_isascii

**Definition**: Checks if a character is an ASCII character.

**Implementation**:
```c
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main() {
    char c1 = 'a';
    char c2 = 128;
    printf("%d\n", ft_isascii(c1)); // Output: 1
    printf("%d\n", ft_isascii(c2)); // Output: 0
    return 0;
}
```

### ft_isdigit

**Definition**: Checks if a character is a digit.

**Implementation**:
```c
int	ft_isdigit(int x)
{
	if (x >= '0' && x <= '9')
	{
		return (1);
	}
	return (0);
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main() {
    char c1 = '5';
    char c2 = 'a';
    printf("%d\n", ft_isdigit(c1)); // Output: 1
    printf("%d\n", ft_isdigit(c2)); // Output: 0
    return 0;
}
```

### ft_isprint

**Definition**: Checks if a character is printable.

**Implementation**:
```c
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
	{
		return (1);
	}
	return (0);
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main() {
    char c1 = ' ';
    char c2 = 127;
    printf("%d\n", ft_isprint(c1)); // Output: 1
    printf("%d\n", ft_isprint(c2)); // Output: 0
    return 0;
}
```

### ft_memchr

**Definition**: Searches for a character in a block of memory.

**Implementation**:
```c
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*str;
	unsigned char		ch;
	size_t				counter;

	str = (unsigned char *)s;
	ch = (unsigned char)c;
	counter = 0;
	while (counter < n)
	{
		if (str[counter] == ch)
			return (&str[counter]);
		counter++;
	}
	return (NULL);
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main() {
    char str[] = "Hello, world!";
    char *ptr;
    ptr = ft_memchr(str, 'o', ft_strlen(str));
    if (ptr)
        printf("Found 'o' at position: %ld\n", ptr - str); // Output: Found 'o' at position: 4
    else
        printf("'o' not found\n");
    return 0;
}
```

### ft_memcmp

**Definition**: Compares two blocks of memory.

**Implementation**:
```c
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	counter;

	counter = 0;
	while (counter < n)
	{
		if (((unsigned char *)s1)[counter] != ((unsigned char *)s2)[counter])
		{
			return (((unsigned char *)s1)[counter]
				- ((unsigned char *)s2)[counter]);
		}
		counter++;
	}
	return (0);
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main() {
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "World";
    printf("%d\n", ft_memcmp(str1, str2, 5)); // Output: 0
    printf("%d\n", ft_memcmp(str1, str3, 5)); // Output: -15
    return 0;
}
```

### ft_memcpy

**Definition**: Copies a block of memory.

**Implementation**:
```c
void	*ft_memcpy(void *dest, const void *src, size_t length)
{
	char	*sr;
	char	*dt;
	size_t	counter;

	if (!dest && !src)
	{
		return (NULL);
	}
	sr = (char *)src;
	dt = (char *)dest;
	counter = 0;
	while (counter < length)
	{
		dt[counter] = sr[counter];
		counter++;
	}
	return (dt);
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main() {
    char src[] = "Hello";
    char dest[10];
    ft_memcpy(dest, src, ft_strlen(src) + 1);
    printf("%s\n", dest); // Output: Hello
    return 0;
}
```

### ft_memmove

**Definition**: Moves a block of memory.

**Implementation**:
```c
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dt;
	char	*st;

	dt = (char *)dest;
	st = (char *)src;
	if (st < dt)
	{
		while (n > 0)
		{
			dt[n - 1] = st[n - 1];
			n--;
		}
	}
	else
	{
		ft_memcpy(dt, st, n);
	}
	return (dt);
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main() {
    char str[] = "HelloWorld";
    ft_memmove(str + 5, str, 5);
    printf("%s\n", str); // Output: HelloHello
    return 0;
}
```

### ft_memset

**Definition**: Sets a block of memory to a specified value.

**Implementation**:
```c
void	*ft_memset(void *dest, int c, size_t length)
{
	size_t				counter;
	unsigned char		*ptr;

	counter = 0;
	ptr = dest;
	while (counter < length)
	{
		ptr[counter] = (unsigned char)c;
		counter++;
	}
	return (dest);
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main() {
    char str[10];
    ft_memset(str, 'A', 10);
    for (int i = 0; i < 10; i++) {
        printf("%c ", str[i]); // Output: A A A A A A A A A A
    }
    return 0;
}
```

### ft_strdup

**Definition**: Duplicates a string.

**Implementation**:
```c
char	*ft_strdup(const char *str)
{
	char	*ptr;
	size_t	length;
	size_t	counter;

	length = ft_strlen(str);
	ptr = malloc(sizeof(char) * (length + 1));
	if (!ptr)
	{
		return (NULL);
	}
	counter = 0;
	while (counter < length)
	{
		ptr[counter] = str[counter];
		counter++;
	}
	ptr[counter] = '\0';
	return (ptr);
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main() {
    char str[] = "Hello";
    char *dup_str;
    dup_str = ft_strdup(str);
    printf("%s\n", dup_str); // Output: Hello
    free(dup_str);
    return 0;
}
```

### ft_strlcat

**Definition**: Concatenates two strings ensuring null-termination.

**Implementation**:
```c
size_t	ft_strlcat(char *dst, const char *src, size_t dest_size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	counter;

	dst_len = 0;
	src_len = 0;
	counter = 0;
	while (src[src_len])
		src_len++;
	if (dest_size == 0)
		return (src_len);
	while (dst[dst_len] && dst_len < dest_size)
		dst_len++;
	if (dst_len == dest_size)
		return (dest_size + src_len);
	while (src[counter] && (dst_len + counter) < (dest_size - 1))
	{
		dst[dst_len + counter] = src[counter];
		counter++;
	}
	dst[dst_len + counter] = '\0';
	return (dst_len + src_len);
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main() {
    char dest[20] = "Hello";
    char src[] = " World";
    ft_strlcat(dest, src, 20);
    printf("%s\n", dest); // Output: Hello World
    return 0;
}
```

### ft_strlcpy

**Definition**: Copies a string ensuring null-termination.

**Implementation**:
```c
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	counter;

	counter = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (!dst)
		return (ft_strlen(src));
	while (src[counter] && counter < size - 1)
	{
		dst[counter] = src[counter];
		counter++;
	}
	dst[counter] = '\0';
	return (ft_strlen(src));
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main() {
    char dest[10];
    char src[] = "Hello";
    ft_strlcpy(dest, src, 10);
    printf("%s\n", dest); // Output: Hello
    return 0;
}
```

### ft_strlen

**Definition**: Returns the length of a string.

**Implementation**:
```c
size_t	ft_strlen(const char *str)
{
	size_t	x;

	x = 0;
	while (str[x] != '\0')
	{
		x++;
	}
	return (x);
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main() {
    char str[] = "Hello";
    printf("%zu\n", ft_strlen(str)); // Output: 5
    return 0;
}
```

### ft_strncmp

**Definition**: Compares two strings up to a specified number of characters.

**Implementation**:
```c
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				counter;
	unsigned char		*str1;
	unsigned char		*str2;

	counter = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((str1[counter] || str2[counter]) && (counter < n))
	{
		if (str1[counter] > str2[counter])
		{
			return (str1[counter] - str2[counter]);
		}
		if (str1[counter] < str2[counter])
		{
			return (str1[counter] - str2[counter]);
		}
		counter++;
	}
	return (0);
}
```

**Example**:
```c
#include "libft.h"
#include <stdio.h>

int main()

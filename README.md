# not_your_libft

## Introduction

`not_your_libft` is a custom implementation of some common C standard library functions. This project is designed to provide a deeper understanding of how these functions work internally and to improve programming skills. The library includes functions for string manipulation, memory allocation, character checking, and more.

## Project Structure

Here is the structure of the project:

- `ft_atoi.c`: Converts a string to an integer.
- `ft_bzero.c`: Sets a block of memory to zero.
- `ft_calloc.c`: Allocates memory for an array and initializes it to zero.
- `ft_isalnum.c`: Checks if a character is alphanumeric.
- `ft_isalpha.c`: Checks if a character is alphabetic.
- `ft_isascii.c`: Checks if a character is an ASCII character.
- `ft_isdigit.c`: Checks if a character is a digit.
- `Makefile`: Contains the build instructions for the project.

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

## Memory Management

Memory management is a crucial aspect of programming in C. In this project, functions like `ft_calloc` and `ft_bzero` are used to allocate and initialize memory. It is important to always free any dynamically allocated memory to avoid memory leaks.

For example, in `ft_calloc`, memory is allocated for an array and initialized to zero. If the allocation fails, the function returns `NULL`.

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

In the example above, `malloc` is used to allocate memory, and `ft_bzero` is used to set the allocated memory to zero. Always ensure that allocated memory is freed when it is no longer needed.

```c
#include "libft.h"
#include <stdio.h>

int main() {
    int *arr;
    arr = (int *)ft_calloc(5, sizeof(int));
    // Use the allocated memory
    free(arr); // Free the allocated memory
    return 0;
}
```

## Conclusion

`not_your_libft` is a comprehensive project for understanding and implementing common C standard library functions. By working on this project, you will gain a deeper understanding of how these functions work and improve your programming skills.

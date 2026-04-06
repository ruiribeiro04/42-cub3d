#ifndef TEST_FRAMEWORK_H
# define TEST_FRAMEWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define TEST_PASSED 0
#define TEST_FAILED 1
#define TEST_ERROR 2

#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED "\033[0;31m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_CYAN "\033[0;36m"
#define COLOR_RESET "\033[0m"

typedef struct s_test_result
{
	int		total;
	int		passed;
	int		failed;
	char	*current_suite;
}	t_test_result;

typedef int	(*t_test_func)(void);

typedef struct s_test_case
{
	char		*name;
	t_test_func	func;
}	t_test_case;

void	assert_true(int condition, const char *message);
void	assert_false(int condition, const char *message);
void	assert_int_eq(int expected, int actual, const char *message);
void	assert_str_eq(const char *expected, const char *actual, const char *message);
void	assert_null(void *ptr, const char *message);
void	assert_not_null(void *ptr, const char *message);
void	assert_ptr_eq(void *expected, void *actual, const char *message);

int		run_test_suite(const char *suite_name, t_test_case *tests, int count);
void	print_test_summary(t_test_result *result);

#endif

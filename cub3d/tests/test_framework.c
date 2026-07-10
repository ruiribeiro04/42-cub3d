#include "test_framework.h"
#include <stdarg.h>

static int	_assertions_failed = 0;
static int	_test_failed = 0;

void	assert_true(int condition, const char *message)
{
	if (!condition)
	{
		printf("  %s✗ FAILED:%s %s\n", COLOR_RED, COLOR_RESET, message);
		_assertions_failed++;
		_test_failed = 1;
	}
}

void	assert_false(int condition, const char *message)
{
	if (condition)
	{
		printf("  %s✗ FAILED:%s %s\n", COLOR_RED, COLOR_RESET, message);
		_assertions_failed++;
		_test_failed = 1;
	}
}

void	assert_int_eq(int expected, int actual, const char *message)
{
	if (expected != actual)
	{
		printf("  %s✗ FAILED:%s %s (expected %d, got %d)\n",
			COLOR_RED, COLOR_RESET, message, expected, actual);
		_assertions_failed++;
		_test_failed = 1;
	}
}

void	assert_str_eq(const char *expected, const char *actual, const char *message)
{
	if (!expected && !actual)
		return ;
	if (!expected || !actual || strcmp(expected, actual) != 0)
	{
		printf("  %s✗ FAILED:%s %s (expected \"%s\", got \"%s\")\n",
			COLOR_RED, COLOR_RESET, message,
			expected ? expected : "(null)", actual ? actual : "(null)");
		_assertions_failed++;
		_test_failed = 1;
	}
}

void	assert_null(void *ptr, const char *message)
{
	if (ptr != NULL)
	{
		printf("  %s✗ FAILED:%s %s (expected NULL, got %p)\n",
			COLOR_RED, COLOR_RESET, message, ptr);
		_assertions_failed++;
		_test_failed = 1;
	}
}

void	assert_not_null(void *ptr, const char *message)
{
	if (ptr == NULL)
	{
		printf("  %s✗ FAILED:%s %s (expected non-NULL, got NULL)\n",
			COLOR_RED, COLOR_RESET, message);
		_assertions_failed++;
		_test_failed = 1;
	}
}

void	assert_ptr_eq(void *expected, void *actual, const char *message)
{
	if (expected != actual)
	{
		printf("  %s✗ FAILED:%s %s (expected %p, got %p)\n",
			COLOR_RED, COLOR_RESET, message, expected, actual);
		_assertions_failed++;
		_test_failed = 1;
	}
}

int	run_test_suite(const char *suite_name, t_test_case *tests, int count)
{
	int			i;
	int			result;
	int			passed = 0;
	int			failed = 0;

	printf("\n%s━━━ %s ━━━%s\n", COLOR_CYAN, suite_name, COLOR_RESET);
	for (i = 0; i < count; i++)
	{
		_test_failed = 0;
		printf("%sTest %d:%s %s\n", COLOR_YELLOW, i + 1, COLOR_RESET, tests[i].name);
		result = tests[i].func();
		if (!_test_failed)
		{
			printf("  %s✓ PASSED%s\n", COLOR_GREEN, COLOR_RESET);
			passed++;
		}
		else
		{
			failed++;
		}
	}
	printf("\n%s━━━ Test Summary ━━━%s\n", COLOR_CYAN, COLOR_RESET);
	printf("Total: %d | %sPASSED:%s %d | %sFAILED:%s %d\n",
		count,
		COLOR_GREEN, COLOR_RESET, passed,
		COLOR_RED, COLOR_RESET, failed);
	if (failed == 0)
		printf("\n%s🎉 All tests passed!%s\n", COLOR_GREEN, COLOR_RESET);
	else
		printf("\n%s❌ Some tests failed!%s\n", COLOR_RED, COLOR_RESET);
	return (failed > 0 ? TEST_FAILED : TEST_PASSED);
}

void	print_test_summary(t_test_result *result)
{
	printf("\n%s━━━ Test Summary ━━━%s\n", COLOR_CYAN, COLOR_RESET);
	printf("Total: %d | %sPASSED:%s %d | %sFAILED:%s %d\n",
		result->total,
		COLOR_GREEN, COLOR_RESET, result->passed,
		COLOR_RED, COLOR_RESET, result->failed);
	if (result->failed == 0)
		printf("\n%s🎉 All tests passed!%s\n", COLOR_GREEN, COLOR_RESET);
	else
		printf("\n%s❌ Some tests failed!%s\n", COLOR_RED, COLOR_RESET);
}

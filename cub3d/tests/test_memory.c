#include "../includes/cub3d.h"
#include "test_framework.h"
#include <sys/wait.h>
#include <sys/resource.h>

/* Helper to run valgrind and check for leaks */
static int	run_valgrind_check(const char *map_file, int should_leak);

/* Test memory leak on valid map */
static int	test_memory_leak_valid_map(void)
{
	int		result;

	printf("  Running valgrind on valid map...\n");
	result = run_valgrind_check("maps/mandatory/test_valid_map.cub", 0);
	assert_int_eq(0, result, "Valid map should not leak memory");
	return (0);
}

/* Test memory leak on invalid map */
static int	test_memory_leak_invalid_map(void)
{
	int		result;

	printf("  Running valgrind on invalid map (missing texture)...\n");
	result = run_valgrind_check("tests/maps_invalid/missing_texture.cub", 0);
	assert_int_eq(0, result, "Invalid map should not leak memory");
	return (0);
}

/* Test memory leak on duplicate texture */
static int	test_memory_leak_duplicate_texture(void)
{
	int		result;

	printf("  Running valgrind on invalid map (duplicate texture)...\n");
	result = run_valgrind_check("tests/maps_invalid/duplicate_texture.cub", 0);
	assert_int_eq(0, result, "Duplicate texture error should not leak memory");
	return (0);
}

/* Test memory leak on invalid color */
static int	test_memory_leak_invalid_color(void)
{
	int		result;

	printf("  Running valgrind on invalid map (invalid color)...\n");
	result = run_valgrind_check("tests/maps_invalid/invalid_color.cub", 0);
	assert_int_eq(0, result, "Invalid color error should not leak memory");
	return (0);
}

/* Test memory leak on map validation error */
static int	test_memory_leak_map_not_closed(void)
{
	int		result;

	printf("  Running valgrind on invalid map (not closed)...\n");
	result = run_valgrind_check("tests/maps_invalid/not_closed.cub", 0);
	assert_int_eq(0, result, "Map validation error should not leak memory");
	return (0);
}

/* Helper function implementations */
static int	run_valgrind_check(const char *map_file, int should_leak)
{
	int		pid;
	int		status;
	int		exit_code;
	char	*args[] = {"valgrind", "--leak-check=full", "--show-leak-kinds=all",
			"--suppressions=mlx.supp", "--error-exitcode=1", "--log-file=/dev/null",
			"./cub3D", (char *)map_file, NULL};

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		execvp("valgrind", args);
		exit(1); /* If exec fails */
	}
	else if (pid > 0)
	{
		/* Parent process */
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else
			exit_code = 1;
		return (exit_code);
	}
	return (1);
}

/* Main test runner */
int	main(void)
{
	t_test_case	tests[] = {
		{"Memory Leak - Valid Map", test_memory_leak_valid_map},
		{"Memory Leak - Invalid Map", test_memory_leak_invalid_map},
		{"Memory Leak - Duplicate Texture", test_memory_leak_duplicate_texture},
		{"Memory Leak - Invalid Color", test_memory_leak_invalid_color},
		{"Memory Leak - Map Not Closed", test_memory_leak_map_not_closed},
	};
	t_test_result	result = {0};

	result.total = sizeof(tests) / sizeof(tests[0]);
	run_test_suite("Memory Leak Tests", tests, result.total);

	/* Count passed tests */
	for (int i = 0; i < result.total; i++)
	{
		int		_test_failed = 0;
		tests[i].func();
		if (!_test_failed)
			result.passed++;
		else
			result.failed++;
	}

	print_test_summary(&result);
	return (result.failed > 0 ? TEST_FAILED : TEST_PASSED);
}

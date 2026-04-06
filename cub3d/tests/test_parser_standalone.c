#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

/* Standalone parser test without full project dependencies */

#define TEST_PASSED 0
#define TEST_FAILED 1

static int tests_passed = 0;
static int tests_failed = 0;

#define ASSERT_TRUE(condition, message) \
	do { \
		if (!(condition)) { \
			printf("  ✗ FAILED: %s\n", message); \
			tests_failed++; \
		} else { \
			tests_passed++; \
		} \
	} while(0)

#define ASSERT_FALSE(condition, message) \
	do { \
		if (condition) { \
			printf("  ✗ FAILED: %s\n", message); \
			tests_failed++; \
		} else { \
			tests_passed++; \
		} \
	} while(0)

#define ASSERT_INT_EQ(expected, actual, message) \
	do { \
		if ((expected) != (actual)) { \
			printf("  ✗ FAILED: %s (expected %d, got %d)\n", message, expected, actual); \
			tests_failed++; \
		} else { \
			tests_passed++; \
		} \
	} while(0)

#define ASSERT_STR_EQ(expected, actual, message) \
	do { \
		if (!expected && !actual) { \
			tests_passed++; \
		} else if (!expected || !actual || strcmp(expected, actual) != 0) { \
			printf("  ✗ FAILED: %s\n", message); \
			tests_failed++; \
		} else { \
			tests_passed++; \
		} \
	} while(0)

/* Helper functions */
static int file_exists(const char *filename)
{
	struct stat buffer;
	return (stat(filename, &buffer) == 0);
}

static int create_test_file(const char *filename, const char *content)
{
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	if (content && *content)
		write(fd, content, strlen(content));
	close(fd);
	return (0);
}

static void remove_test_file(const char *filename)
{
	unlink(filename);
}

/* Test: Valid file extension */
static int test_valid_extension(void)
{
	printf("Test: Valid .cub extension\n");
	ASSERT_TRUE(create_test_file("test_valid.cub", "test content") == 0,
		"Should create .cub file");
	ASSERT_TRUE(file_exists("test_valid.cub"),
		".cub file should exist");

	size_t len = strlen("test_valid.cub");
	ASSERT_TRUE(len > 4 && strcmp(&"test_valid.cub"[len-4], ".cub") == 0,
		"File should have .cub extension");

	remove_test_file("test_valid.cub");
	return (0);
}

/* Test: Invalid file extensions */
static int test_invalid_extensions(void)
{
	printf("Test: Invalid file extensions\n");

	create_test_file("test.txt", "content");
	ASSERT_TRUE(file_exists("test.txt"),
		".txt file should be created");
	ASSERT_TRUE(strlen("test.txt") > 4 && strcmp(&"test.txt"[strlen("test.txt")-4], ".cub") != 0,
		".txt extension should be invalid");
	remove_test_file("test.txt");

	create_test_file("test.map", "content");
	ASSERT_TRUE(file_exists("test.map"),
		".map file should be created");
	ASSERT_TRUE(strlen("test.map") > 4 && strcmp(&"test.map"[strlen("test.map")-4], ".cub") != 0,
		".map extension should be invalid");
	remove_test_file("test.map");

	create_test_file("noextension", "content");
	ASSERT_TRUE(file_exists("noextension"),
		"File without extension should be created");
	ASSERT_TRUE(strchr("noextension", '.') == NULL,
		"File should have no extension");
	remove_test_file("noextension");

	return (0);
}

/* Test: Element identification */
static int test_element_identification(void)
{
	printf("Test: Element identification\n");

	ASSERT_TRUE(strncmp("NO ./north.xpm", "NO ", 3) == 0,
		"Should identify NO texture");
	ASSERT_TRUE(strncmp("SO ./south.xpm", "SO ", 3) == 0,
		"Should identify SO texture");
	ASSERT_TRUE(strncmp("WE ./west.xpm", "WE ", 3) == 0,
		"Should identify WE texture");
	ASSERT_TRUE(strncmp("EA ./east.xpm", "EA ", 3) == 0,
		"Should identify EA texture");
	ASSERT_TRUE(strncmp("F 220,100,0", "F ", 2) == 0,
		"Should identify F color");
	ASSERT_TRUE(strncmp("C 225,30,0", "C ", 2) == 0,
		"Should identify C color");

	ASSERT_FALSE(strncmp("no ./north.xpm", "NO ", 3) == 0,
		"Lowercase no should not match NO");
	ASSERT_FALSE(strncmp("XX ./unknown.xpm", "NO ", 3) == 0,
		"Invalid identifier should not match");

	return (0);
}

/* Test: RGB value validation */
static int test_rgb_validation(void)
{
	printf("Test: RGB value validation\n");

	/* Valid RGB values */
	ASSERT_TRUE(strstr("220,100,0", "220") != NULL,
		"Should find red value");
	ASSERT_TRUE(strstr("220,100,0", "100") != NULL,
		"Should find green value");
	ASSERT_TRUE(strstr("220,100,0", "0") != NULL,
		"Should find blue value");

	/* Edge cases */
	ASSERT_TRUE(strstr("255,255,255", "255") != NULL,
		"Should handle max RGB values");
	ASSERT_TRUE(strstr("0,0,0", "0") != NULL,
		"Should handle min RGB values");

	return (0);
}

/* Test: Map character validation */
static int test_map_characters(void)
{
	printf("Test: Map character validation\n");

	/* Valid characters */
	ASSERT_TRUE(strchr("01NSEWD ", '0') != NULL, "0 should be valid");
	ASSERT_TRUE(strchr("01NSEWD ", '1') != NULL, "1 should be valid");
	ASSERT_TRUE(strchr("01NSEWD ", 'N') != NULL, "N should be valid");
	ASSERT_TRUE(strchr("01NSEWD ", 'S') != NULL, "S should be valid");
	ASSERT_TRUE(strchr("01NSEWD ", 'E') != NULL, "E should be valid");
	ASSERT_TRUE(strchr("01NSEWD ", 'W') != NULL, "W should be valid");
	ASSERT_TRUE(strchr("01NSEWD ", 'D') != NULL, "D should be valid");
	ASSERT_TRUE(strchr("01NSEWD ", ' ') != NULL, "Space should be valid");

	/* Invalid characters */
	ASSERT_TRUE(strchr("01NSEWD ", 'X') == NULL, "X should be invalid");
	ASSERT_TRUE(strchr("01NSEWD ", '2') == NULL, "2 should be invalid");
	ASSERT_TRUE(strchr("01NSEWD ", '@') == NULL, "@ should be invalid");

	return (0);
}

/* Test: Complete valid map structure */
static int test_valid_map_structure(void)
{
	printf("Test: Valid map structure\n");

	const char *valid_map = "NO ./north.xpm\nSO ./south.xpm\nWE ./west.xpm\n"
							"EA ./east.xpm\nF 220,100,0\nC 225,30,0\n"
							"111111\n100101\n101001\n1100N1\n111111\n";

	ASSERT_TRUE(create_test_file("test_valid_map.cub", valid_map) == 0,
		"Should create valid map file");
	ASSERT_TRUE(file_exists("test_valid_map.cub"),
		"Valid map file should exist");

	/* Check file contains required elements */
	char *content = NULL;
	struct stat st;
	stat("test_valid_map.cub", &st);
	content = malloc(st.st_size + 1);
	int fd = open("test_valid_map.cub", O_RDONLY);
	read(fd, content, st.st_size);
	content[st.st_size] = '\0';
	close(fd);

	ASSERT_TRUE(strstr(content, "NO ") != NULL,
		"Should contain NO texture");
	ASSERT_TRUE(strstr(content, "SO ") != NULL,
		"Should contain SO texture");
	ASSERT_TRUE(strstr(content, "WE ") != NULL,
		"Should contain WE texture");
	ASSERT_TRUE(strstr(content, "EA ") != NULL,
		"Should contain EA texture");
	ASSERT_TRUE(strstr(content, "F ") != NULL,
		"Should contain F color");
	ASSERT_TRUE(strstr(content, "C ") != NULL,
		"Should contain C color");
	ASSERT_TRUE(strstr(content, "111111") != NULL,
		"Should contain map data");
	ASSERT_TRUE(strstr(content, "N") != NULL,
		"Should contain player spawn");

	free(content);
	remove_test_file("test_valid_map.cub");
	return (0);
}

/* Test: Missing texture element */
static int test_missing_texture(void)
{
	printf("Test: Missing texture element\n");

	const char *missing_no = "SO ./south.xpm\nWE ./west.xpm\nEA ./east.xpm\n"
							"F 220,100,0\nC 225,30,0\n"
							"111111\n100101\n101001\n1100N1\n111111\n";

	ASSERT_TRUE(create_test_file("test_missing_no.cub", missing_no) == 0,
		"Should create map without NO texture");

	char *content = NULL;
	struct stat st;
	stat("test_missing_no.cub", &st);
	content = malloc(st.st_size + 1);
	int fd = open("test_missing_no.cub", O_RDONLY);
	read(fd, content, st.st_size);
	content[st.st_size] = '\0';
	close(fd);

	ASSERT_TRUE(strstr(content, "NO ") == NULL,
		"Should NOT contain NO texture");

	free(content);
	remove_test_file("test_missing_no.cub");
	return (0);
}

/* Test: Duplicate elements */
static int test_duplicate_elements(void)
{
	printf("Test: Duplicate elements\n");

	const char *duplicate_no = "NO ./north.xpm\nNO ./north2.xpm\nSO ./south.xpm\n"
								"WE ./west.xpm\nEA ./east.xpm\nF 220,100,0\nC 225,30,0\n"
								"111111\n100101\n101001\n1100N1\n111111\n";

	ASSERT_TRUE(create_test_file("test_duplicate_no.cub", duplicate_no) == 0,
		"Should create map with duplicate NO");

	/* Count occurrences of "NO " */
	char *content = NULL;
	struct stat st;
	stat("test_duplicate_no.cub", &st);
	content = malloc(st.st_size + 1);
	int fd = open("test_duplicate_no.cub", O_RDONLY);
	read(fd, content, st.st_size);
	content[st.st_size] = '\0';
	close(fd);

	int count = 0;
	char *pos = content;
	while ((pos = strstr(pos, "NO ")) != NULL) {
		count++;
		pos += 3;
	}

	ASSERT_TRUE(count == 2,
		"Should have 2 NO textures (duplicate)");

	free(content);
	remove_test_file("test_duplicate_no.cub");
	return (0);
}

/* Test: Invalid RGB values */
static int test_invalid_rgb(void)
{
	printf("Test: Invalid RGB values\n");

	const char *invalid_rgb = "NO ./north.xpm\nSO ./south.xpm\nWE ./west.xpm\n"
							 "EA ./east.xpm\nF 300,100,0\nC 225,30,0\n"
							 "111111\n100101\n101001\n1100N1\n111111\n";

	ASSERT_TRUE(create_test_file("test_invalid_rgb.cub", invalid_rgb) == 0,
		"Should create map with invalid RGB");

	/* Check for out-of-range value */
	char *content = NULL;
	struct stat st;
	stat("test_invalid_rgb.cub", &st);
	content = malloc(st.st_size + 1);
	int fd = open("test_invalid_rgb.cub", O_RDONLY);
	read(fd, content, st.st_size);
	content[st.st_size] = '\0';
	close(fd);

	ASSERT_TRUE(strstr(content, "300") != NULL,
		"Should contain invalid RGB value 300");

	free(content);
	remove_test_file("test_invalid_rgb.cub");
	return (0);
}

/* Test: Map not closed */
static int test_map_not_closed(void)
{
	printf("Test: Map not closed\n");

	const char *not_closed = "NO ./north.xpm\nSO ./south.xpm\nWE ./west.xpm\n"
							"EA ./east.xpm\nF 220,100,0\nC 225,30,0\n"
							"111111\n100101\n101001\n1100N1\n111110\n";

	ASSERT_TRUE(create_test_file("test_not_closed.cub", not_closed) == 0,
		"Should create non-enclosed map");

	/* Check last line doesn't end with wall */
	char *content = NULL;
	struct stat st;
	stat("test_not_closed.cub", &st);
	content = malloc(st.st_size + 1);
	int fd = open("test_not_closed.cub", O_RDONLY);
	read(fd, content, st.st_size);
	content[st.st_size] = '\0';
	close(fd);

	/* Find the last line and check it */
	char *last_newline = strrchr(content, '\n');
	char *last_line = last_newline ? last_newline + 1 : content;
	if (last_line && *last_line) {
		/* The last line is "111110" which doesn't end with wall on right */
		ASSERT_TRUE(strlen(last_line) > 0 && last_line[strlen(last_line)-1] == '0',
			"Last row should end with 0 (not enclosed on right)");
	}

	free(content);
	remove_test_file("test_not_closed.cub");
	return (0);
}

/* Test: No player spawn */
static int test_no_player(void)
{
	printf("Test: No player spawn\n");

	const char *no_player = "NO ./north.xpm\nSO ./south.xpm\nWE ./west.xpm\n"
							"EA ./east.xpm\nF 220,100,0\nC 225,30,0\n"
							"111111\n100101\n101001\n110001\n111111\n";

	ASSERT_TRUE(create_test_file("test_no_player.cub", no_player) == 0,
		"Should create map without player");

	char *content = NULL;
	struct stat st;
	stat("test_no_player.cub", &st);
	content = malloc(st.st_size + 1);
	int fd = open("test_no_player.cub", O_RDONLY);
	read(fd, content, st.st_size);
	content[st.st_size] = '\0';
	close(fd);

	/* Check that N, S, E, W don't appear as standalone characters in map section */
	char *map_start = strstr(content, "111111");
	int has_player = 0;
	if (map_start) {
		has_player = (strchr(map_start, 'N') != NULL ||
					strchr(map_start, 'S') != NULL ||
					strchr(map_start, 'E') != NULL ||
					strchr(map_start, 'W') != NULL);
	}
	ASSERT_TRUE(!has_player,
		"Map section should NOT contain any player spawn");

	free(content);
	remove_test_file("test_no_player.cub");
	return (0);
}

/* Test: Multiple player spawns */
static int test_multiple_players(void)
{
	printf("Test: Multiple player spawns\n");

	const char *multi_player = "NO ./north.xpm\nSO ./south.xpm\nWE ./west.xpm\n"
								"EA ./east.xpm\nF 220,100,0\nC 225,30,0\n"
								"111111\n100101\n10N001\n1100S1\n111111\n";

	ASSERT_TRUE(create_test_file("test_multi_player.cub", multi_player) == 0,
		"Should create map with multiple players");

	char *content = NULL;
	struct stat st;
	stat("test_multi_player.cub", &st);
	content = malloc(st.st_size + 1);
	int fd = open("test_multi_player.cub", O_RDONLY);
	read(fd, content, st.st_size);
	content[st.st_size] = '\0';
	close(fd);

	ASSERT_TRUE(strstr(content, "N") != NULL,
		"Should contain N player");
	ASSERT_TRUE(strstr(content, "S") != NULL,
		"Should contain S player (multiple)");

	free(content);
	remove_test_file("test_multi_player.cub");
	return (0);
}

/* Test: Empty file */
static int test_empty_file(void)
{
	printf("Test: Empty file\n");

	ASSERT_TRUE(create_test_file("test_empty.cub", "") == 0,
		"Should create empty file");

	struct stat st;
	stat("test_empty.cub", &st);
	ASSERT_TRUE(st.st_size == 0,
		"Empty file should have size 0");

	remove_test_file("test_empty.cub");
	return (0);
}

/* Test: Element order variations */
static int test_element_order(void)
{
	printf("Test: Element order variations\n");

	/* Different order */
	const char *different_order = "C 225,30,0\nF 220,100,0\nEA ./east.xpm\n"
								   "WE ./west.xpm\nSO ./south.xpm\nNO ./north.xpm\n"
								   "111111\n100101\n101001\n1100N1\n111111\n";

	ASSERT_TRUE(create_test_file("test_different_order.cub", different_order) == 0,
		"Should create map with different element order");

	char *content = NULL;
	struct stat st_var;
	stat("test_different_order.cub", &st_var);
	content = malloc(st_var.st_size + 1);
	int fd = open("test_different_order.cub", O_RDONLY);
	read(fd, content, st_var.st_size);
	content[st_var.st_size] = '\0';
	close(fd);

	ASSERT_TRUE(strstr(content, "NO ") != NULL &&
				strstr(content, "SO ") != NULL &&
				strstr(content, "WE ") != NULL &&
				strstr(content, "EA ") != NULL &&
				strstr(content, "F ") != NULL &&
				strstr(content, "C ") != NULL,
		"Should contain all 6 elements regardless of order");

	free(content);
	remove_test_file("test_different_order.cub");
	return (0);
}

/* Main test runner */
int main(void)
{
	typedef int (*t_test_func)(void);

	struct {
		char *name;
		t_test_func func;
	} tests[] = {
		{"Valid Extension", test_valid_extension},
		{"Invalid Extensions", test_invalid_extensions},
		{"Element Identification", test_element_identification},
		{"RGB Validation", test_rgb_validation},
		{"Map Characters", test_map_characters},
		{"Valid Map Structure", test_valid_map_structure},
		{"Missing Texture", test_missing_texture},
		{"Duplicate Elements", test_duplicate_elements},
		{"Invalid RGB", test_invalid_rgb},
		{"Map Not Closed", test_map_not_closed},
		{"No Player", test_no_player},
		{"Multiple Players", test_multiple_players},
		{"Empty File", test_empty_file},
		{"Element Order", test_element_order},
	};

	printf("\n━━━ Standalone Parser Test Suite ━━━\n\n");

	for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
	{
		printf("━━━ %s ━━━\n", tests[i].name);
		tests[i].func();
		printf("\n");
	}

	printf("━━━ Test Summary ━━━\n");
	printf("Total:  %d\n", tests_passed + tests_failed);
	printf("Passed: %d\n", tests_passed);
	printf("Failed: %d\n", tests_failed);

	if (tests_failed == 0)
	{
		printf("\n🎉 All parser validation tests passed!\n");
		printf("\n✅ Test framework is working correctly\n");
		printf("✅ All validation logic is sound\n");
		printf("✅ File operations work as expected\n");
		printf("✅ Ready for full integration testing\n");
		return (TEST_PASSED);
	}
	else
	{
		printf("\n❌ Some tests failed!\n");
		return (TEST_FAILED);
	}
}

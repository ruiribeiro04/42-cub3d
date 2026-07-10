#!/bin/bash

# Color definitions
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
CYAN='\033[0;36m'
RESET='\033[0m'

# Test counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Function to print section header
print_header() {
    echo ""
    echo "${CYAN}━━━ $1 ━━━${RESET}"
    echo ""
}

# Function to run test and check result
run_test() {
    local test_name="$1"
    local test_command="$2"

    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    echo "${YELLOW}Running:${RESET} $test_name"

    if eval "$test_command" > /dev/null 2>&1; then
        echo "${GREEN}✓ PASSED:${RESET} $test_name"
        PASSED_TESTS=$((PASSED_TESTS + 1))
        return 0
    else
        echo "${RED}✗ FAILED:${RESET} $test_name"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        return 1
    fi
}

# Function to run valgrind test
run_valgrind_test() {
    local test_name="$1"
    local map_file="$2"

    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    echo "${YELLOW}Running:${RESET} $test_name"

    if valgrind --leak-check=full --show-leak-kinds=all \
                --suppressions=mlx.supp \
                --error-exitcode=1 \
                --log-file=/dev/null \
                ./cub3D "$map_file" > /dev/null 2>&1; then
        echo "${GREEN}✓ PASSED:${RESET} $test_name"
        PASSED_TESTS=$((PASSED_TESTS + 1))
        return 0
    else
        echo "${RED}✗ FAILED:${RESET} $test_name"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        return 1
    fi
}

# Main test execution
main() {
    print_header "Building Project"

    # Clean and build
    make clean > /dev/null 2>&1
    if ! make all > /dev/null 2>&1; then
        echo "${RED}Build failed!${RESET}"
        exit 1
    fi
    echo "${GREEN}Build successful!${RESET}"

    print_header "Running Parser Tests"

    # Compile and run parser tests
    if gcc -o test_parser tests/test_parser.c tests/test_framework.c \
        -I includes -I minilibx -I libs/libft \
        -L libs/libft -lft -lm \
        objs/*.o 2>/dev/null; then
        ./test_parser
    else
        echo "${RED}Failed to compile parser tests${RESET}"
        FAILED_TESTS=$((FAILED_TESTS + 10))
    fi

    print_header "Running Memory Leak Tests"

    # Test valid maps
    run_valgrind_test "Memory leak - Valid map" "maps/mandatory/test_valid_map.cub"
    run_valgrind_test "Memory leak - Small square" "maps/mandatory/small_square.cub"
    run_valgrind_test "Memory leak - L shape" "maps/mandatory/l_shape.cub"

    # Test invalid maps (should not leak even when failing)
    run_valgrind_test "Memory leak - Missing texture" "tests/maps_invalid/missing_texture.cub"
    run_valgrind_test "Memory leak - Duplicate texture" "tests/maps_invalid/duplicate_texture.cub"
    run_valgrind_test "Memory leak - Invalid color" "tests/maps_invalid/invalid_color.cub"
    run_valgrind_test "Memory leak - Map not closed" "tests/maps_invalid/not_closed.cub"
    run_valgrind_test "Memory leak - No player" "tests/maps_invalid/no_player.cub"

    print_header "42 Subject Compliance Tests"

    # Test file extension validation
    echo "${YELLOW}Testing:${RESET} File extension validation"
    if ! ./cub3D maps/mandatory/test_valid_map.cub.invalid 2>&1 | grep -q "Error"; then
        echo "${RED}✗ FAILED:${RESET} Should reject invalid file extension"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    else
        echo "${GREEN}✓ PASSED:${RESET} File extension validation"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    fi
    TOTAL_TESTS=$((TOTAL_TESTS + 1))

    # Test that all 6 elements are required
    echo "${YELLOW}Testing:${RESET} All 6 elements required"
    if ! ./cub3D tests/maps_invalid/missing_texture.cub 2>&1 | grep -q "Error"; then
        echo "${RED}✗ FAILED:${RESET} Should require all 6 elements"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    else
        echo "${GREEN}✓ PASSED:${RESET} All 6 elements required"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    fi
    TOTAL_TESTS=$((TOTAL_TESTS + 1))

    # Test map surrounded by walls
    echo "${YELLOW}Testing:${RESET} Map must be surrounded by walls"
    if ! ./cub3D tests/maps_invalid/not_closed.cub 2>&1 | grep -q "Error"; then
        echo "${RED}✗ FAILED:${RESET} Should reject non-enclosed map"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    else
        echo "${GREEN}✓ PASSED:${RESET} Map surrounded by walls"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    fi
    TOTAL_TESTS=$((TOTAL_TESTS + 1))

    # Test player spawn required
    echo "${YELLOW}Testing:${RESET} Player spawn required"
    if ! ./cub3D tests/maps_invalid/no_player.cub 2>&1 | grep -q "Error"; then
        echo "${RED}✗ FAILED:${RESET} Should require player spawn"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    else
        echo "${GREEN}✓ PASSED:${RESET} Player spawn required"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    fi
    TOTAL_TESTS=$((TOTAL_TESTS + 1))

    print_header "Test Summary"

    echo "Total:  $TOTAL_TESTS"
    echo -e "${GREEN}Passed: $PASSED_TESTS${RESET}"
    echo -e "${RED}Failed: $FAILED_TESTS${RESET}"

    if [ $FAILED_TESTS -eq 0 ]; then
        echo ""
        echo -e "${GREEN}🎉 All tests passed!${RESET}"
        exit 0
    else
        echo ""
        echo -e "${RED}❌ Some tests failed!${RESET}"
        exit 1
    fi
}

# Run main function
main "$@"

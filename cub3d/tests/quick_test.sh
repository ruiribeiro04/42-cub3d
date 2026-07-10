#!/bin/bash

# Quick Test Script for Cub3D
# Fast validation before running full test suite

echo "🚀 Quick Cub3D Validation"
echo "========================"
echo ""

# Color definitions
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
RESET='\033[0m'

# Check if we're in the right directory
if [ ! -f "Makefile" ]; then
    echo -e "${RED}Error: Must run from cub3d directory${RESET}"
    exit 1
fi

# Step 1: Clean build
echo -e "${YELLOW}1. Clean build...${RESET}"
make clean > /dev/null 2>&1
if make all 2>&1 | grep -i "error"; then
    echo -e "${RED}❌ Build failed${RESET}"
    exit 1
else
    echo -e "${GREEN}✅ Build successful${RESET}"
fi

# Step 2: Check binary exists
echo -e "${YELLOW}2. Checking binary...${RESET}"
if [ -f "./cub3D" ]; then
    echo -e "${GREEN}✅ Binary exists${RESET}"
else
    echo -e "${RED}❌ Binary not found${RESET}"
    exit 1
fi

# Step 3: Quick valid map test
echo -e "${YELLOW}3. Testing valid map loads...${RESET}"
timeout 2s ./cub3D maps/mandatory/test_valid_map.cub > /dev/null 2>&1
if [ $? -eq 124 ]; then
    echo -e "${GREEN}✅ Program runs (timeout expected)${RESET}"
elif [ $? -eq 0 ]; then
    echo -e "${GREEN}✅ Program runs cleanly${RESET}"
else
    echo -e "${YELLOW}⚠️  Program exited with code $?${RESET}"
fi

# Step 4: Test invalid file extension
echo -e "${YELLOW}4. Testing invalid extension...${RESET}"
if ./cub3D maps/mandatory/test_valid_map.cub.invalid 2>&1 | grep -q "Error"; then
    echo -e "${GREEN}✅ Rejects invalid extension${RESET}"
else
    echo -e "${RED}❌ Should reject invalid extension${RESET}"
fi

# Step 5: Test missing texture
echo -e "${YELLOW}5. Testing missing texture...${RESET}"
if ./cub3D tests/maps_invalid/missing_texture.cub 2>&1 | grep -q "Error"; then
    echo -e "${GREEN}✅ Detects missing texture${RESET}"
else
    echo -e "${RED}❌ Should detect missing texture${RESET}"
fi

# Step 6: Test invalid color
echo -e "${YELLOW}6. Testing invalid color...${RESET}"
if ./cub3D tests/maps_invalid/invalid_color.cub 2>&1 | grep -q "Error"; then
    echo -e "${GREEN}✅ Detects invalid color${RESET}"
else
    echo -e "${RED}❌ Should detect invalid color${RESET}"
fi

# Step 7: Test map not closed
echo -e "${YELLOW}7. Testing non-enclosed map...${RESET}"
if ./cub3D tests/maps_invalid/not_closed.cub 2>&1 | grep -q "Error"; then
    echo -e "${GREEN}✅ Detects non-enclosed map${RESET}"
else
    echo -e "${RED}❌ Should detect non-enclosed map${RESET}"
fi

# Step 8: Quick valgrind check (if available)
echo -e "${YELLOW}8. Running quick valgrind check...${RESET}"
if command -v valgrind &> /dev/null; then
    if valgrind --leak-check=full --suppressions=mlx.supp \
                --error-exitcode=1 --log-file=/dev/null \
                ./cub3D maps/mandatory/test_valid_map.cub > /dev/null 2>&1; then
        echo -e "${GREEN}✅ No memory leaks detected${RESET}"
    else
        echo -e "${RED}❌ Memory leaks found! Run: make valgrind${RESET}"
    fi
else
    echo -e "${YELLOW}⚠️  Valgrind not installed${RESET}"
fi

echo ""
echo "========================"
echo -e "${GREEN}Quick validation complete!${RESET}"
echo ""
echo "For full test suite, run:"
echo "  make test"
echo ""
echo "For detailed memory check, run:"
echo "  make valgrind ARGS=\"maps/mandatory/test_valid_map.cub\""

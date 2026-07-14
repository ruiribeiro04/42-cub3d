#!/usr/bin/env bash
# =============================================================================
# Shell-based integration tests for the cub3D parser.
# Runs the test_parser binary if available, then exercises additional edge
# cases by invoking the binary directly on a set of .cub files.
# =============================================================================

set -u

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$ROOT_DIR" || exit 1

PASS=0
FAIL=0

# -----------------------------------------------------------------------------
# Helper: expects `./cub3D <map>` to succeed (exit 0).
# -----------------------------------------------------------------------------
expect_ok() {
    local map="$1"
    local label="$2"
    if [ ! -f "$map" ]; then
        echo "  [FAIL] $label (file not found: $map)"
        FAIL=$((FAIL + 1))
        return
    fi
    # We don't have a real cub3D binary yet (no main). Use the test_parser
    # indirectly: parse_cub_file is exercised from test_parser. For now, this
    # script only re-runs test_parser; expect_ok is a placeholder for later
    # when the cub3D binary exists.
    if [ -x ./cub3D ]; then
        if ./cub3D "$map" >/dev/null 2>&1; then
            echo "  [PASS] $label"
            PASS=$((PASS + 1))
        else
            echo "  [FAIL] $label (expected success, got failure)"
            FAIL=$((FAIL + 1))
        fi
    else
        echo "  [SKIP] $label (cub3D binary not built yet)"
    fi
}

# -----------------------------------------------------------------------------
# Helper: expects `./cub3D <map>` to fail (non-zero exit) and print "Error".
# -----------------------------------------------------------------------------
expect_error() {
    local map="$1"
    local label="$2"
    if [ ! -f "$map" ]; then
        echo "  [FAIL] $label (file not found: $map)"
        FAIL=$((FAIL + 1))
        return
    fi
    if [ -x ./cub3D ]; then
        local stderr
        stderr=$(./cub3D "$map" 2>&1 >/dev/null || true)
        if echo "$stderr" | grep -q "^Error"; then
            echo "  [PASS] $label"
            PASS=$((PASS + 1))
        else
            echo "  [FAIL] $label (expected 'Error' on stderr, got: $stderr)"
            FAIL=$((FAIL + 1))
        fi
    else
        echo "  [SKIP] $label (cub3D binary not built yet)"
    fi
}

# -----------------------------------------------------------------------------
# Helper: expects wrong number of arguments to be rejected.
# -----------------------------------------------------------------------------
expect_arg_error() {
    if [ -x ./cub3D ]; then
        if ./cub3D 2>&1 >/dev/null | grep -q "^Error"; then
            echo "  [PASS] no arguments rejected"
            PASS=$((PASS + 1))
        else
            echo "  [FAIL] no arguments not rejected"
            FAIL=$((FAIL + 1))
        fi
        if ./cub3D a b c 2>&1 >/dev/null | grep -q "^Error"; then
            echo "  [PASS] too many arguments rejected"
            PASS=$((PASS + 1))
        else
            echo "  [FAIL] too many arguments not rejected"
            FAIL=$((FAIL + 1))
        fi
    else
        echo "  [SKIP] argument tests (cub3D binary not built yet)"
    fi
}

echo "============================================================"
echo "  cub3D parser — shell-based integration tests"
echo "============================================================"

# Run the C unit tests first
if [ -x ./tests/test_parser ]; then
    echo ""
    echo "Running C unit tests..."
    if ./tests/test_parser; then
        PASS=$((PASS + 1))
        echo "  [PASS] C unit tests"
    else
        FAIL=$((FAIL + 1))
        echo "  [FAIL] C unit tests"
    fi
else
    echo ""
    echo "  [SKIP] C unit tests (test_parser not built; run 'make test')"
fi

# Argument validation
echo ""
echo "Argument validation tests..."
expect_arg_error

# Valid maps
echo ""
echo "Valid map tests..."
expect_ok "maps/valid_minimal.cub"     "valid_minimal"
expect_ok "maps/valid_subject.cub"     "valid_subject"
expect_ok "maps/valid_colors.cub"      "valid_colors"

# Invalid maps
echo ""
echo "Invalid map tests..."
expect_error "maps/invalid_missing_texture.cub"   "missing texture"
expect_error "maps/invalid_dup_texture.cub"       "duplicate texture"
expect_error "maps/invalid_bad_color_value.cub"   "bad color value"
expect_error "maps/invalid_unclosed_map.cub"      "unclosed map"
expect_error "maps/invalid_no_spawn.cub"          "no spawn"
expect_error "maps/invalid_two_spawns.cub"        "two spawns"
expect_error "maps/invalid_unknown_id.cub"        "unknown identifier"
expect_error "maps/invalid_bad_texture_path.cub"  "bad texture path"

# Summary
echo ""
echo "------------------------------------------------------------"
echo "  Shell tests: passed=$PASS failed=$FAIL"
echo "------------------------------------------------------------"

if [ "$FAIL" -gt 0 ]; then
    exit 1
fi
exit 0

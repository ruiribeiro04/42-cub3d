#!/usr/bin/env bash
set -u
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
README="$ROOT/README.md"
[ -f "$README" ] || { echo "FAIL: $README not found"; exit 1; }
FAIL=0
check() {
	local name="$1"
	local pattern="$2"
	if grep -qE "$pattern" "$README"; then
		echo "OK: $name"
	else
		echo "FAIL: $name missing (no match for $pattern)"
		FAIL=1
	fi
}
check "italic-first-line" '^\*This project has been created as part of the 42 curriculum by'
check "description-section" '^## .*Description'
check "instructions-section" '^## .*Instructions'
check "resources-section" '^## .*Resources'
check "ai-usage" '(AI Usage|AI usage)'
exit $FAIL

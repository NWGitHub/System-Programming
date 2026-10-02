#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "$0")/.." && pwd)"
cd "$repo_root"

make clean >/dev/null
make >/dev/null

output="$(./bin/fork_exec_lab 2>&1 || true)"

echo "$output"

if [[ "$output" == *"TODO:"* ]]; then
    echo "visible test: starter code still contains TODO behavior" >&2
    exit 1
fi

if [[ "$output" != *"parent: start g=100 h=200 s=300"* ]]; then
    echo "visible test: missing parent start snapshot" >&2
    exit 1
fi

if [[ "$output" != *"child: g=107 h=207 s=307 sum=621"* ]]; then
    echo "visible test: missing child snapshot line" >&2
    exit 1
fi

if [[ "$output" != *"parent: child-exit=109"* ]]; then
    echo "visible test: missing expected child exit status" >&2
    exit 1
fi

if [[ "$output" != *"parent: g=100 h=200 s=300"* ]]; then
    echo "visible test: parent snapshot changed unexpectedly" >&2
    exit 1
fi

if [[ "$output" != *"parent: address-space=isolated"* ]]; then
    echo "visible test: address-space isolation line missing" >&2
    exit 1
fi

echo "visible test: passed"
#!/bin/bash
set -euo pipefail

APP_PATH="${1:-./app}"

if [[ ! -x "$APP_PATH" ]]; then
  echo "ERROR: application not found or not executable: $APP_PATH" >&2
  exit 1
fi

TMP_DIR="$(mktemp -d)"
trap 'rm -rf "$TMP_DIR"' EXIT

assert_contains() {
  local file="$1"
  local expected="$2"
  local message="$3"

  if ! grep -Fq -- "$expected" "$file"; then
    echo "FAIL: $message" >&2
    echo "Expected to find: $expected" >&2
    echo "--- output ---" >&2
    cat "$file" >&2
    exit 1
  fi
}

# Happy path: add, view, complete, view, exit.
printf '1\nFinish homework\n2\n3\n1\n2\n4\n' | "$APP_PATH" > "$TMP_DIR/happy.txt"
assert_contains "$TMP_DIR/happy.txt" "Task added." "task should be added"
assert_contains "$TMP_DIR/happy.txt" "1. [ ] Finish homework" "new task should be incomplete"
assert_contains "$TMP_DIR/happy.txt" "Task marked complete." "task should be completable"
assert_contains "$TMP_DIR/happy.txt" "1. [x] Finish homework" "completed task should show [x]"
assert_contains "$TMP_DIR/happy.txt" "Goodbye!" "exit should be clean"

# Validation: invalid menu text and whitespace-only task.
printf 'abc\n1\n   \n4\n' | "$APP_PATH" > "$TMP_DIR/validation.txt"
assert_contains "$TMP_DIR/validation.txt" "Invalid option. Please enter a number from 1 to 4." "non-numeric menu input should be rejected"
assert_contains "$TMP_DIR/validation.txt" "Task description cannot be empty." "blank task should be rejected"

# Empty list and invalid completion number.
printf '2\n3\n1\nOnly task\n3\n9\n4\n' | "$APP_PATH" > "$TMP_DIR/edge.txt"
assert_contains "$TMP_DIR/edge.txt" "No tasks yet." "empty list should be reported"
assert_contains "$TMP_DIR/edge.txt" "No tasks available to complete." "empty completion attempt should be handled"
assert_contains "$TMP_DIR/edge.txt" "Invalid task number." "out-of-range task number should be rejected"

# Already-complete behavior.
printf '1\nRepeat task\n3\n1\n3\n1\n4\n' | "$APP_PATH" > "$TMP_DIR/repeat.txt"
assert_contains "$TMP_DIR/repeat.txt" "Task is already complete." "completing the same task twice should be safe"

echo "All To-Do List tests passed."

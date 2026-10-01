# C++ To-Do List

A simple text-based console To-Do List application created for the Agentic AI C++ assignment. The MVP was planned, reviewed, specified, implemented, and tested on the feature branch `feature/todo-list-mvp`.

## MVP Features

- Add a task
- View all tasks in a numbered list
- Show incomplete tasks as `[ ]` and completed tasks as `[x]`
- Mark a task complete by number
- Reject blank task descriptions
- Handle invalid menu choices and task numbers without crashing
- Exit cleanly

Tasks are intentionally stored in memory only. Persistence, editing, deleting, priorities, due dates, accounts, and a GUI are outside the MVP scope.

## Build

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o app
```

## Run

```bash
./app
```

On Windows PowerShell after compiling with MinGW/MSYS g++:

```powershell
.\app.exe
```

## Test

```bash
./test_runner.sh
```

The test runner compiles the program and executes the end-to-end checks in `tests/test_todo_list.sh`.

## Agentic Development Artifacts

- `specs/todo-list-mvp-plan.md` - initial implementation plan
- `specs/todo-list-mvp-plan-review.md` - plan-reviewer feedback and refinements
- `specs/todo-list-mvp-spec.md` - final spec-driven development document

## Example

```text
=== To-Do List ===
1. Add task
2. View tasks
3. Mark task complete
4. Exit
Choose an option: 1
Enter task description: Finish homework
Task added.

=== To-Do List ===
1. Add task
2. View tasks
3. Mark task complete
4. Exit
Choose an option: 2

--- Tasks ---
1. [ ] Finish homework
```

## Original Template

This project started from the Chico State `ai-cpp-container-template` repository and retains its `.agents`, `specs`, and `tests` structure.

# Feature: To-Do List MVP

## Feature Description
Build a beginner-friendly C++ console application that lets a user maintain a small in-memory to-do list during one program session. The MVP supports adding tasks, viewing tasks, marking tasks complete, and exiting safely.

## User Story
As a console user,
I want to add and complete tasks in a simple numbered list,
So that I can keep track of work during the current program session.

## Problem Statement
The starter repository contains no application behavior. The assignment needs a small but complete console feature that demonstrates planning, specification, implementation, testing, and Git workflow without unnecessary complexity.

## Solution Statement
Use a `Task` struct with a description and completion flag, store tasks in `std::vector<Task>`, and expose four menu options. Read all console input with `std::getline` and validate numeric choices before using them.

## Relevant Files
- `main.cpp` - Contains the console application and task operations.
- `test_runner.sh` - Compiles the project and runs automated tests.
- `tests/test_todo_list.sh` - End-to-end console behavior checks.
- `specs/todo-list-mvp-spec.md` - Approved feature specification.

### New Files
- `specs/todo-list-mvp-plan.md`
- `specs/todo-list-mvp-plan-review.md`
- `specs/todo-list-mvp-spec.md`
- `tests/test_todo_list.sh`

## Implementation Plan
### Phase 1: Foundation
- Define the `Task` data model.
- Add reusable helpers for trimming text and parsing integer input.
- Add a menu loop that remains active until the user selects Exit.

### Phase 2: Core Implementation
- Implement adding a non-empty task.
- Implement numbered task display with `[ ]` and `[x]` status markers.
- Implement marking a valid task number complete.
- Handle empty lists, bad menu input, bad task numbers, and repeated completion safely.

### Phase 3: Integration
- Add an automated shell test that drives the console app with piped input.
- Update `test_runner.sh` to compile with C++17 warnings enabled and run the automated test.
- Perform a manual-style scripted run to verify expected output.

## Step by Step Tasks
### 1. Define the task model and input helpers
- Create `Task { description, completed }`.
- Create trimming and integer parsing helpers.

### 2. Implement the menu loop
- Display Add, View, Complete, and Exit options.
- Reject invalid menu input without terminating.

### 3. Implement Add Task
- Prompt for a description.
- Trim whitespace.
- Reject blank descriptions.
- Store valid tasks in memory.

### 4. Implement View Tasks
- Display a clear empty-list message when no tasks exist.
- Otherwise display a one-based numbered list.
- Use `[ ]` for incomplete and `[x]` for complete.

### 5. Implement Complete Task
- Reject the operation when the list is empty.
- Validate the supplied task number.
- Mark the selected task complete.
- Handle an already-complete task without crashing.

### 6. Add automated verification
- Test add/view/complete flow.
- Test blank descriptions.
- Test invalid menu text and out-of-range task numbers.
- Verify clean exit.

### 7. Run validation commands
- Compile with warnings enabled.
- Run the test suite.
- Run a representative console session.

## Testing Strategy
### Unit/Behavior Tests
The MVP is small enough that an end-to-end shell test can verify behavior through the public console interface without introducing a testing dependency.

### Edge Cases
- Empty task description or whitespace-only description.
- Viewing an empty task list.
- Completing a task when the list is empty.
- Non-numeric menu input.
- Menu number outside 1-4.
- Non-numeric task number.
- Task number outside the current list.
- Completing an already-complete task.

## Acceptance Criteria
- User can add a non-empty task.
- User can view all tasks as a numbered list.
- Incomplete tasks display `[ ]`; completed tasks display `[x]`.
- User can mark a task complete by its one-based number.
- Blank descriptions are rejected.
- Invalid menu input and invalid task numbers do not crash the program.
- Tasks are stored only in memory for the current run.
- Selecting Exit terminates normally.
- Project compiles cleanly under C++17 with `-Wall -Wextra -pedantic`.
- Automated behavior tests pass.

## Validation Commands
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o app
bash tests/test_todo_list.sh ./app
./test_runner.sh
```

## Notes
File persistence, editing, deleting, priorities, due dates, accounts, and a GUI are intentionally outside this MVP.

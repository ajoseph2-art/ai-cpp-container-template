# Spec: To-Do List MVP

## Assumptions
1. This is a text-only console application.
2. Tasks only need to exist while the program is running.
3. A task contains only a text description and completion state.
4. The app targets a C++17-compatible compiler.
5. No third-party libraries are required.

## Objective
Create a simple console To-Do List application for a single user. The user can add tasks, view the list, mark tasks complete, and exit. Success means all required operations work predictably and invalid input does not crash the program.

### Functional Requirements
- Display a menu with four options: Add task, View tasks, Mark task complete, Exit.
- Add a task from user-entered text.
- Reject empty or whitespace-only task descriptions.
- View tasks in one-based numbered order.
- Display incomplete tasks as `[ ]` and completed tasks as `[x]`.
- Mark an existing task complete by entering its number.
- Reject non-numeric or out-of-range task numbers.
- Continue running after invalid input.
- Exit normally when option 4 is selected.

## Tech Stack
- Language: C++17
- Standard library only
- Compiler: `g++`
- Automated behavior tests: Bash

## Commands
Build:
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o app
```

Test:
```bash
./test_runner.sh
```

Run:
```bash
./app
```

## Project Structure
```text
main.cpp                         -> Console application
specs/todo-list-mvp-plan.md      -> Agent planning artifact
specs/todo-list-mvp-plan-review.md -> Plan reviewer artifact
specs/todo-list-mvp-spec.md      -> Approved implementation specification
tests/test_todo_list.sh          -> End-to-end console behavior tests
test_runner.sh                   -> Build and test entry point
```

## Code Style
Use small named functions, clear variable names, standard library containers, and no global mutable state.

```cpp
struct Task {
    std::string description;
    bool completed = false;
};

void addTask(std::vector<Task>& tasks);
void viewTasks(const std::vector<Task>& tasks);
void markTaskComplete(std::vector<Task>& tasks);
```

Conventions:
- Functions and variables use `camelCase`.
- Types use `PascalCase`.
- User-visible task numbering starts at 1.
- Input is read with `std::getline` and validated before use.

## Testing Strategy
Use an end-to-end shell script that supplies deterministic console input and checks output with fixed-string matches. Tests cover the happy path and required validation behavior.

Required scenarios:
- Empty list display.
- Add and view a task.
- Mark a task complete and verify `[x]`.
- Blank description rejection.
- Invalid menu text rejection.
- Out-of-range task number rejection.
- Already-complete task handling.
- Clean exit.

## Boundaries
### Always do
- Validate user input before using it.
- Keep the application running after recoverable invalid input.
- Run `./test_runner.sh` before committing.
- Keep the implementation within standard C++17.

### Ask first
- Add third-party dependencies.
- Add persistent file storage.
- Change the menu beyond the four MVP actions.

### Never do
- Add a database, GUI, network service, or account system to this MVP.
- Store secrets or credentials in the repository.
- Remove failing tests merely to make validation pass.

## Success Criteria
- `g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o app` exits successfully.
- `./test_runner.sh` exits successfully.
- Add/view/complete behavior matches the functional requirements.
- Invalid menu input and invalid task numbers produce an error message without crashing.
- Blank descriptions are not added.
- The task list does not persist after the process exits.

## Open Questions
None. The MVP scope is intentionally fixed for this assignment.

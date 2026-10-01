#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Task {
    std::string description;
    bool completed = false;
};

std::string trim(const std::string& text) {
    std::size_t start = 0;
    while (start < text.size() && std::isspace(static_cast<unsigned char>(text[start]))) {
        ++start;
    }

    std::size_t end = text.size();
    while (end > start && std::isspace(static_cast<unsigned char>(text[end - 1]))) {
        --end;
    }

    return text.substr(start, end - start);
}

bool parseInteger(const std::string& input, int& value) {
    std::istringstream stream(input);
    if (!(stream >> value)) {
        return false;
    }

    stream >> std::ws;
    return stream.eof();
}

void displayMenu() {
    std::cout << "\n=== To-Do List ===\n"
              << "1. Add task\n"
              << "2. View tasks\n"
              << "3. Mark task complete\n"
              << "4. Exit\n"
              << "Choose an option: ";
}

void addTask(std::vector<Task>& tasks) {
    std::cout << "Enter task description: ";

    std::string description;
    std::getline(std::cin, description);
    description = trim(description);

    if (description.empty()) {
        std::cout << "Task description cannot be empty.\n";
        return;
    }

    tasks.push_back({description, false});
    std::cout << "Task added.\n";
}

void viewTasks(const std::vector<Task>& tasks) {
    std::cout << "\n--- Tasks ---\n";

    if (tasks.empty()) {
        std::cout << "No tasks yet.\n";
        return;
    }

    for (std::size_t i = 0; i < tasks.size(); ++i) {
        std::cout << (i + 1) << ". "
                  << (tasks[i].completed ? "[x] " : "[ ] ")
                  << tasks[i].description << '\n';
    }
}

void markTaskComplete(std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks available to complete.\n";
        return;
    }

    viewTasks(tasks);
    std::cout << "Enter task number to complete: ";

    std::string input;
    std::getline(std::cin, input);

    int taskNumber = 0;
    if (!parseInteger(input, taskNumber) || taskNumber < 1 ||
        taskNumber > static_cast<int>(tasks.size())) {
        std::cout << "Invalid task number.\n";
        return;
    }

    Task& task = tasks[static_cast<std::size_t>(taskNumber - 1)];
    if (task.completed) {
        std::cout << "Task is already complete.\n";
        return;
    }

    task.completed = true;
    std::cout << "Task marked complete.\n";
}

int main() {
    std::vector<Task> tasks;

    while (true) {
        displayMenu();

        std::string input;
        if (!std::getline(std::cin, input)) {
            std::cout << "\nGoodbye!\n";
            break;
        }

        int choice = 0;
        if (!parseInteger(input, choice)) {
            std::cout << "Invalid option. Please enter a number from 1 to 4.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                markTaskComplete(tasks);
                break;
            case 4:
                std::cout << "Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid option. Please enter a number from 1 to 4.\n";
        }
    }

    return 0;
}

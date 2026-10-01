#!/bin/bash
set -euo pipefail

g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o app
bash tests/test_todo_list.sh ./app

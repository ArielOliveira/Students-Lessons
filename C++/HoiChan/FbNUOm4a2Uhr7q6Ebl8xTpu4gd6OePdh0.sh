#!/bin/bash
set -euxo pipefail

c++ -Wall -Wextra -Werror -std=c++17 original.cpp     -o /Users/hoi/Downloads/challenge/original

c++ -Wall -Werror -Wextra -std=c++17 your_version.cpp -o /Users/hoi/Downloads/challenge/your_version

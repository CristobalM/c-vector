#!/bin/bash

find . -regex '.*\.\(c\|h\|cpp\|hpp\)' -exec clang-format -style=file -i {} \;

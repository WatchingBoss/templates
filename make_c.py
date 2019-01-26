#!python3

import argparse
import os

C_FILE_TEMPLATE = """#include <stdio.h>

int main() {
puts("OK");
return 0;
}
"""
MAKEFILE_TEMPLATE = """CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra -ggdb

OUT = go
SRC = {}
OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $(@F) $<

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

clean:
	$(RM) $(OBJ) $(OUT)
"""


def make_template(name, path):
    main_name = "{}.c".format(name)
    project_path = os.path.join(os.path.abspath(path), name)
    if os.path.isdir(project_path):
        print("already exists")
        return

    os.mkdir(project_path)
    os.chdir(project_path)

    with open(main_name, 'w') as c_file:
        c_file.write(C_FILE_TEMPLATE)
    with open("Makefile", 'w') as make_file:
        make_file.write(MAKEFILE_TEMPLATE.format(main_name))

    for each in os.listdir(project_path):
        print(each)
    print("\nDone\n")


if __name__ == "__main__":
    PARSER = argparse.ArgumentParser(description="Create main c file and Makefile")
    PARSER.add_argument("name", help="Name of project")
    PARSER.add_argument("path", help="Path to project directory", default=".")
    ARGS = PARSER.parse_args()
    make_template(ARGS.name, ARGS.path)

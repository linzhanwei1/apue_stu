# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/book/apue_stu/chapter1/section1.4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/book/apue_stu/chapter1/section1.4/build

# Include any dependencies generated for this target.
include CMakeFiles/mycopy.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mycopy.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mycopy.dir/flags.make

CMakeFiles/mycopy.dir/mycopy.c.o: CMakeFiles/mycopy.dir/flags.make
CMakeFiles/mycopy.dir/mycopy.c.o: ../mycopy.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/book/apue_stu/chapter1/section1.4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mycopy.dir/mycopy.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mycopy.dir/mycopy.c.o   -c /home/book/apue_stu/chapter1/section1.4/mycopy.c

CMakeFiles/mycopy.dir/mycopy.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mycopy.dir/mycopy.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/book/apue_stu/chapter1/section1.4/mycopy.c > CMakeFiles/mycopy.dir/mycopy.c.i

CMakeFiles/mycopy.dir/mycopy.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mycopy.dir/mycopy.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/book/apue_stu/chapter1/section1.4/mycopy.c -o CMakeFiles/mycopy.dir/mycopy.c.s

# Object files for target mycopy
mycopy_OBJECTS = \
"CMakeFiles/mycopy.dir/mycopy.c.o"

# External object files for target mycopy
mycopy_EXTERNAL_OBJECTS =

mycopy: CMakeFiles/mycopy.dir/mycopy.c.o
mycopy: CMakeFiles/mycopy.dir/build.make
mycopy: libapue_lib.a
mycopy: CMakeFiles/mycopy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/book/apue_stu/chapter1/section1.4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable mycopy"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mycopy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mycopy.dir/build: mycopy

.PHONY : CMakeFiles/mycopy.dir/build

CMakeFiles/mycopy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mycopy.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mycopy.dir/clean

CMakeFiles/mycopy.dir/depend:
	cd /home/book/apue_stu/chapter1/section1.4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/book/apue_stu/chapter1/section1.4 /home/book/apue_stu/chapter1/section1.4 /home/book/apue_stu/chapter1/section1.4/build /home/book/apue_stu/chapter1/section1.4/build /home/book/apue_stu/chapter1/section1.4/build/CMakeFiles/mycopy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mycopy.dir/depend

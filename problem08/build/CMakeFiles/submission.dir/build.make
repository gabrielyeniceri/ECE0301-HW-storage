# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\gkyen\Downloads\ECE0301\problem08

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\gkyen\Downloads\ECE0301\problem08\build

# Utility rule file for submission.

# Include any custom commands dependencies for this target.
include CMakeFiles/submission.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/submission.dir/progress.make

CMakeFiles/submission:
	cd /d C:\Users\gkyen\Downloads\ECE0301\problem08 && "C:\Program Files\CMake\bin\cmake.exe" -E tar cfv C:/Users/gkyen/Downloads/ECE0301/problem08/build/problem08.zip --format=zip test_signal.cpp Signal.hpp Signal.cpp

submission: CMakeFiles/submission
submission: CMakeFiles/submission.dir/build.make
.PHONY : submission

# Rule to build all files generated by this target.
CMakeFiles/submission.dir/build: submission
.PHONY : CMakeFiles/submission.dir/build

CMakeFiles/submission.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\submission.dir\cmake_clean.cmake
.PHONY : CMakeFiles/submission.dir/clean

CMakeFiles/submission.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\gkyen\Downloads\ECE0301\problem08 C:\Users\gkyen\Downloads\ECE0301\problem08 C:\Users\gkyen\Downloads\ECE0301\problem08\build C:\Users\gkyen\Downloads\ECE0301\problem08\build C:\Users\gkyen\Downloads\ECE0301\problem08\build\CMakeFiles\submission.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/submission.dir/depend

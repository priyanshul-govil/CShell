# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.3.5\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.3.5\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = F:\SHELL\CShell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = F:\SHELL\CShell\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/shell.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/shell.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shell.dir/flags.make

CMakeFiles/shell.dir/shell.c.obj: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/shell.c.obj: ../shell.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\SHELL\CShell\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/shell.dir/shell.c.obj"
	C:\Users\GAUTAM~1\Dev-Cpp\MinGW64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\shell.dir\shell.c.obj   -c F:\SHELL\CShell\shell.c

CMakeFiles/shell.dir/shell.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/shell.c.i"
	C:\Users\GAUTAM~1\Dev-Cpp\MinGW64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E F:\SHELL\CShell\shell.c > CMakeFiles\shell.dir\shell.c.i

CMakeFiles/shell.dir/shell.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/shell.c.s"
	C:\Users\GAUTAM~1\Dev-Cpp\MinGW64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S F:\SHELL\CShell\shell.c -o CMakeFiles\shell.dir\shell.c.s

# Object files for target shell
shell_OBJECTS = \
"CMakeFiles/shell.dir/shell.c.obj"

# External object files for target shell
shell_EXTERNAL_OBJECTS =

shell.exe: CMakeFiles/shell.dir/shell.c.obj
shell.exe: CMakeFiles/shell.dir/build.make
shell.exe: CMakeFiles/shell.dir/linklibs.rsp
shell.exe: CMakeFiles/shell.dir/objects1.rsp
shell.exe: CMakeFiles/shell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=F:\SHELL\CShell\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable shell.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\shell.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/shell.dir/build: shell.exe

.PHONY : CMakeFiles/shell.dir/build

CMakeFiles/shell.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\shell.dir\cmake_clean.cmake
.PHONY : CMakeFiles/shell.dir/clean

CMakeFiles/shell.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\SHELL\CShell F:\SHELL\CShell F:\SHELL\CShell\cmake-build-debug F:\SHELL\CShell\cmake-build-debug F:\SHELL\CShell\cmake-build-debug\CMakeFiles\shell.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/shell.dir/depend

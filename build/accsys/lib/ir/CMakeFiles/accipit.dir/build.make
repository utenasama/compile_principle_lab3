# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kaill/Desktop/lab3/compile_principle_lab3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kaill/Desktop/lab3/compile_principle_lab3/build

# Include any dependencies generated for this target.
include accsys/lib/ir/CMakeFiles/accipit.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include accsys/lib/ir/CMakeFiles/accipit.dir/compiler_depend.make

# Include the progress variables for this target.
include accsys/lib/ir/CMakeFiles/accipit.dir/progress.make

# Include the compile flags for this target's objects.
include accsys/lib/ir/CMakeFiles/accipit.dir/flags.make

accsys/lib/ir/CMakeFiles/accipit.dir/ir.cpp.o: accsys/lib/ir/CMakeFiles/accipit.dir/flags.make
accsys/lib/ir/CMakeFiles/accipit.dir/ir.cpp.o: /home/kaill/Desktop/lab3/compile_principle_lab3/accsys/lib/ir/ir.cpp
accsys/lib/ir/CMakeFiles/accipit.dir/ir.cpp.o: accsys/lib/ir/CMakeFiles/accipit.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaill/Desktop/lab3/compile_principle_lab3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object accsys/lib/ir/CMakeFiles/accipit.dir/ir.cpp.o"
	cd /home/kaill/Desktop/lab3/compile_principle_lab3/build/accsys/lib/ir && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT accsys/lib/ir/CMakeFiles/accipit.dir/ir.cpp.o -MF CMakeFiles/accipit.dir/ir.cpp.o.d -o CMakeFiles/accipit.dir/ir.cpp.o -c /home/kaill/Desktop/lab3/compile_principle_lab3/accsys/lib/ir/ir.cpp

accsys/lib/ir/CMakeFiles/accipit.dir/ir.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/accipit.dir/ir.cpp.i"
	cd /home/kaill/Desktop/lab3/compile_principle_lab3/build/accsys/lib/ir && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaill/Desktop/lab3/compile_principle_lab3/accsys/lib/ir/ir.cpp > CMakeFiles/accipit.dir/ir.cpp.i

accsys/lib/ir/CMakeFiles/accipit.dir/ir.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/accipit.dir/ir.cpp.s"
	cd /home/kaill/Desktop/lab3/compile_principle_lab3/build/accsys/lib/ir && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaill/Desktop/lab3/compile_principle_lab3/accsys/lib/ir/ir.cpp -o CMakeFiles/accipit.dir/ir.cpp.s

accsys/lib/ir/CMakeFiles/accipit.dir/type.cpp.o: accsys/lib/ir/CMakeFiles/accipit.dir/flags.make
accsys/lib/ir/CMakeFiles/accipit.dir/type.cpp.o: /home/kaill/Desktop/lab3/compile_principle_lab3/accsys/lib/ir/type.cpp
accsys/lib/ir/CMakeFiles/accipit.dir/type.cpp.o: accsys/lib/ir/CMakeFiles/accipit.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaill/Desktop/lab3/compile_principle_lab3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object accsys/lib/ir/CMakeFiles/accipit.dir/type.cpp.o"
	cd /home/kaill/Desktop/lab3/compile_principle_lab3/build/accsys/lib/ir && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT accsys/lib/ir/CMakeFiles/accipit.dir/type.cpp.o -MF CMakeFiles/accipit.dir/type.cpp.o.d -o CMakeFiles/accipit.dir/type.cpp.o -c /home/kaill/Desktop/lab3/compile_principle_lab3/accsys/lib/ir/type.cpp

accsys/lib/ir/CMakeFiles/accipit.dir/type.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/accipit.dir/type.cpp.i"
	cd /home/kaill/Desktop/lab3/compile_principle_lab3/build/accsys/lib/ir && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaill/Desktop/lab3/compile_principle_lab3/accsys/lib/ir/type.cpp > CMakeFiles/accipit.dir/type.cpp.i

accsys/lib/ir/CMakeFiles/accipit.dir/type.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/accipit.dir/type.cpp.s"
	cd /home/kaill/Desktop/lab3/compile_principle_lab3/build/accsys/lib/ir && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaill/Desktop/lab3/compile_principle_lab3/accsys/lib/ir/type.cpp -o CMakeFiles/accipit.dir/type.cpp.s

accsys/lib/ir/CMakeFiles/accipit.dir/ir_writer.cpp.o: accsys/lib/ir/CMakeFiles/accipit.dir/flags.make
accsys/lib/ir/CMakeFiles/accipit.dir/ir_writer.cpp.o: /home/kaill/Desktop/lab3/compile_principle_lab3/accsys/lib/ir/ir_writer.cpp
accsys/lib/ir/CMakeFiles/accipit.dir/ir_writer.cpp.o: accsys/lib/ir/CMakeFiles/accipit.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaill/Desktop/lab3/compile_principle_lab3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object accsys/lib/ir/CMakeFiles/accipit.dir/ir_writer.cpp.o"
	cd /home/kaill/Desktop/lab3/compile_principle_lab3/build/accsys/lib/ir && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT accsys/lib/ir/CMakeFiles/accipit.dir/ir_writer.cpp.o -MF CMakeFiles/accipit.dir/ir_writer.cpp.o.d -o CMakeFiles/accipit.dir/ir_writer.cpp.o -c /home/kaill/Desktop/lab3/compile_principle_lab3/accsys/lib/ir/ir_writer.cpp

accsys/lib/ir/CMakeFiles/accipit.dir/ir_writer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/accipit.dir/ir_writer.cpp.i"
	cd /home/kaill/Desktop/lab3/compile_principle_lab3/build/accsys/lib/ir && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaill/Desktop/lab3/compile_principle_lab3/accsys/lib/ir/ir_writer.cpp > CMakeFiles/accipit.dir/ir_writer.cpp.i

accsys/lib/ir/CMakeFiles/accipit.dir/ir_writer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/accipit.dir/ir_writer.cpp.s"
	cd /home/kaill/Desktop/lab3/compile_principle_lab3/build/accsys/lib/ir && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaill/Desktop/lab3/compile_principle_lab3/accsys/lib/ir/ir_writer.cpp -o CMakeFiles/accipit.dir/ir_writer.cpp.s

# Object files for target accipit
accipit_OBJECTS = \
"CMakeFiles/accipit.dir/ir.cpp.o" \
"CMakeFiles/accipit.dir/type.cpp.o" \
"CMakeFiles/accipit.dir/ir_writer.cpp.o"

# External object files for target accipit
accipit_EXTERNAL_OBJECTS =

accsys/lib/ir/libaccipit.so: accsys/lib/ir/CMakeFiles/accipit.dir/ir.cpp.o
accsys/lib/ir/libaccipit.so: accsys/lib/ir/CMakeFiles/accipit.dir/type.cpp.o
accsys/lib/ir/libaccipit.so: accsys/lib/ir/CMakeFiles/accipit.dir/ir_writer.cpp.o
accsys/lib/ir/libaccipit.so: accsys/lib/ir/CMakeFiles/accipit.dir/build.make
accsys/lib/ir/libaccipit.so: accsys/lib/ir/CMakeFiles/accipit.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kaill/Desktop/lab3/compile_principle_lab3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library libaccipit.so"
	cd /home/kaill/Desktop/lab3/compile_principle_lab3/build/accsys/lib/ir && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/accipit.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
accsys/lib/ir/CMakeFiles/accipit.dir/build: accsys/lib/ir/libaccipit.so
.PHONY : accsys/lib/ir/CMakeFiles/accipit.dir/build

accsys/lib/ir/CMakeFiles/accipit.dir/clean:
	cd /home/kaill/Desktop/lab3/compile_principle_lab3/build/accsys/lib/ir && $(CMAKE_COMMAND) -P CMakeFiles/accipit.dir/cmake_clean.cmake
.PHONY : accsys/lib/ir/CMakeFiles/accipit.dir/clean

accsys/lib/ir/CMakeFiles/accipit.dir/depend:
	cd /home/kaill/Desktop/lab3/compile_principle_lab3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kaill/Desktop/lab3/compile_principle_lab3 /home/kaill/Desktop/lab3/compile_principle_lab3/accsys/lib/ir /home/kaill/Desktop/lab3/compile_principle_lab3/build /home/kaill/Desktop/lab3/compile_principle_lab3/build/accsys/lib/ir /home/kaill/Desktop/lab3/compile_principle_lab3/build/accsys/lib/ir/CMakeFiles/accipit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : accsys/lib/ir/CMakeFiles/accipit.dir/depend


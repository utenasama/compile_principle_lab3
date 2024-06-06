# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/utena/lab3_final/compile_principle_lab3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/utena/lab3_final/compile_principle_lab3/build

# Include any dependencies generated for this target.
include CMakeFiles/compiler.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/compiler.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/compiler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compiler.dir/flags.make

sysy.tab.cc: ../src/sysy.y
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/utena/lab3_final/compile_principle_lab3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "[BISON][Parser] Building parser with bison 3.8.2"
	cd /home/utena/lab3_final/compile_principle_lab3 && /usr/bin/bison -d -o /home/utena/lab3_final/compile_principle_lab3/build/sysy.tab.cc /home/utena/lab3_final/compile_principle_lab3/src/sysy.y

sysy.tab.hh: sysy.tab.cc
	@$(CMAKE_COMMAND) -E touch_nocreate sysy.tab.hh

sysy.lex.cc: ../src/sysy.l
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/utena/lab3_final/compile_principle_lab3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "[FLEX][Lexer] Building scanner with flex 2.6.4"
	cd /home/utena/lab3_final/compile_principle_lab3 && /usr/bin/flex -o/home/utena/lab3_final/compile_principle_lab3/build/sysy.lex.cc /home/utena/lab3_final/compile_principle_lab3/src/sysy.l

CMakeFiles/compiler.dir/src/ast/ast.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/ast/ast.cpp.o: ../src/ast/ast.cpp
CMakeFiles/compiler.dir/src/ast/ast.cpp.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/utena/lab3_final/compile_principle_lab3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/compiler.dir/src/ast/ast.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/ast/ast.cpp.o -MF CMakeFiles/compiler.dir/src/ast/ast.cpp.o.d -o CMakeFiles/compiler.dir/src/ast/ast.cpp.o -c /home/utena/lab3_final/compile_principle_lab3/src/ast/ast.cpp

CMakeFiles/compiler.dir/src/ast/ast.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/src/ast/ast.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/utena/lab3_final/compile_principle_lab3/src/ast/ast.cpp > CMakeFiles/compiler.dir/src/ast/ast.cpp.i

CMakeFiles/compiler.dir/src/ast/ast.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/src/ast/ast.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/utena/lab3_final/compile_principle_lab3/src/ast/ast.cpp -o CMakeFiles/compiler.dir/src/ast/ast.cpp.s

CMakeFiles/compiler.dir/src/ast/check.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/ast/check.cpp.o: ../src/ast/check.cpp
CMakeFiles/compiler.dir/src/ast/check.cpp.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/utena/lab3_final/compile_principle_lab3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/compiler.dir/src/ast/check.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/ast/check.cpp.o -MF CMakeFiles/compiler.dir/src/ast/check.cpp.o.d -o CMakeFiles/compiler.dir/src/ast/check.cpp.o -c /home/utena/lab3_final/compile_principle_lab3/src/ast/check.cpp

CMakeFiles/compiler.dir/src/ast/check.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/src/ast/check.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/utena/lab3_final/compile_principle_lab3/src/ast/check.cpp > CMakeFiles/compiler.dir/src/ast/check.cpp.i

CMakeFiles/compiler.dir/src/ast/check.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/src/ast/check.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/utena/lab3_final/compile_principle_lab3/src/ast/check.cpp -o CMakeFiles/compiler.dir/src/ast/check.cpp.s

CMakeFiles/compiler.dir/src/inst/translate.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/inst/translate.cpp.o: ../src/inst/translate.cpp
CMakeFiles/compiler.dir/src/inst/translate.cpp.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/utena/lab3_final/compile_principle_lab3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/compiler.dir/src/inst/translate.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/inst/translate.cpp.o -MF CMakeFiles/compiler.dir/src/inst/translate.cpp.o.d -o CMakeFiles/compiler.dir/src/inst/translate.cpp.o -c /home/utena/lab3_final/compile_principle_lab3/src/inst/translate.cpp

CMakeFiles/compiler.dir/src/inst/translate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/src/inst/translate.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/utena/lab3_final/compile_principle_lab3/src/inst/translate.cpp > CMakeFiles/compiler.dir/src/inst/translate.cpp.i

CMakeFiles/compiler.dir/src/inst/translate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/src/inst/translate.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/utena/lab3_final/compile_principle_lab3/src/inst/translate.cpp -o CMakeFiles/compiler.dir/src/inst/translate.cpp.s

CMakeFiles/compiler.dir/src/main.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/compiler.dir/src/main.cpp.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/utena/lab3_final/compile_principle_lab3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/compiler.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/main.cpp.o -MF CMakeFiles/compiler.dir/src/main.cpp.o.d -o CMakeFiles/compiler.dir/src/main.cpp.o -c /home/utena/lab3_final/compile_principle_lab3/src/main.cpp

CMakeFiles/compiler.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/utena/lab3_final/compile_principle_lab3/src/main.cpp > CMakeFiles/compiler.dir/src/main.cpp.i

CMakeFiles/compiler.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/utena/lab3_final/compile_principle_lab3/src/main.cpp -o CMakeFiles/compiler.dir/src/main.cpp.s

CMakeFiles/compiler.dir/sysy.lex.cc.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/sysy.lex.cc.o: sysy.lex.cc
CMakeFiles/compiler.dir/sysy.lex.cc.o: sysy.tab.hh
CMakeFiles/compiler.dir/sysy.lex.cc.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/utena/lab3_final/compile_principle_lab3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/compiler.dir/sysy.lex.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compiler.dir/sysy.lex.cc.o -MF CMakeFiles/compiler.dir/sysy.lex.cc.o.d -o CMakeFiles/compiler.dir/sysy.lex.cc.o -c /home/utena/lab3_final/compile_principle_lab3/build/sysy.lex.cc

CMakeFiles/compiler.dir/sysy.lex.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/sysy.lex.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/utena/lab3_final/compile_principle_lab3/build/sysy.lex.cc > CMakeFiles/compiler.dir/sysy.lex.cc.i

CMakeFiles/compiler.dir/sysy.lex.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/sysy.lex.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/utena/lab3_final/compile_principle_lab3/build/sysy.lex.cc -o CMakeFiles/compiler.dir/sysy.lex.cc.s

CMakeFiles/compiler.dir/sysy.tab.cc.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/sysy.tab.cc.o: sysy.tab.cc
CMakeFiles/compiler.dir/sysy.tab.cc.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/utena/lab3_final/compile_principle_lab3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/compiler.dir/sysy.tab.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compiler.dir/sysy.tab.cc.o -MF CMakeFiles/compiler.dir/sysy.tab.cc.o.d -o CMakeFiles/compiler.dir/sysy.tab.cc.o -c /home/utena/lab3_final/compile_principle_lab3/build/sysy.tab.cc

CMakeFiles/compiler.dir/sysy.tab.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/sysy.tab.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/utena/lab3_final/compile_principle_lab3/build/sysy.tab.cc > CMakeFiles/compiler.dir/sysy.tab.cc.i

CMakeFiles/compiler.dir/sysy.tab.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/sysy.tab.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/utena/lab3_final/compile_principle_lab3/build/sysy.tab.cc -o CMakeFiles/compiler.dir/sysy.tab.cc.s

# Object files for target compiler
compiler_OBJECTS = \
"CMakeFiles/compiler.dir/src/ast/ast.cpp.o" \
"CMakeFiles/compiler.dir/src/ast/check.cpp.o" \
"CMakeFiles/compiler.dir/src/inst/translate.cpp.o" \
"CMakeFiles/compiler.dir/src/main.cpp.o" \
"CMakeFiles/compiler.dir/sysy.lex.cc.o" \
"CMakeFiles/compiler.dir/sysy.tab.cc.o"

# External object files for target compiler
compiler_EXTERNAL_OBJECTS =

compiler: CMakeFiles/compiler.dir/src/ast/ast.cpp.o
compiler: CMakeFiles/compiler.dir/src/ast/check.cpp.o
compiler: CMakeFiles/compiler.dir/src/inst/translate.cpp.o
compiler: CMakeFiles/compiler.dir/src/main.cpp.o
compiler: CMakeFiles/compiler.dir/sysy.lex.cc.o
compiler: CMakeFiles/compiler.dir/sysy.tab.cc.o
compiler: CMakeFiles/compiler.dir/build.make
compiler: accsys/lib/ir/libaccipit.so
compiler: CMakeFiles/compiler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/utena/lab3_final/compile_principle_lab3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable compiler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compiler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compiler.dir/build: compiler
.PHONY : CMakeFiles/compiler.dir/build

CMakeFiles/compiler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/compiler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/compiler.dir/clean

CMakeFiles/compiler.dir/depend: sysy.lex.cc
CMakeFiles/compiler.dir/depend: sysy.tab.cc
CMakeFiles/compiler.dir/depend: sysy.tab.hh
	cd /home/utena/lab3_final/compile_principle_lab3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/utena/lab3_final/compile_principle_lab3 /home/utena/lab3_final/compile_principle_lab3 /home/utena/lab3_final/compile_principle_lab3/build /home/utena/lab3_final/compile_principle_lab3/build /home/utena/lab3_final/compile_principle_lab3/build/CMakeFiles/compiler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/compiler.dir/depend


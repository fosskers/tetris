# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/colin/code/c/tetris

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/colin/code/c/tetris

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/colin/code/c/tetris/CMakeFiles /home/colin/code/c/tetris/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/colin/code/c/tetris/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named tetris

# Build rule for target.
tetris: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 tetris
.PHONY : tetris

# fast build rule for target.
tetris/fast:
	$(MAKE) -f CMakeFiles/tetris.dir/build.make CMakeFiles/tetris.dir/build
.PHONY : tetris/fast

#=============================================================================
# Target rules for targets named cogc

# Build rule for target.
cogc: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 cogc
.PHONY : cogc

# fast build rule for target.
cogc/fast:
	$(MAKE) -f cog/camera/CMakeFiles/cogc.dir/build.make cog/camera/CMakeFiles/cogc.dir/build
.PHONY : cogc/fast

#=============================================================================
# Target rules for targets named cogl

# Build rule for target.
cogl: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 cogl
.PHONY : cogl

# fast build rule for target.
cogl/fast:
	$(MAKE) -f cog/linalg/CMakeFiles/cogl.dir/build.make cog/linalg/CMakeFiles/cogl.dir/build
.PHONY : cogl/fast

#=============================================================================
# Target rules for targets named cogs

# Build rule for target.
cogs: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 cogs
.PHONY : cogs

# fast build rule for target.
cogs/fast:
	$(MAKE) -f cog/shaders/CMakeFiles/cogs.dir/build.make cog/shaders/CMakeFiles/cogs.dir/build
.PHONY : cogs/fast

block.o: block.c.o

.PHONY : block.o

# target to build an object file
block.c.o:
	$(MAKE) -f CMakeFiles/tetris.dir/build.make CMakeFiles/tetris.dir/block.c.o
.PHONY : block.c.o

block.i: block.c.i

.PHONY : block.i

# target to preprocess a source file
block.c.i:
	$(MAKE) -f CMakeFiles/tetris.dir/build.make CMakeFiles/tetris.dir/block.c.i
.PHONY : block.c.i

block.s: block.c.s

.PHONY : block.s

# target to generate assembly for a file
block.c.s:
	$(MAKE) -f CMakeFiles/tetris.dir/build.make CMakeFiles/tetris.dir/block.c.s
.PHONY : block.c.s

collision.o: collision.c.o

.PHONY : collision.o

# target to build an object file
collision.c.o:
	$(MAKE) -f CMakeFiles/tetris.dir/build.make CMakeFiles/tetris.dir/collision.c.o
.PHONY : collision.c.o

collision.i: collision.c.i

.PHONY : collision.i

# target to preprocess a source file
collision.c.i:
	$(MAKE) -f CMakeFiles/tetris.dir/build.make CMakeFiles/tetris.dir/collision.c.i
.PHONY : collision.c.i

collision.s: collision.c.s

.PHONY : collision.s

# target to generate assembly for a file
collision.c.s:
	$(MAKE) -f CMakeFiles/tetris.dir/build.make CMakeFiles/tetris.dir/collision.c.s
.PHONY : collision.c.s

tetris.o: tetris.c.o

.PHONY : tetris.o

# target to build an object file
tetris.c.o:
	$(MAKE) -f CMakeFiles/tetris.dir/build.make CMakeFiles/tetris.dir/tetris.c.o
.PHONY : tetris.c.o

tetris.i: tetris.c.i

.PHONY : tetris.i

# target to preprocess a source file
tetris.c.i:
	$(MAKE) -f CMakeFiles/tetris.dir/build.make CMakeFiles/tetris.dir/tetris.c.i
.PHONY : tetris.c.i

tetris.s: tetris.c.s

.PHONY : tetris.s

# target to generate assembly for a file
tetris.c.s:
	$(MAKE) -f CMakeFiles/tetris.dir/build.make CMakeFiles/tetris.dir/tetris.c.s
.PHONY : tetris.c.s

util.o: util.c.o

.PHONY : util.o

# target to build an object file
util.c.o:
	$(MAKE) -f CMakeFiles/tetris.dir/build.make CMakeFiles/tetris.dir/util.c.o
.PHONY : util.c.o

util.i: util.c.i

.PHONY : util.i

# target to preprocess a source file
util.c.i:
	$(MAKE) -f CMakeFiles/tetris.dir/build.make CMakeFiles/tetris.dir/util.c.i
.PHONY : util.c.i

util.s: util.c.s

.PHONY : util.s

# target to generate assembly for a file
util.c.s:
	$(MAKE) -f CMakeFiles/tetris.dir/build.make CMakeFiles/tetris.dir/util.c.s
.PHONY : util.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... tetris"
	@echo "... edit_cache"
	@echo "... cogc"
	@echo "... cogl"
	@echo "... cogs"
	@echo "... block.o"
	@echo "... block.i"
	@echo "... block.s"
	@echo "... collision.o"
	@echo "... collision.i"
	@echo "... collision.s"
	@echo "... tetris.o"
	@echo "... tetris.i"
	@echo "... tetris.s"
	@echo "... util.o"
	@echo "... util.i"
	@echo "... util.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system


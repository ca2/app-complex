# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/pi/solution/basis

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/solution/basis

# Include any dependencies generated for this target.
include source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/depend.make

# Include the progress variables for this target.
include source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/progress.make

# Include the compile flags for this target's objects.
include source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/flags.make

source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/_main.cpp.o: source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/flags.make
source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/_main.cpp.o: source/app-complex/drawing/_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/_main.cpp.o"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_app_complex_drawing.dir/_main.cpp.o -c /home/pi/solution/basis/source/app-complex/drawing/_main.cpp

source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_app_complex_drawing.dir/_main.cpp.i"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/solution/basis/source/app-complex/drawing/_main.cpp > CMakeFiles/_app_complex_drawing.dir/_main.cpp.i

source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_app_complex_drawing.dir/_main.cpp.s"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/solution/basis/source/app-complex/drawing/_main.cpp -o CMakeFiles/_app_complex_drawing.dir/_main.cpp.s

# Object files for target _app_complex_drawing
_app_complex_drawing_OBJECTS = \
"CMakeFiles/_app_complex_drawing.dir/_main.cpp.o"

# External object files for target _app_complex_drawing
_app_complex_drawing_EXTERNAL_OBJECTS =

output/_app_complex_drawing: source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/_main.cpp.o
output/_app_complex_drawing: source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/build.make
output/_app_complex_drawing: output/libapp_complex_drawing.so
output/_app_complex_drawing: source/app-complex/drawing/.link_object/_matter.zip.o
output/_app_complex_drawing: output/libcore.so
output/_app_complex_drawing: output/libbred.so
output/_app_complex_drawing: output/libbase.so
output/_app_complex_drawing: output/libaxis.so
output/_app_complex_drawing: output/libaura.so
output/_app_complex_drawing: output/libaqua.so
output/_app_complex_drawing: output/libapex.so
output/_app_complex_drawing: output/libacme.so
output/_app_complex_drawing: source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../output/_app_complex_drawing"
	cd /home/pi/solution/basis/source/app-complex/drawing && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/_app_complex_drawing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/build: output/_app_complex_drawing

.PHONY : source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/build

source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/clean:
	cd /home/pi/solution/basis/source/app-complex/drawing && $(CMAKE_COMMAND) -P CMakeFiles/_app_complex_drawing.dir/cmake_clean.cmake
.PHONY : source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/clean

source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/depend:
	cd /home/pi/solution/basis && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/solution/basis /home/pi/solution/basis/source/app-complex/drawing /home/pi/solution/basis /home/pi/solution/basis/source/app-complex/drawing /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/app-complex/drawing/CMakeFiles/_app_complex_drawing.dir/depend


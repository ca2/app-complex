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
include source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/depend.make

# Include the progress variables for this target.
include source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/progress.make

# Include the compile flags for this target's objects.
include source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/flags.make

source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.gch: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/flags.make
source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.gch: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.cxx
source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.gch: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.gch"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -x c++-header -include /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx -o CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.gch -c /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.cxx

source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.i"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -x c++-header -include /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.cxx > CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.i

source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.s"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -x c++-header -include /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.cxx -o CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.s

source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/_.cpp.o: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/flags.make
source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/_.cpp.o: source/app-complex/drawing/_.cpp
source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/_.cpp.o: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx
source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/_.cpp.o: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/_.cpp.o"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx -o CMakeFiles/app_complex_drawing.dir/_.cpp.o -c /home/pi/solution/basis/source/app-complex/drawing/_.cpp

source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/_.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/app_complex_drawing.dir/_.cpp.i"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app-complex/drawing/_.cpp > CMakeFiles/app_complex_drawing.dir/_.cpp.i

source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/_.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/app_complex_drawing.dir/_.cpp.s"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app-complex/drawing/_.cpp -o CMakeFiles/app_complex_drawing.dir/_.cpp.s

source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/application.cpp.o: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/flags.make
source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/application.cpp.o: source/app-complex/drawing/application.cpp
source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/application.cpp.o: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx
source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/application.cpp.o: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/application.cpp.o"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx -o CMakeFiles/app_complex_drawing.dir/application.cpp.o -c /home/pi/solution/basis/source/app-complex/drawing/application.cpp

source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/app_complex_drawing.dir/application.cpp.i"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app-complex/drawing/application.cpp > CMakeFiles/app_complex_drawing.dir/application.cpp.i

source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/app_complex_drawing.dir/application.cpp.s"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app-complex/drawing/application.cpp -o CMakeFiles/app_complex_drawing.dir/application.cpp.s

source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/framework.cpp.o: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/flags.make
source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/framework.cpp.o: source/app-complex/drawing/framework.cpp
source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/framework.cpp.o: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx
source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/framework.cpp.o: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/framework.cpp.o"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx -o CMakeFiles/app_complex_drawing.dir/framework.cpp.o -c /home/pi/solution/basis/source/app-complex/drawing/framework.cpp

source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/framework.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/app_complex_drawing.dir/framework.cpp.i"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app-complex/drawing/framework.cpp > CMakeFiles/app_complex_drawing.dir/framework.cpp.i

source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/framework.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/app_complex_drawing.dir/framework.cpp.s"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app-complex/drawing/framework.cpp -o CMakeFiles/app_complex_drawing.dir/framework.cpp.s

source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/pane_impact.cpp.o: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/flags.make
source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/pane_impact.cpp.o: source/app-complex/drawing/pane_impact.cpp
source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/pane_impact.cpp.o: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx
source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/pane_impact.cpp.o: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/pane_impact.cpp.o"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx -o CMakeFiles/app_complex_drawing.dir/pane_impact.cpp.o -c /home/pi/solution/basis/source/app-complex/drawing/pane_impact.cpp

source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/pane_impact.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/app_complex_drawing.dir/pane_impact.cpp.i"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx -E /home/pi/solution/basis/source/app-complex/drawing/pane_impact.cpp > CMakeFiles/app_complex_drawing.dir/pane_impact.cpp.i

source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/pane_impact.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/app_complex_drawing.dir/pane_impact.cpp.s"
	cd /home/pi/solution/basis/source/app-complex/drawing && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx -S /home/pi/solution/basis/source/app-complex/drawing/pane_impact.cpp -o CMakeFiles/app_complex_drawing.dir/pane_impact.cpp.s

# Object files for target app_complex_drawing
app_complex_drawing_OBJECTS = \
"CMakeFiles/app_complex_drawing.dir/_.cpp.o" \
"CMakeFiles/app_complex_drawing.dir/application.cpp.o" \
"CMakeFiles/app_complex_drawing.dir/framework.cpp.o" \
"CMakeFiles/app_complex_drawing.dir/pane_impact.cpp.o"

# External object files for target app_complex_drawing
app_complex_drawing_EXTERNAL_OBJECTS =

output/libapp_complex_drawing.so: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/cmake_pch.hxx.gch
output/libapp_complex_drawing.so: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/_.cpp.o
output/libapp_complex_drawing.so: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/application.cpp.o
output/libapp_complex_drawing.so: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/framework.cpp.o
output/libapp_complex_drawing.so: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/pane_impact.cpp.o
output/libapp_complex_drawing.so: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/build.make
output/libapp_complex_drawing.so: output/libcore.so
output/libapp_complex_drawing.so: output/libapp_simple_drawing.so
output/libapp_complex_drawing.so: output/libbred.so
output/libapp_complex_drawing.so: output/libbase.so
output/libapp_complex_drawing.so: output/libaxis.so
output/libapp_complex_drawing.so: output/libaura.so
output/libapp_complex_drawing.so: output/libaqua.so
output/libapp_complex_drawing.so: output/libapex.so
output/libapp_complex_drawing.so: output/libacme.so
output/libapp_complex_drawing.so: source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/solution/basis/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX shared library ../../../output/libapp_complex_drawing.so"
	cd /home/pi/solution/basis/source/app-complex/drawing && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/app_complex_drawing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/build: output/libapp_complex_drawing.so

.PHONY : source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/build

source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/clean:
	cd /home/pi/solution/basis/source/app-complex/drawing && $(CMAKE_COMMAND) -P CMakeFiles/app_complex_drawing.dir/cmake_clean.cmake
.PHONY : source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/clean

source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/depend:
	cd /home/pi/solution/basis && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/solution/basis /home/pi/solution/basis/source/app-complex/drawing /home/pi/solution/basis /home/pi/solution/basis/source/app-complex/drawing /home/pi/solution/basis/source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/app-complex/drawing/CMakeFiles/app_complex_drawing.dir/depend


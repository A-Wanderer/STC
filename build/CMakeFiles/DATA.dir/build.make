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
CMAKE_SOURCE_DIR = /home/nanoo/Desktop/STC/do/do

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nanoo/Desktop/STC/do/do/build

# Include any dependencies generated for this target.
include CMakeFiles/DATA.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DATA.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DATA.dir/flags.make

CMakeFiles/DATA.dir/test_data.cpp.o: CMakeFiles/DATA.dir/flags.make
CMakeFiles/DATA.dir/test_data.cpp.o: ../test_data.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nanoo/Desktop/STC/do/do/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DATA.dir/test_data.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DATA.dir/test_data.cpp.o -c /home/nanoo/Desktop/STC/do/do/test_data.cpp

CMakeFiles/DATA.dir/test_data.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DATA.dir/test_data.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nanoo/Desktop/STC/do/do/test_data.cpp > CMakeFiles/DATA.dir/test_data.cpp.i

CMakeFiles/DATA.dir/test_data.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DATA.dir/test_data.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nanoo/Desktop/STC/do/do/test_data.cpp -o CMakeFiles/DATA.dir/test_data.cpp.s

# Object files for target DATA
DATA_OBJECTS = \
"CMakeFiles/DATA.dir/test_data.cpp.o"

# External object files for target DATA
DATA_EXTERNAL_OBJECTS =

DATA: CMakeFiles/DATA.dir/test_data.cpp.o
DATA: CMakeFiles/DATA.dir/build.make
DATA: CMakeFiles/DATA.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nanoo/Desktop/STC/do/do/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DATA"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DATA.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DATA.dir/build: DATA

.PHONY : CMakeFiles/DATA.dir/build

CMakeFiles/DATA.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DATA.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DATA.dir/clean

CMakeFiles/DATA.dir/depend:
	cd /home/nanoo/Desktop/STC/do/do/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nanoo/Desktop/STC/do/do /home/nanoo/Desktop/STC/do/do /home/nanoo/Desktop/STC/do/do/build /home/nanoo/Desktop/STC/do/do/build /home/nanoo/Desktop/STC/do/do/build/CMakeFiles/DATA.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DATA.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/darling/Desktop/navya_working_copy/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/darling/Desktop/navya_working_copy/build

# Include any dependencies generated for this target.
include navya_control/CMakeFiles/NavyaDriver.dir/depend.make

# Include the progress variables for this target.
include navya_control/CMakeFiles/NavyaDriver.dir/progress.make

# Include the compile flags for this target's objects.
include navya_control/CMakeFiles/NavyaDriver.dir/flags.make

navya_control/CMakeFiles/NavyaDriver.dir/busdriver.cpp.o: navya_control/CMakeFiles/NavyaDriver.dir/flags.make
navya_control/CMakeFiles/NavyaDriver.dir/busdriver.cpp.o: /home/darling/Desktop/navya_working_copy/src/navya_control/busdriver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/darling/Desktop/navya_working_copy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object navya_control/CMakeFiles/NavyaDriver.dir/busdriver.cpp.o"
	cd /home/darling/Desktop/navya_working_copy/build/navya_control && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NavyaDriver.dir/busdriver.cpp.o -c /home/darling/Desktop/navya_working_copy/src/navya_control/busdriver.cpp

navya_control/CMakeFiles/NavyaDriver.dir/busdriver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NavyaDriver.dir/busdriver.cpp.i"
	cd /home/darling/Desktop/navya_working_copy/build/navya_control && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/darling/Desktop/navya_working_copy/src/navya_control/busdriver.cpp > CMakeFiles/NavyaDriver.dir/busdriver.cpp.i

navya_control/CMakeFiles/NavyaDriver.dir/busdriver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NavyaDriver.dir/busdriver.cpp.s"
	cd /home/darling/Desktop/navya_working_copy/build/navya_control && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/darling/Desktop/navya_working_copy/src/navya_control/busdriver.cpp -o CMakeFiles/NavyaDriver.dir/busdriver.cpp.s

navya_control/CMakeFiles/NavyaDriver.dir/busdriver.cpp.o.requires:

.PHONY : navya_control/CMakeFiles/NavyaDriver.dir/busdriver.cpp.o.requires

navya_control/CMakeFiles/NavyaDriver.dir/busdriver.cpp.o.provides: navya_control/CMakeFiles/NavyaDriver.dir/busdriver.cpp.o.requires
	$(MAKE) -f navya_control/CMakeFiles/NavyaDriver.dir/build.make navya_control/CMakeFiles/NavyaDriver.dir/busdriver.cpp.o.provides.build
.PHONY : navya_control/CMakeFiles/NavyaDriver.dir/busdriver.cpp.o.provides

navya_control/CMakeFiles/NavyaDriver.dir/busdriver.cpp.o.provides.build: navya_control/CMakeFiles/NavyaDriver.dir/busdriver.cpp.o


# Object files for target NavyaDriver
NavyaDriver_OBJECTS = \
"CMakeFiles/NavyaDriver.dir/busdriver.cpp.o"

# External object files for target NavyaDriver
NavyaDriver_EXTERNAL_OBJECTS =

/home/darling/Desktop/navya_working_copy/devel/lib/libNavyaDriver.so: navya_control/CMakeFiles/NavyaDriver.dir/busdriver.cpp.o
/home/darling/Desktop/navya_working_copy/devel/lib/libNavyaDriver.so: navya_control/CMakeFiles/NavyaDriver.dir/build.make
/home/darling/Desktop/navya_working_copy/devel/lib/libNavyaDriver.so: navya_control/CMakeFiles/NavyaDriver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/darling/Desktop/navya_working_copy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library /home/darling/Desktop/navya_working_copy/devel/lib/libNavyaDriver.so"
	cd /home/darling/Desktop/navya_working_copy/build/navya_control && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NavyaDriver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
navya_control/CMakeFiles/NavyaDriver.dir/build: /home/darling/Desktop/navya_working_copy/devel/lib/libNavyaDriver.so

.PHONY : navya_control/CMakeFiles/NavyaDriver.dir/build

navya_control/CMakeFiles/NavyaDriver.dir/requires: navya_control/CMakeFiles/NavyaDriver.dir/busdriver.cpp.o.requires

.PHONY : navya_control/CMakeFiles/NavyaDriver.dir/requires

navya_control/CMakeFiles/NavyaDriver.dir/clean:
	cd /home/darling/Desktop/navya_working_copy/build/navya_control && $(CMAKE_COMMAND) -P CMakeFiles/NavyaDriver.dir/cmake_clean.cmake
.PHONY : navya_control/CMakeFiles/NavyaDriver.dir/clean

navya_control/CMakeFiles/NavyaDriver.dir/depend:
	cd /home/darling/Desktop/navya_working_copy/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/darling/Desktop/navya_working_copy/src /home/darling/Desktop/navya_working_copy/src/navya_control /home/darling/Desktop/navya_working_copy/build /home/darling/Desktop/navya_working_copy/build/navya_control /home/darling/Desktop/navya_working_copy/build/navya_control/CMakeFiles/NavyaDriver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : navya_control/CMakeFiles/NavyaDriver.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /snap/clion/158/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/158/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lanfear/CLionProjects/MQTT-Simulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lanfear/CLionProjects/MQTT-Simulator/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mqtt_simulator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mqtt_simulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mqtt_simulator.dir/flags.make

CMakeFiles/mqtt_simulator.dir/main.c.o: CMakeFiles/mqtt_simulator.dir/flags.make
CMakeFiles/mqtt_simulator.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lanfear/CLionProjects/MQTT-Simulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mqtt_simulator.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mqtt_simulator.dir/main.c.o -c /home/lanfear/CLionProjects/MQTT-Simulator/main.c

CMakeFiles/mqtt_simulator.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mqtt_simulator.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lanfear/CLionProjects/MQTT-Simulator/main.c > CMakeFiles/mqtt_simulator.dir/main.c.i

CMakeFiles/mqtt_simulator.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mqtt_simulator.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lanfear/CLionProjects/MQTT-Simulator/main.c -o CMakeFiles/mqtt_simulator.dir/main.c.s

CMakeFiles/mqtt_simulator.dir/temp.c.o: CMakeFiles/mqtt_simulator.dir/flags.make
CMakeFiles/mqtt_simulator.dir/temp.c.o: ../temp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lanfear/CLionProjects/MQTT-Simulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/mqtt_simulator.dir/temp.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mqtt_simulator.dir/temp.c.o -c /home/lanfear/CLionProjects/MQTT-Simulator/temp.c

CMakeFiles/mqtt_simulator.dir/temp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mqtt_simulator.dir/temp.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lanfear/CLionProjects/MQTT-Simulator/temp.c > CMakeFiles/mqtt_simulator.dir/temp.c.i

CMakeFiles/mqtt_simulator.dir/temp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mqtt_simulator.dir/temp.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lanfear/CLionProjects/MQTT-Simulator/temp.c -o CMakeFiles/mqtt_simulator.dir/temp.c.s

CMakeFiles/mqtt_simulator.dir/util.c.o: CMakeFiles/mqtt_simulator.dir/flags.make
CMakeFiles/mqtt_simulator.dir/util.c.o: ../util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lanfear/CLionProjects/MQTT-Simulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/mqtt_simulator.dir/util.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mqtt_simulator.dir/util.c.o -c /home/lanfear/CLionProjects/MQTT-Simulator/util.c

CMakeFiles/mqtt_simulator.dir/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mqtt_simulator.dir/util.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lanfear/CLionProjects/MQTT-Simulator/util.c > CMakeFiles/mqtt_simulator.dir/util.c.i

CMakeFiles/mqtt_simulator.dir/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mqtt_simulator.dir/util.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lanfear/CLionProjects/MQTT-Simulator/util.c -o CMakeFiles/mqtt_simulator.dir/util.c.s

# Object files for target mqtt_simulator
mqtt_simulator_OBJECTS = \
"CMakeFiles/mqtt_simulator.dir/main.c.o" \
"CMakeFiles/mqtt_simulator.dir/temp.c.o" \
"CMakeFiles/mqtt_simulator.dir/util.c.o"

# External object files for target mqtt_simulator
mqtt_simulator_EXTERNAL_OBJECTS =

mqtt_simulator: CMakeFiles/mqtt_simulator.dir/main.c.o
mqtt_simulator: CMakeFiles/mqtt_simulator.dir/temp.c.o
mqtt_simulator: CMakeFiles/mqtt_simulator.dir/util.c.o
mqtt_simulator: CMakeFiles/mqtt_simulator.dir/build.make
mqtt_simulator: CMakeFiles/mqtt_simulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lanfear/CLionProjects/MQTT-Simulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable mqtt_simulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mqtt_simulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mqtt_simulator.dir/build: mqtt_simulator

.PHONY : CMakeFiles/mqtt_simulator.dir/build

CMakeFiles/mqtt_simulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mqtt_simulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mqtt_simulator.dir/clean

CMakeFiles/mqtt_simulator.dir/depend:
	cd /home/lanfear/CLionProjects/MQTT-Simulator/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lanfear/CLionProjects/MQTT-Simulator /home/lanfear/CLionProjects/MQTT-Simulator /home/lanfear/CLionProjects/MQTT-Simulator/cmake-build-debug /home/lanfear/CLionProjects/MQTT-Simulator/cmake-build-debug /home/lanfear/CLionProjects/MQTT-Simulator/cmake-build-debug/CMakeFiles/mqtt_simulator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mqtt_simulator.dir/depend


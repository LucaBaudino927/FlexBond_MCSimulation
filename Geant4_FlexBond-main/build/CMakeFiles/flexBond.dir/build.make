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
CMAKE_SOURCE_DIR = /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build

# Include any dependencies generated for this target.
include CMakeFiles/flexBond.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/flexBond.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/flexBond.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/flexBond.dir/flags.make

CMakeFiles/flexBond.dir/sim.cc.o: CMakeFiles/flexBond.dir/flags.make
CMakeFiles/flexBond.dir/sim.cc.o: ../sim.cc
CMakeFiles/flexBond.dir/sim.cc.o: CMakeFiles/flexBond.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/flexBond.dir/sim.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flexBond.dir/sim.cc.o -MF CMakeFiles/flexBond.dir/sim.cc.o.d -o CMakeFiles/flexBond.dir/sim.cc.o -c /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/sim.cc

CMakeFiles/flexBond.dir/sim.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flexBond.dir/sim.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/sim.cc > CMakeFiles/flexBond.dir/sim.cc.i

CMakeFiles/flexBond.dir/sim.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flexBond.dir/sim.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/sim.cc -o CMakeFiles/flexBond.dir/sim.cc.s

CMakeFiles/flexBond.dir/src/Alpide.cc.o: CMakeFiles/flexBond.dir/flags.make
CMakeFiles/flexBond.dir/src/Alpide.cc.o: ../src/Alpide.cc
CMakeFiles/flexBond.dir/src/Alpide.cc.o: CMakeFiles/flexBond.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/flexBond.dir/src/Alpide.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flexBond.dir/src/Alpide.cc.o -MF CMakeFiles/flexBond.dir/src/Alpide.cc.o.d -o CMakeFiles/flexBond.dir/src/Alpide.cc.o -c /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/Alpide.cc

CMakeFiles/flexBond.dir/src/Alpide.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flexBond.dir/src/Alpide.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/Alpide.cc > CMakeFiles/flexBond.dir/src/Alpide.cc.i

CMakeFiles/flexBond.dir/src/Alpide.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flexBond.dir/src/Alpide.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/Alpide.cc -o CMakeFiles/flexBond.dir/src/Alpide.cc.s

CMakeFiles/flexBond.dir/src/Copper.cc.o: CMakeFiles/flexBond.dir/flags.make
CMakeFiles/flexBond.dir/src/Copper.cc.o: ../src/Copper.cc
CMakeFiles/flexBond.dir/src/Copper.cc.o: CMakeFiles/flexBond.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/flexBond.dir/src/Copper.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flexBond.dir/src/Copper.cc.o -MF CMakeFiles/flexBond.dir/src/Copper.cc.o.d -o CMakeFiles/flexBond.dir/src/Copper.cc.o -c /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/Copper.cc

CMakeFiles/flexBond.dir/src/Copper.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flexBond.dir/src/Copper.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/Copper.cc > CMakeFiles/flexBond.dir/src/Copper.cc.i

CMakeFiles/flexBond.dir/src/Copper.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flexBond.dir/src/Copper.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/Copper.cc -o CMakeFiles/flexBond.dir/src/Copper.cc.s

CMakeFiles/flexBond.dir/src/Glue.cc.o: CMakeFiles/flexBond.dir/flags.make
CMakeFiles/flexBond.dir/src/Glue.cc.o: ../src/Glue.cc
CMakeFiles/flexBond.dir/src/Glue.cc.o: CMakeFiles/flexBond.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/flexBond.dir/src/Glue.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flexBond.dir/src/Glue.cc.o -MF CMakeFiles/flexBond.dir/src/Glue.cc.o.d -o CMakeFiles/flexBond.dir/src/Glue.cc.o -c /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/Glue.cc

CMakeFiles/flexBond.dir/src/Glue.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flexBond.dir/src/Glue.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/Glue.cc > CMakeFiles/flexBond.dir/src/Glue.cc.i

CMakeFiles/flexBond.dir/src/Glue.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flexBond.dir/src/Glue.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/Glue.cc -o CMakeFiles/flexBond.dir/src/Glue.cc.s

CMakeFiles/flexBond.dir/src/Kapton.cc.o: CMakeFiles/flexBond.dir/flags.make
CMakeFiles/flexBond.dir/src/Kapton.cc.o: ../src/Kapton.cc
CMakeFiles/flexBond.dir/src/Kapton.cc.o: CMakeFiles/flexBond.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/flexBond.dir/src/Kapton.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flexBond.dir/src/Kapton.cc.o -MF CMakeFiles/flexBond.dir/src/Kapton.cc.o.d -o CMakeFiles/flexBond.dir/src/Kapton.cc.o -c /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/Kapton.cc

CMakeFiles/flexBond.dir/src/Kapton.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flexBond.dir/src/Kapton.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/Kapton.cc > CMakeFiles/flexBond.dir/src/Kapton.cc.i

CMakeFiles/flexBond.dir/src/Kapton.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flexBond.dir/src/Kapton.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/Kapton.cc -o CMakeFiles/flexBond.dir/src/Kapton.cc.s

CMakeFiles/flexBond.dir/src/MapsFoilDetectorList.cc.o: CMakeFiles/flexBond.dir/flags.make
CMakeFiles/flexBond.dir/src/MapsFoilDetectorList.cc.o: ../src/MapsFoilDetectorList.cc
CMakeFiles/flexBond.dir/src/MapsFoilDetectorList.cc.o: CMakeFiles/flexBond.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/flexBond.dir/src/MapsFoilDetectorList.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flexBond.dir/src/MapsFoilDetectorList.cc.o -MF CMakeFiles/flexBond.dir/src/MapsFoilDetectorList.cc.o.d -o CMakeFiles/flexBond.dir/src/MapsFoilDetectorList.cc.o -c /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MapsFoilDetectorList.cc

CMakeFiles/flexBond.dir/src/MapsFoilDetectorList.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flexBond.dir/src/MapsFoilDetectorList.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MapsFoilDetectorList.cc > CMakeFiles/flexBond.dir/src/MapsFoilDetectorList.cc.i

CMakeFiles/flexBond.dir/src/MapsFoilDetectorList.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flexBond.dir/src/MapsFoilDetectorList.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MapsFoilDetectorList.cc -o CMakeFiles/flexBond.dir/src/MapsFoilDetectorList.cc.s

CMakeFiles/flexBond.dir/src/MyActionInitialization.cc.o: CMakeFiles/flexBond.dir/flags.make
CMakeFiles/flexBond.dir/src/MyActionInitialization.cc.o: ../src/MyActionInitialization.cc
CMakeFiles/flexBond.dir/src/MyActionInitialization.cc.o: CMakeFiles/flexBond.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/flexBond.dir/src/MyActionInitialization.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flexBond.dir/src/MyActionInitialization.cc.o -MF CMakeFiles/flexBond.dir/src/MyActionInitialization.cc.o.d -o CMakeFiles/flexBond.dir/src/MyActionInitialization.cc.o -c /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MyActionInitialization.cc

CMakeFiles/flexBond.dir/src/MyActionInitialization.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flexBond.dir/src/MyActionInitialization.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MyActionInitialization.cc > CMakeFiles/flexBond.dir/src/MyActionInitialization.cc.i

CMakeFiles/flexBond.dir/src/MyActionInitialization.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flexBond.dir/src/MyActionInitialization.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MyActionInitialization.cc -o CMakeFiles/flexBond.dir/src/MyActionInitialization.cc.s

CMakeFiles/flexBond.dir/src/MyDetectorConstruction.cc.o: CMakeFiles/flexBond.dir/flags.make
CMakeFiles/flexBond.dir/src/MyDetectorConstruction.cc.o: ../src/MyDetectorConstruction.cc
CMakeFiles/flexBond.dir/src/MyDetectorConstruction.cc.o: CMakeFiles/flexBond.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/flexBond.dir/src/MyDetectorConstruction.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flexBond.dir/src/MyDetectorConstruction.cc.o -MF CMakeFiles/flexBond.dir/src/MyDetectorConstruction.cc.o.d -o CMakeFiles/flexBond.dir/src/MyDetectorConstruction.cc.o -c /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MyDetectorConstruction.cc

CMakeFiles/flexBond.dir/src/MyDetectorConstruction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flexBond.dir/src/MyDetectorConstruction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MyDetectorConstruction.cc > CMakeFiles/flexBond.dir/src/MyDetectorConstruction.cc.i

CMakeFiles/flexBond.dir/src/MyDetectorConstruction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flexBond.dir/src/MyDetectorConstruction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MyDetectorConstruction.cc -o CMakeFiles/flexBond.dir/src/MyDetectorConstruction.cc.s

CMakeFiles/flexBond.dir/src/MyEventAction.cc.o: CMakeFiles/flexBond.dir/flags.make
CMakeFiles/flexBond.dir/src/MyEventAction.cc.o: ../src/MyEventAction.cc
CMakeFiles/flexBond.dir/src/MyEventAction.cc.o: CMakeFiles/flexBond.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/flexBond.dir/src/MyEventAction.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flexBond.dir/src/MyEventAction.cc.o -MF CMakeFiles/flexBond.dir/src/MyEventAction.cc.o.d -o CMakeFiles/flexBond.dir/src/MyEventAction.cc.o -c /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MyEventAction.cc

CMakeFiles/flexBond.dir/src/MyEventAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flexBond.dir/src/MyEventAction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MyEventAction.cc > CMakeFiles/flexBond.dir/src/MyEventAction.cc.i

CMakeFiles/flexBond.dir/src/MyEventAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flexBond.dir/src/MyEventAction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MyEventAction.cc -o CMakeFiles/flexBond.dir/src/MyEventAction.cc.s

CMakeFiles/flexBond.dir/src/MyPrimaryGenerator.cc.o: CMakeFiles/flexBond.dir/flags.make
CMakeFiles/flexBond.dir/src/MyPrimaryGenerator.cc.o: ../src/MyPrimaryGenerator.cc
CMakeFiles/flexBond.dir/src/MyPrimaryGenerator.cc.o: CMakeFiles/flexBond.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/flexBond.dir/src/MyPrimaryGenerator.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flexBond.dir/src/MyPrimaryGenerator.cc.o -MF CMakeFiles/flexBond.dir/src/MyPrimaryGenerator.cc.o.d -o CMakeFiles/flexBond.dir/src/MyPrimaryGenerator.cc.o -c /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MyPrimaryGenerator.cc

CMakeFiles/flexBond.dir/src/MyPrimaryGenerator.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flexBond.dir/src/MyPrimaryGenerator.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MyPrimaryGenerator.cc > CMakeFiles/flexBond.dir/src/MyPrimaryGenerator.cc.i

CMakeFiles/flexBond.dir/src/MyPrimaryGenerator.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flexBond.dir/src/MyPrimaryGenerator.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MyPrimaryGenerator.cc -o CMakeFiles/flexBond.dir/src/MyPrimaryGenerator.cc.s

CMakeFiles/flexBond.dir/src/MyRunAction.cc.o: CMakeFiles/flexBond.dir/flags.make
CMakeFiles/flexBond.dir/src/MyRunAction.cc.o: ../src/MyRunAction.cc
CMakeFiles/flexBond.dir/src/MyRunAction.cc.o: CMakeFiles/flexBond.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/flexBond.dir/src/MyRunAction.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flexBond.dir/src/MyRunAction.cc.o -MF CMakeFiles/flexBond.dir/src/MyRunAction.cc.o.d -o CMakeFiles/flexBond.dir/src/MyRunAction.cc.o -c /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MyRunAction.cc

CMakeFiles/flexBond.dir/src/MyRunAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flexBond.dir/src/MyRunAction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MyRunAction.cc > CMakeFiles/flexBond.dir/src/MyRunAction.cc.i

CMakeFiles/flexBond.dir/src/MyRunAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flexBond.dir/src/MyRunAction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MyRunAction.cc -o CMakeFiles/flexBond.dir/src/MyRunAction.cc.s

CMakeFiles/flexBond.dir/src/MySensitiveDetector.cc.o: CMakeFiles/flexBond.dir/flags.make
CMakeFiles/flexBond.dir/src/MySensitiveDetector.cc.o: ../src/MySensitiveDetector.cc
CMakeFiles/flexBond.dir/src/MySensitiveDetector.cc.o: CMakeFiles/flexBond.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/flexBond.dir/src/MySensitiveDetector.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flexBond.dir/src/MySensitiveDetector.cc.o -MF CMakeFiles/flexBond.dir/src/MySensitiveDetector.cc.o.d -o CMakeFiles/flexBond.dir/src/MySensitiveDetector.cc.o -c /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MySensitiveDetector.cc

CMakeFiles/flexBond.dir/src/MySensitiveDetector.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flexBond.dir/src/MySensitiveDetector.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MySensitiveDetector.cc > CMakeFiles/flexBond.dir/src/MySensitiveDetector.cc.i

CMakeFiles/flexBond.dir/src/MySensitiveDetector.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flexBond.dir/src/MySensitiveDetector.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MySensitiveDetector.cc -o CMakeFiles/flexBond.dir/src/MySensitiveDetector.cc.s

CMakeFiles/flexBond.dir/src/MySensitiveDetectorHit.cc.o: CMakeFiles/flexBond.dir/flags.make
CMakeFiles/flexBond.dir/src/MySensitiveDetectorHit.cc.o: ../src/MySensitiveDetectorHit.cc
CMakeFiles/flexBond.dir/src/MySensitiveDetectorHit.cc.o: CMakeFiles/flexBond.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/flexBond.dir/src/MySensitiveDetectorHit.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flexBond.dir/src/MySensitiveDetectorHit.cc.o -MF CMakeFiles/flexBond.dir/src/MySensitiveDetectorHit.cc.o.d -o CMakeFiles/flexBond.dir/src/MySensitiveDetectorHit.cc.o -c /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MySensitiveDetectorHit.cc

CMakeFiles/flexBond.dir/src/MySensitiveDetectorHit.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flexBond.dir/src/MySensitiveDetectorHit.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MySensitiveDetectorHit.cc > CMakeFiles/flexBond.dir/src/MySensitiveDetectorHit.cc.i

CMakeFiles/flexBond.dir/src/MySensitiveDetectorHit.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flexBond.dir/src/MySensitiveDetectorHit.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MySensitiveDetectorHit.cc -o CMakeFiles/flexBond.dir/src/MySensitiveDetectorHit.cc.s

CMakeFiles/flexBond.dir/src/MySteppingAction.cc.o: CMakeFiles/flexBond.dir/flags.make
CMakeFiles/flexBond.dir/src/MySteppingAction.cc.o: ../src/MySteppingAction.cc
CMakeFiles/flexBond.dir/src/MySteppingAction.cc.o: CMakeFiles/flexBond.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/flexBond.dir/src/MySteppingAction.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flexBond.dir/src/MySteppingAction.cc.o -MF CMakeFiles/flexBond.dir/src/MySteppingAction.cc.o.d -o CMakeFiles/flexBond.dir/src/MySteppingAction.cc.o -c /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MySteppingAction.cc

CMakeFiles/flexBond.dir/src/MySteppingAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flexBond.dir/src/MySteppingAction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MySteppingAction.cc > CMakeFiles/flexBond.dir/src/MySteppingAction.cc.i

CMakeFiles/flexBond.dir/src/MySteppingAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flexBond.dir/src/MySteppingAction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/MySteppingAction.cc -o CMakeFiles/flexBond.dir/src/MySteppingAction.cc.s

CMakeFiles/flexBond.dir/src/SolderBall.cc.o: CMakeFiles/flexBond.dir/flags.make
CMakeFiles/flexBond.dir/src/SolderBall.cc.o: ../src/SolderBall.cc
CMakeFiles/flexBond.dir/src/SolderBall.cc.o: CMakeFiles/flexBond.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/flexBond.dir/src/SolderBall.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flexBond.dir/src/SolderBall.cc.o -MF CMakeFiles/flexBond.dir/src/SolderBall.cc.o.d -o CMakeFiles/flexBond.dir/src/SolderBall.cc.o -c /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/SolderBall.cc

CMakeFiles/flexBond.dir/src/SolderBall.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flexBond.dir/src/SolderBall.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/SolderBall.cc > CMakeFiles/flexBond.dir/src/SolderBall.cc.i

CMakeFiles/flexBond.dir/src/SolderBall.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flexBond.dir/src/SolderBall.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/src/SolderBall.cc -o CMakeFiles/flexBond.dir/src/SolderBall.cc.s

# Object files for target flexBond
flexBond_OBJECTS = \
"CMakeFiles/flexBond.dir/sim.cc.o" \
"CMakeFiles/flexBond.dir/src/Alpide.cc.o" \
"CMakeFiles/flexBond.dir/src/Copper.cc.o" \
"CMakeFiles/flexBond.dir/src/Glue.cc.o" \
"CMakeFiles/flexBond.dir/src/Kapton.cc.o" \
"CMakeFiles/flexBond.dir/src/MapsFoilDetectorList.cc.o" \
"CMakeFiles/flexBond.dir/src/MyActionInitialization.cc.o" \
"CMakeFiles/flexBond.dir/src/MyDetectorConstruction.cc.o" \
"CMakeFiles/flexBond.dir/src/MyEventAction.cc.o" \
"CMakeFiles/flexBond.dir/src/MyPrimaryGenerator.cc.o" \
"CMakeFiles/flexBond.dir/src/MyRunAction.cc.o" \
"CMakeFiles/flexBond.dir/src/MySensitiveDetector.cc.o" \
"CMakeFiles/flexBond.dir/src/MySensitiveDetectorHit.cc.o" \
"CMakeFiles/flexBond.dir/src/MySteppingAction.cc.o" \
"CMakeFiles/flexBond.dir/src/SolderBall.cc.o"

# External object files for target flexBond
flexBond_EXTERNAL_OBJECTS =

flexBond: CMakeFiles/flexBond.dir/sim.cc.o
flexBond: CMakeFiles/flexBond.dir/src/Alpide.cc.o
flexBond: CMakeFiles/flexBond.dir/src/Copper.cc.o
flexBond: CMakeFiles/flexBond.dir/src/Glue.cc.o
flexBond: CMakeFiles/flexBond.dir/src/Kapton.cc.o
flexBond: CMakeFiles/flexBond.dir/src/MapsFoilDetectorList.cc.o
flexBond: CMakeFiles/flexBond.dir/src/MyActionInitialization.cc.o
flexBond: CMakeFiles/flexBond.dir/src/MyDetectorConstruction.cc.o
flexBond: CMakeFiles/flexBond.dir/src/MyEventAction.cc.o
flexBond: CMakeFiles/flexBond.dir/src/MyPrimaryGenerator.cc.o
flexBond: CMakeFiles/flexBond.dir/src/MyRunAction.cc.o
flexBond: CMakeFiles/flexBond.dir/src/MySensitiveDetector.cc.o
flexBond: CMakeFiles/flexBond.dir/src/MySensitiveDetectorHit.cc.o
flexBond: CMakeFiles/flexBond.dir/src/MySteppingAction.cc.o
flexBond: CMakeFiles/flexBond.dir/src/SolderBall.cc.o
flexBond: CMakeFiles/flexBond.dir/build.make
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4Tree.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4FR.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4GMocren.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4visHepRep.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4RayTracer.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4VRML.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4ToolsSG.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4OpenGL.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4vis_management.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4modeling.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4interfaces.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4mctruth.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4geomtext.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4gdml.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4error_propagation.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4readout.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4physicslists.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4run.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4event.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4tracking.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4parmodels.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4processes.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4digits_hits.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4track.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4particles.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4geometry.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4materials.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4graphics_reps.so
flexBond: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
flexBond: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
flexBond: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
flexBond: /usr/lib/x86_64-linux-gnu/libxerces-c.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4analysis.so
flexBond: /usr/lib/x86_64-linux-gnu/libexpat.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4zlib.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4intercoms.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4global.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4clhep.so
flexBond: /home/luca/geant4-v11.3.0-install/lib/libG4ptl.so.3.0.0
flexBond: CMakeFiles/flexBond.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX executable flexBond"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/flexBond.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/flexBond.dir/build: flexBond
.PHONY : CMakeFiles/flexBond.dir/build

CMakeFiles/flexBond.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/flexBond.dir/cmake_clean.cmake
.PHONY : CMakeFiles/flexBond.dir/clean

CMakeFiles/flexBond.dir/depend:
	cd /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build /home/luca/geant4_workdir/FlexBond/Geant4_FlexBond-main/build/CMakeFiles/flexBond.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/flexBond.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/af6618/C_TANK

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/af6618/C_TANK

# Include any dependencies generated for this target.
include CMakeFiles/TANK.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TANK.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TANK.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TANK.dir/flags.make

CMakeFiles/TANK.dir/buffers/VirtualRDMARingBuffer.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/buffers/VirtualRDMARingBuffer.c.o: buffers/VirtualRDMARingBuffer.c
CMakeFiles/TANK.dir/buffers/VirtualRDMARingBuffer.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TANK.dir/buffers/VirtualRDMARingBuffer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/buffers/VirtualRDMARingBuffer.c.o -MF CMakeFiles/TANK.dir/buffers/VirtualRDMARingBuffer.c.o.d -o CMakeFiles/TANK.dir/buffers/VirtualRDMARingBuffer.c.o -c /home/af6618/C_TANK/buffers/VirtualRDMARingBuffer.c

CMakeFiles/TANK.dir/buffers/VirtualRDMARingBuffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/buffers/VirtualRDMARingBuffer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/buffers/VirtualRDMARingBuffer.c > CMakeFiles/TANK.dir/buffers/VirtualRDMARingBuffer.c.i

CMakeFiles/TANK.dir/buffers/VirtualRDMARingBuffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/buffers/VirtualRDMARingBuffer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/buffers/VirtualRDMARingBuffer.c -o CMakeFiles/TANK.dir/buffers/VirtualRDMARingBuffer.c.s

CMakeFiles/TANK.dir/buffers/VirtualSHMDoubleRingBuffer.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/buffers/VirtualSHMDoubleRingBuffer.c.o: buffers/VirtualSHMDoubleRingBuffer.c
CMakeFiles/TANK.dir/buffers/VirtualSHMDoubleRingBuffer.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/TANK.dir/buffers/VirtualSHMDoubleRingBuffer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/buffers/VirtualSHMDoubleRingBuffer.c.o -MF CMakeFiles/TANK.dir/buffers/VirtualSHMDoubleRingBuffer.c.o.d -o CMakeFiles/TANK.dir/buffers/VirtualSHMDoubleRingBuffer.c.o -c /home/af6618/C_TANK/buffers/VirtualSHMDoubleRingBuffer.c

CMakeFiles/TANK.dir/buffers/VirtualSHMDoubleRingBuffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/buffers/VirtualSHMDoubleRingBuffer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/buffers/VirtualSHMDoubleRingBuffer.c > CMakeFiles/TANK.dir/buffers/VirtualSHMDoubleRingBuffer.c.i

CMakeFiles/TANK.dir/buffers/VirtualSHMDoubleRingBuffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/buffers/VirtualSHMDoubleRingBuffer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/buffers/VirtualSHMDoubleRingBuffer.c -o CMakeFiles/TANK.dir/buffers/VirtualSHMDoubleRingBuffer.c.s

CMakeFiles/TANK.dir/buffers/VirtualSHMRingBuffer.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/buffers/VirtualSHMRingBuffer.c.o: buffers/VirtualSHMRingBuffer.c
CMakeFiles/TANK.dir/buffers/VirtualSHMRingBuffer.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/TANK.dir/buffers/VirtualSHMRingBuffer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/buffers/VirtualSHMRingBuffer.c.o -MF CMakeFiles/TANK.dir/buffers/VirtualSHMRingBuffer.c.o.d -o CMakeFiles/TANK.dir/buffers/VirtualSHMRingBuffer.c.o -c /home/af6618/C_TANK/buffers/VirtualSHMRingBuffer.c

CMakeFiles/TANK.dir/buffers/VirtualSHMRingBuffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/buffers/VirtualSHMRingBuffer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/buffers/VirtualSHMRingBuffer.c > CMakeFiles/TANK.dir/buffers/VirtualSHMRingBuffer.c.i

CMakeFiles/TANK.dir/buffers/VirtualSHMRingBuffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/buffers/VirtualSHMRingBuffer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/buffers/VirtualSHMRingBuffer.c -o CMakeFiles/TANK.dir/buffers/VirtualSHMRingBuffer.c.s

CMakeFiles/TANK.dir/client/RdmaClient.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/client/RdmaClient.c.o: client/RdmaClient.c
CMakeFiles/TANK.dir/client/RdmaClient.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/TANK.dir/client/RdmaClient.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/client/RdmaClient.c.o -MF CMakeFiles/TANK.dir/client/RdmaClient.c.o.d -o CMakeFiles/TANK.dir/client/RdmaClient.c.o -c /home/af6618/C_TANK/client/RdmaClient.c

CMakeFiles/TANK.dir/client/RdmaClient.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/client/RdmaClient.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/client/RdmaClient.c > CMakeFiles/TANK.dir/client/RdmaClient.c.i

CMakeFiles/TANK.dir/client/RdmaClient.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/client/RdmaClient.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/client/RdmaClient.c -o CMakeFiles/TANK.dir/client/RdmaClient.c.s

CMakeFiles/TANK.dir/client/SharedMemoryClient.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/client/SharedMemoryClient.c.o: client/SharedMemoryClient.c
CMakeFiles/TANK.dir/client/SharedMemoryClient.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/TANK.dir/client/SharedMemoryClient.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/client/SharedMemoryClient.c.o -MF CMakeFiles/TANK.dir/client/SharedMemoryClient.c.o.d -o CMakeFiles/TANK.dir/client/SharedMemoryClient.c.o -c /home/af6618/C_TANK/client/SharedMemoryClient.c

CMakeFiles/TANK.dir/client/SharedMemoryClient.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/client/SharedMemoryClient.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/client/SharedMemoryClient.c > CMakeFiles/TANK.dir/client/SharedMemoryClient.c.i

CMakeFiles/TANK.dir/client/SharedMemoryClient.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/client/SharedMemoryClient.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/client/SharedMemoryClient.c -o CMakeFiles/TANK.dir/client/SharedMemoryClient.c.s

CMakeFiles/TANK.dir/client/TcpClient.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/client/TcpClient.c.o: client/TcpClient.c
CMakeFiles/TANK.dir/client/TcpClient.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/TANK.dir/client/TcpClient.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/client/TcpClient.c.o -MF CMakeFiles/TANK.dir/client/TcpClient.c.o.d -o CMakeFiles/TANK.dir/client/TcpClient.c.o -c /home/af6618/C_TANK/client/TcpClient.c

CMakeFiles/TANK.dir/client/TcpClient.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/client/TcpClient.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/client/TcpClient.c > CMakeFiles/TANK.dir/client/TcpClient.c.i

CMakeFiles/TANK.dir/client/TcpClient.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/client/TcpClient.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/client/TcpClient.c -o CMakeFiles/TANK.dir/client/TcpClient.c.s

CMakeFiles/TANK.dir/connections/P2PConnection.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/connections/P2PConnection.c.o: connections/P2PConnection.c
CMakeFiles/TANK.dir/connections/P2PConnection.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/TANK.dir/connections/P2PConnection.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/connections/P2PConnection.c.o -MF CMakeFiles/TANK.dir/connections/P2PConnection.c.o.d -o CMakeFiles/TANK.dir/connections/P2PConnection.c.o -c /home/af6618/C_TANK/connections/P2PConnection.c

CMakeFiles/TANK.dir/connections/P2PConnection.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/connections/P2PConnection.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/connections/P2PConnection.c > CMakeFiles/TANK.dir/connections/P2PConnection.c.i

CMakeFiles/TANK.dir/connections/P2PConnection.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/connections/P2PConnection.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/connections/P2PConnection.c -o CMakeFiles/TANK.dir/connections/P2PConnection.c.s

CMakeFiles/TANK.dir/rdma/CompletionQueuePair.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/rdma/CompletionQueuePair.c.o: rdma/CompletionQueuePair.c
CMakeFiles/TANK.dir/rdma/CompletionQueuePair.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/TANK.dir/rdma/CompletionQueuePair.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/rdma/CompletionQueuePair.c.o -MF CMakeFiles/TANK.dir/rdma/CompletionQueuePair.c.o.d -o CMakeFiles/TANK.dir/rdma/CompletionQueuePair.c.o -c /home/af6618/C_TANK/rdma/CompletionQueuePair.c

CMakeFiles/TANK.dir/rdma/CompletionQueuePair.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/rdma/CompletionQueuePair.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/rdma/CompletionQueuePair.c > CMakeFiles/TANK.dir/rdma/CompletionQueuePair.c.i

CMakeFiles/TANK.dir/rdma/CompletionQueuePair.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/rdma/CompletionQueuePair.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/rdma/CompletionQueuePair.c -o CMakeFiles/TANK.dir/rdma/CompletionQueuePair.c.s

CMakeFiles/TANK.dir/rdma/Network.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/rdma/Network.c.o: rdma/Network.c
CMakeFiles/TANK.dir/rdma/Network.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/TANK.dir/rdma/Network.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/rdma/Network.c.o -MF CMakeFiles/TANK.dir/rdma/Network.c.o.d -o CMakeFiles/TANK.dir/rdma/Network.c.o -c /home/af6618/C_TANK/rdma/Network.c

CMakeFiles/TANK.dir/rdma/Network.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/rdma/Network.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/rdma/Network.c > CMakeFiles/TANK.dir/rdma/Network.c.i

CMakeFiles/TANK.dir/rdma/Network.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/rdma/Network.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/rdma/Network.c -o CMakeFiles/TANK.dir/rdma/Network.c.s

CMakeFiles/TANK.dir/rdma/QueuePair.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/rdma/QueuePair.c.o: rdma/QueuePair.c
CMakeFiles/TANK.dir/rdma/QueuePair.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/TANK.dir/rdma/QueuePair.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/rdma/QueuePair.c.o -MF CMakeFiles/TANK.dir/rdma/QueuePair.c.o.d -o CMakeFiles/TANK.dir/rdma/QueuePair.c.o -c /home/af6618/C_TANK/rdma/QueuePair.c

CMakeFiles/TANK.dir/rdma/QueuePair.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/rdma/QueuePair.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/rdma/QueuePair.c > CMakeFiles/TANK.dir/rdma/QueuePair.c.i

CMakeFiles/TANK.dir/rdma/QueuePair.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/rdma/QueuePair.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/rdma/QueuePair.c -o CMakeFiles/TANK.dir/rdma/QueuePair.c.s

CMakeFiles/TANK.dir/rdma/RcQueuePair.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/rdma/RcQueuePair.c.o: rdma/RcQueuePair.c
CMakeFiles/TANK.dir/rdma/RcQueuePair.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/TANK.dir/rdma/RcQueuePair.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/rdma/RcQueuePair.c.o -MF CMakeFiles/TANK.dir/rdma/RcQueuePair.c.o.d -o CMakeFiles/TANK.dir/rdma/RcQueuePair.c.o -c /home/af6618/C_TANK/rdma/RcQueuePair.c

CMakeFiles/TANK.dir/rdma/RcQueuePair.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/rdma/RcQueuePair.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/rdma/RcQueuePair.c > CMakeFiles/TANK.dir/rdma/RcQueuePair.c.i

CMakeFiles/TANK.dir/rdma/RcQueuePair.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/rdma/RcQueuePair.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/rdma/RcQueuePair.c -o CMakeFiles/TANK.dir/rdma/RcQueuePair.c.s

CMakeFiles/TANK.dir/rdma/RDMANetworking.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/rdma/RDMANetworking.c.o: rdma/RDMANetworking.c
CMakeFiles/TANK.dir/rdma/RDMANetworking.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/TANK.dir/rdma/RDMANetworking.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/rdma/RDMANetworking.c.o -MF CMakeFiles/TANK.dir/rdma/RDMANetworking.c.o.d -o CMakeFiles/TANK.dir/rdma/RDMANetworking.c.o -c /home/af6618/C_TANK/rdma/RDMANetworking.c

CMakeFiles/TANK.dir/rdma/RDMANetworking.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/rdma/RDMANetworking.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/rdma/RDMANetworking.c > CMakeFiles/TANK.dir/rdma/RDMANetworking.c.i

CMakeFiles/TANK.dir/rdma/RDMANetworking.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/rdma/RDMANetworking.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/rdma/RDMANetworking.c -o CMakeFiles/TANK.dir/rdma/RDMANetworking.c.s

CMakeFiles/TANK.dir/rdma/UcQueuePair.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/rdma/UcQueuePair.c.o: rdma/UcQueuePair.c
CMakeFiles/TANK.dir/rdma/UcQueuePair.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/TANK.dir/rdma/UcQueuePair.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/rdma/UcQueuePair.c.o -MF CMakeFiles/TANK.dir/rdma/UcQueuePair.c.o.d -o CMakeFiles/TANK.dir/rdma/UcQueuePair.c.o -c /home/af6618/C_TANK/rdma/UcQueuePair.c

CMakeFiles/TANK.dir/rdma/UcQueuePair.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/rdma/UcQueuePair.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/rdma/UcQueuePair.c > CMakeFiles/TANK.dir/rdma/UcQueuePair.c.i

CMakeFiles/TANK.dir/rdma/UcQueuePair.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/rdma/UcQueuePair.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/rdma/UcQueuePair.c -o CMakeFiles/TANK.dir/rdma/UcQueuePair.c.s

CMakeFiles/TANK.dir/rdma/UdQueuePair.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/rdma/UdQueuePair.c.o: rdma/UdQueuePair.c
CMakeFiles/TANK.dir/rdma/UdQueuePair.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/TANK.dir/rdma/UdQueuePair.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/rdma/UdQueuePair.c.o -MF CMakeFiles/TANK.dir/rdma/UdQueuePair.c.o.d -o CMakeFiles/TANK.dir/rdma/UdQueuePair.c.o -c /home/af6618/C_TANK/rdma/UdQueuePair.c

CMakeFiles/TANK.dir/rdma/UdQueuePair.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/rdma/UdQueuePair.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/rdma/UdQueuePair.c > CMakeFiles/TANK.dir/rdma/UdQueuePair.c.i

CMakeFiles/TANK.dir/rdma/UdQueuePair.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/rdma/UdQueuePair.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/rdma/UdQueuePair.c -o CMakeFiles/TANK.dir/rdma/UdQueuePair.c.s

CMakeFiles/TANK.dir/server/RdmaServer.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/server/RdmaServer.c.o: server/RdmaServer.c
CMakeFiles/TANK.dir/server/RdmaServer.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object CMakeFiles/TANK.dir/server/RdmaServer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/server/RdmaServer.c.o -MF CMakeFiles/TANK.dir/server/RdmaServer.c.o.d -o CMakeFiles/TANK.dir/server/RdmaServer.c.o -c /home/af6618/C_TANK/server/RdmaServer.c

CMakeFiles/TANK.dir/server/RdmaServer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/server/RdmaServer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/server/RdmaServer.c > CMakeFiles/TANK.dir/server/RdmaServer.c.i

CMakeFiles/TANK.dir/server/RdmaServer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/server/RdmaServer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/server/RdmaServer.c -o CMakeFiles/TANK.dir/server/RdmaServer.c.s

CMakeFiles/TANK.dir/server/SharedMemoryServer.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/server/SharedMemoryServer.c.o: server/SharedMemoryServer.c
CMakeFiles/TANK.dir/server/SharedMemoryServer.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building C object CMakeFiles/TANK.dir/server/SharedMemoryServer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/server/SharedMemoryServer.c.o -MF CMakeFiles/TANK.dir/server/SharedMemoryServer.c.o.d -o CMakeFiles/TANK.dir/server/SharedMemoryServer.c.o -c /home/af6618/C_TANK/server/SharedMemoryServer.c

CMakeFiles/TANK.dir/server/SharedMemoryServer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/server/SharedMemoryServer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/server/SharedMemoryServer.c > CMakeFiles/TANK.dir/server/SharedMemoryServer.c.i

CMakeFiles/TANK.dir/server/SharedMemoryServer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/server/SharedMemoryServer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/server/SharedMemoryServer.c -o CMakeFiles/TANK.dir/server/SharedMemoryServer.c.s

CMakeFiles/TANK.dir/server/TcpServer.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/server/TcpServer.c.o: server/TcpServer.c
CMakeFiles/TANK.dir/server/TcpServer.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building C object CMakeFiles/TANK.dir/server/TcpServer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/server/TcpServer.c.o -MF CMakeFiles/TANK.dir/server/TcpServer.c.o.d -o CMakeFiles/TANK.dir/server/TcpServer.c.o -c /home/af6618/C_TANK/server/TcpServer.c

CMakeFiles/TANK.dir/server/TcpServer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/server/TcpServer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/server/TcpServer.c > CMakeFiles/TANK.dir/server/TcpServer.c.i

CMakeFiles/TANK.dir/server/TcpServer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/server/TcpServer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/server/TcpServer.c -o CMakeFiles/TANK.dir/server/TcpServer.c.s

CMakeFiles/TANK.dir/test/bench.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/test/bench.c.o: test/bench.c
CMakeFiles/TANK.dir/test/bench.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building C object CMakeFiles/TANK.dir/test/bench.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/test/bench.c.o -MF CMakeFiles/TANK.dir/test/bench.c.o.d -o CMakeFiles/TANK.dir/test/bench.c.o -c /home/af6618/C_TANK/test/bench.c

CMakeFiles/TANK.dir/test/bench.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/test/bench.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/test/bench.c > CMakeFiles/TANK.dir/test/bench.c.i

CMakeFiles/TANK.dir/test/bench.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/test/bench.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/test/bench.c -o CMakeFiles/TANK.dir/test/bench.c.s

CMakeFiles/TANK.dir/utils/utils.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/utils/utils.c.o: utils/utils.c
CMakeFiles/TANK.dir/utils/utils.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Building C object CMakeFiles/TANK.dir/utils/utils.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/utils/utils.c.o -MF CMakeFiles/TANK.dir/utils/utils.c.o.d -o CMakeFiles/TANK.dir/utils/utils.c.o -c /home/af6618/C_TANK/utils/utils.c

CMakeFiles/TANK.dir/utils/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/utils/utils.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/utils/utils.c > CMakeFiles/TANK.dir/utils/utils.c.i

CMakeFiles/TANK.dir/utils/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/utils/utils.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/utils/utils.c -o CMakeFiles/TANK.dir/utils/utils.c.s

CMakeFiles/TANK.dir/utils/vec.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/utils/vec.c.o: utils/vec.c
CMakeFiles/TANK.dir/utils/vec.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_20) "Building C object CMakeFiles/TANK.dir/utils/vec.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/utils/vec.c.o -MF CMakeFiles/TANK.dir/utils/vec.c.o.d -o CMakeFiles/TANK.dir/utils/vec.c.o -c /home/af6618/C_TANK/utils/vec.c

CMakeFiles/TANK.dir/utils/vec.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/utils/vec.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/utils/vec.c > CMakeFiles/TANK.dir/utils/vec.c.i

CMakeFiles/TANK.dir/utils/vec.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/utils/vec.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/utils/vec.c -o CMakeFiles/TANK.dir/utils/vec.c.s

CMakeFiles/TANK.dir/utils/virtualMemory.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/utils/virtualMemory.c.o: utils/virtualMemory.c
CMakeFiles/TANK.dir/utils/virtualMemory.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_21) "Building C object CMakeFiles/TANK.dir/utils/virtualMemory.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/utils/virtualMemory.c.o -MF CMakeFiles/TANK.dir/utils/virtualMemory.c.o.d -o CMakeFiles/TANK.dir/utils/virtualMemory.c.o -c /home/af6618/C_TANK/utils/virtualMemory.c

CMakeFiles/TANK.dir/utils/virtualMemory.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/utils/virtualMemory.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/utils/virtualMemory.c > CMakeFiles/TANK.dir/utils/virtualMemory.c.i

CMakeFiles/TANK.dir/utils/virtualMemory.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/utils/virtualMemory.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/utils/virtualMemory.c -o CMakeFiles/TANK.dir/utils/virtualMemory.c.s

CMakeFiles/TANK.dir/main.c.o: CMakeFiles/TANK.dir/flags.make
CMakeFiles/TANK.dir/main.c.o: main.c
CMakeFiles/TANK.dir/main.c.o: CMakeFiles/TANK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_22) "Building C object CMakeFiles/TANK.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TANK.dir/main.c.o -MF CMakeFiles/TANK.dir/main.c.o.d -o CMakeFiles/TANK.dir/main.c.o -c /home/af6618/C_TANK/main.c

CMakeFiles/TANK.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TANK.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/af6618/C_TANK/main.c > CMakeFiles/TANK.dir/main.c.i

CMakeFiles/TANK.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TANK.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/af6618/C_TANK/main.c -o CMakeFiles/TANK.dir/main.c.s

# Object files for target TANK
TANK_OBJECTS = \
"CMakeFiles/TANK.dir/buffers/VirtualRDMARingBuffer.c.o" \
"CMakeFiles/TANK.dir/buffers/VirtualSHMDoubleRingBuffer.c.o" \
"CMakeFiles/TANK.dir/buffers/VirtualSHMRingBuffer.c.o" \
"CMakeFiles/TANK.dir/client/RdmaClient.c.o" \
"CMakeFiles/TANK.dir/client/SharedMemoryClient.c.o" \
"CMakeFiles/TANK.dir/client/TcpClient.c.o" \
"CMakeFiles/TANK.dir/connections/P2PConnection.c.o" \
"CMakeFiles/TANK.dir/rdma/CompletionQueuePair.c.o" \
"CMakeFiles/TANK.dir/rdma/Network.c.o" \
"CMakeFiles/TANK.dir/rdma/QueuePair.c.o" \
"CMakeFiles/TANK.dir/rdma/RcQueuePair.c.o" \
"CMakeFiles/TANK.dir/rdma/RDMANetworking.c.o" \
"CMakeFiles/TANK.dir/rdma/UcQueuePair.c.o" \
"CMakeFiles/TANK.dir/rdma/UdQueuePair.c.o" \
"CMakeFiles/TANK.dir/server/RdmaServer.c.o" \
"CMakeFiles/TANK.dir/server/SharedMemoryServer.c.o" \
"CMakeFiles/TANK.dir/server/TcpServer.c.o" \
"CMakeFiles/TANK.dir/test/bench.c.o" \
"CMakeFiles/TANK.dir/utils/utils.c.o" \
"CMakeFiles/TANK.dir/utils/vec.c.o" \
"CMakeFiles/TANK.dir/utils/virtualMemory.c.o" \
"CMakeFiles/TANK.dir/main.c.o"

# External object files for target TANK
TANK_EXTERNAL_OBJECTS =

TANK: CMakeFiles/TANK.dir/buffers/VirtualRDMARingBuffer.c.o
TANK: CMakeFiles/TANK.dir/buffers/VirtualSHMDoubleRingBuffer.c.o
TANK: CMakeFiles/TANK.dir/buffers/VirtualSHMRingBuffer.c.o
TANK: CMakeFiles/TANK.dir/client/RdmaClient.c.o
TANK: CMakeFiles/TANK.dir/client/SharedMemoryClient.c.o
TANK: CMakeFiles/TANK.dir/client/TcpClient.c.o
TANK: CMakeFiles/TANK.dir/connections/P2PConnection.c.o
TANK: CMakeFiles/TANK.dir/rdma/CompletionQueuePair.c.o
TANK: CMakeFiles/TANK.dir/rdma/Network.c.o
TANK: CMakeFiles/TANK.dir/rdma/QueuePair.c.o
TANK: CMakeFiles/TANK.dir/rdma/RcQueuePair.c.o
TANK: CMakeFiles/TANK.dir/rdma/RDMANetworking.c.o
TANK: CMakeFiles/TANK.dir/rdma/UcQueuePair.c.o
TANK: CMakeFiles/TANK.dir/rdma/UdQueuePair.c.o
TANK: CMakeFiles/TANK.dir/server/RdmaServer.c.o
TANK: CMakeFiles/TANK.dir/server/SharedMemoryServer.c.o
TANK: CMakeFiles/TANK.dir/server/TcpServer.c.o
TANK: CMakeFiles/TANK.dir/test/bench.c.o
TANK: CMakeFiles/TANK.dir/utils/utils.c.o
TANK: CMakeFiles/TANK.dir/utils/vec.c.o
TANK: CMakeFiles/TANK.dir/utils/virtualMemory.c.o
TANK: CMakeFiles/TANK.dir/main.c.o
TANK: CMakeFiles/TANK.dir/build.make
TANK: CMakeFiles/TANK.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/af6618/C_TANK/CMakeFiles --progress-num=$(CMAKE_PROGRESS_23) "Linking C executable TANK"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TANK.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TANK.dir/build: TANK
.PHONY : CMakeFiles/TANK.dir/build

CMakeFiles/TANK.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TANK.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TANK.dir/clean

CMakeFiles/TANK.dir/depend:
	cd /home/af6618/C_TANK && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/af6618/C_TANK /home/af6618/C_TANK /home/af6618/C_TANK /home/af6618/C_TANK /home/af6618/C_TANK/CMakeFiles/TANK.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TANK.dir/depend

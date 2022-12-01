cmake_minimum_required(VERSION 3.21)
project(TANK C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -D_GNU_SOURCE -march=native -mtune=native -luuid -lm -lrt -libverbs -fPIC")

include_directories(buffers)
include_directories(client)
include_directories(connections)
include_directories(rdma)
include_directories(server)
include_directories(test)
include_directories(utils)

set(executables
            P2PTest)

add_executable(TANK
        buffers/VirtualRDMARingBuffer.c
        buffers/VirtualRDMARingBuffer.h
        buffers/VirtualSHMDoubleRingBuffer.c
        buffers/VirtualSHMDoubleRingBuffer.h
        buffers/VirtualSHMRingBuffer.c
        buffers/VirtualSHMRingBuffer.h
        client/RdmaClient.c
        client/RdmaClient.h
        client/SharedMemoryClient.c
        client/SharedMemoryClient.h
        client/TcpClient.c
        client/TcpClient.h
        connections/P2PConnection.c
        connections/P2PConnection.h
        rdma/CompletionQueuePair.c
        rdma/CompletionQueuePair.h
        rdma/Network.c
        rdma/Network.h
        rdma/QueuePair.c
        rdma/QueuePair.h
        rdma/RcQueuePair.c
        rdma/RcQueuePair.h
        rdma/RDMANetworking.c
        rdma/RDMANetworking.h
        rdma/UcQueuePair.c
        rdma/UcQueuePair.h
        rdma/UdQueuePair.c
        rdma/UdQueuePair.h
        server/RdmaServer.c
        server/RdmaServer.h
        server/SharedMemoryServer.c
        server/SharedMemoryServer.h
        server/TcpServer.c
        server/TcpServer.h
        test/bench.c
        test/bench.h
        utils/utils.c
        utils/utils.h
        utils/vec.c
        utils/vec.h
        utils/virtualMemory.c
        utils/virtualMemory.h
        main.c)

target_link_libraries(TANK PRIVATE uuid ibverbs rt m)

foreach (exe ${executables})
    add_executable(${exe}
        buffers/VirtualRDMARingBuffer.c
        buffers/VirtualRDMARingBuffer.h
        buffers/VirtualSHMDoubleRingBuffer.c
        buffers/VirtualSHMDoubleRingBuffer.h
        buffers/VirtualSHMRingBuffer.c
        buffers/VirtualSHMRingBuffer.h
        client/RdmaClient.c
        client/RdmaClient.h
        client/SharedMemoryClient.c
        client/SharedMemoryClient.h
        client/TcpClient.c
        client/TcpClient.h
        connections/P2PConnection.c
        connections/P2PConnection.h
        rdma/CompletionQueuePair.c
        rdma/CompletionQueuePair.h
        rdma/Network.c
        rdma/Network.h
        rdma/QueuePair.c
        rdma/QueuePair.h
        rdma/RcQueuePair.c
        rdma/RcQueuePair.h
        rdma/RDMANetworking.c
        rdma/RDMANetworking.h
        rdma/UcQueuePair.c
        rdma/UcQueuePair.h
        rdma/UdQueuePair.c
        rdma/UdQueuePair.h
        server/RdmaServer.c
        server/RdmaServer.h
        server/SharedMemoryServer.c
        server/SharedMemoryServer.h
        server/TcpServer.c
        server/TcpServer.h
        test/bench.c
        test/bench.h
        utils/utils.c
        utils/utils.h
        utils/vec.c
        utils/vec.h
        utils/virtualMemory.c
        utils/virtualMemory.h
        test/${exe}.c)
    target_link_libraries(${exe} PRIVATE uuid ibverbs rt m)
endforeach ()



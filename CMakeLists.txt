cmake_minimum_required(VERSION 4.2)
project(Os_Concurrency)

set(CMAKE_CXX_STANDARD 14)

add_executable(Os_Concurrency
        .idea/.gitignore
        .idea/editor.xml
        .idea/modules.xml
        .idea/Os&Concurrency.iml
        Process&Threads/Threads.cpp
        Process&Threads/join_detach.cpp
        Race_Condition/Race.cpp
        Race_Condition/Lock_Guard.cpp
        DeadLock/printer_scanner_ex.cpp
        DeadLock/solution_lock.cpp
        Produce_Consumer_CV/Producer_Consumer.cpp)

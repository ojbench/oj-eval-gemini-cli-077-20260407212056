cmake_minimum_required(VERSION 3.10)
project(CrossArray)

set(CMAKE_CXX_STANDARD 14)

# If main.cpp exists, compile it into code
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    add_executable(code main.cpp)
else()
    # Just a dummy to satisfy the requirement of having a 'code' executable
    # in case the OJ doesn't provide main.cpp before cmake
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp" "int main() { return 0; }")
    add_executable(code "${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp")
endif()

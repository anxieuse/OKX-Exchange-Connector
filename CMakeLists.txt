cmake_minimum_required(VERSION 3.15)
project(OKX-WebSocket-Connector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Collect source files
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h" "include/*.hpp")

# Create the executable
add_executable(websocket_client ${SOURCES} ${HEADERS})

# Find required packages
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(OpenSSL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(websocketpp REQUIRED CONFIG)

# Add include directories
target_include_directories(websocket_client PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
    ${OPENSSL_INCLUDE_DIR}
)

# Link required libraries
target_link_libraries(websocket_client PRIVATE
    ${Boost_LIBRARIES}
    OpenSSL::SSL
    OpenSSL::Crypto
    websocketpp::websocketpp
    nlohmann_json::nlohmann_json
)

# Set necessary compile definitions
target_compile_definitions(websocket_client PRIVATE
    _WEBSOCKETPP_CPP11_THREAD_
)

# Set target properties
set_target_properties(websocket_client PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    PUBLIC_HEADER "${HEADERS}"
)
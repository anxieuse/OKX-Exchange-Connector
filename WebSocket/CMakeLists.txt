# Collect all source files in the WebSocket directory
file(GLOB WS_SOURCES "*.cpp")
file(GLOB WS_HEADERS "*.h" "*.hpp")

# Create the WebSocket library
add_executable(websocket_client ${WS_SOURCES} ${WS_HEADERS})

# Find Boost - websocketpp requires Boost
find_package(Boost REQUIRED COMPONENTS system thread)

# Find OpenSSL for TLS support
find_package(OpenSSL REQUIRED)

find_package(nlohmann_json QUIET)

# Use Conan-provided websocketpp
find_package(websocketpp REQUIRED CONFIG)

# Add include directories
target_include_directories(websocket_client PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${OPENSSL_INCLUDE_DIR}
    ${WEBSOCKETPP_INCLUDE_DIRS}
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

# Make include directory available to other targets
target_include_directories(websocket_client PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Export the library
set_target_properties(websocket_client PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    PUBLIC_HEADER "${WS_HEADERS}"
)
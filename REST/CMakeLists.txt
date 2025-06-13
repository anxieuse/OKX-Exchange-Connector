# Collect all source files in the REST directory
file(GLOB REST_SOURCES "*.cpp")
file(GLOB REST_HEADERS "*.h" "*.hpp")

# Create the REST library
add_executable(rest_client ${REST_SOURCES} ${REST_HEADERS})

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Find libcurl for HTTP requests
find_package(CURL REQUIRED)

find_package(websocketpp REQUIRED CONFIG)

# Find JSON library
find_package(nlohmann_json QUIET)

# Link all required libraries
target_link_libraries(rest_client PRIVATE 
    ${CURL_LIBRARIES}
    OpenSSL::SSL
    OpenSSL::Crypto
    websocketpp::websocketpp
)

# Add JSON library
if(nlohmann_json_FOUND)
    target_link_libraries(rest_client PRIVATE nlohmann_json::nlohmann_json)
else()
    target_link_libraries(rest_client PRIVATE nlohmann_json::nlohmann_json)
endif()

# Set include directories
target_include_directories(rest_client PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CURL_INCLUDE_DIRS}
    ${OPENSSL_INCLUDE_DIR}
)

# Make include directory available to other targets that link against this
target_include_directories(rest_client PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Export the library with proper properties
set_target_properties(rest_client PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    PUBLIC_HEADER "${REST_HEADERS}"
)
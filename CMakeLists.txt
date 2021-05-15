cmake_minimum_required(VERSION 3.0.0)
project(Boids-SFML VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Makes sure that all required SFML libraries and main executable gets
# copied over to same location.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/)

# Build SFML.
add_subdirectory(vendors/sfml/)

# GLOB all the source and header files.
file(GLOB SPACESCAPE_SOURCE_FILES src/*.cpp)
file(GLOB SPACESCAPE_HEADER_FILES include/*.hpp)
file(GLOB SPACESCAPE_ASSET_FILES assets/*.png)

# Add the main target.
add_executable(${PROJECT_NAME} ${SPACESCAPE_SOURCE_FILES} ${SPACESCAPE_HEADER_FILES})

# Include directories for main target.
target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC ${PROJECT_SOURCE_DIR}/include/
    PUBLIC ${PROJECT_SOURCE_DIR}/vendors/sfml/include/
)

# Link required libraries.
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

####################################################################################################
# cmake configuration
cmake_minimum_required(VERSION 3.15)
project(breakOut)
set(CMAKE_CXX_STANDARD 14)
####################################################################################################

####################################################################################################
# link library and include headers
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)
link_directories(${PROJECT_SOURCE_DIR}/dll)
####################################################################################################


####################################################################################################

file(GLOB SOURCE "src/classes/*.cpp")

add_executable(
        breakOut main.cpp
        src/glad.c
        src/stb_image.cpp
        ${SOURCE}
)
####################################################################################################



####################################################################################################
target_link_libraries(breakOut ${PROJECT_SOURCE_DIR}/lib/glfw3.lib)
target_link_libraries(breakOut ${PROJECT_SOURCE_DIR}/lib/assimp-vc140-mt.lib)
#target_link_libraries(breakOut ${PROJECT_SOURCE_DIR}/dll/mingw/glfw3.dll)
####################################################################################################

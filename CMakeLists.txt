cmake_minimum_required(VERSION 3.27 FATAL_ERROR)

SET(projectName magul)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#find_package(SDL2 2 REQUIRED)
include_directories("./include")
if (WIN32)
    include_directories("C:/Projects/Libs/SDL2/include")
endif (WIN32)


add_executable (${projectName} src/magul.cpp 
 src/image.cpp src/color.cpp src/circle.cpp src/vector2.cpp
 src/vector3.cpp src/ray.cpp src/hit.cpp src/camera.cpp 
 src/sphere.cpp src/basicscene.cpp src/constants.cpp
 src/lightinfo.cpp src/directionallight.cpp src/pointlight.cpp

)

TARGET_LINK_LIBRARIES(${projectName}
 SDL2
 SDL2main
 SDL2_image
 
)

if (WIN32)
    add_definitions(-DSDL_MAIN_HANDLED)
endif (WIN32)


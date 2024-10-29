cmake_minimum_required(VERSION 3.27 FATAL_ERROR)

SET(projectName magul)

find_package(SDL2 2 REQUIRED)
include_directories("./include")

add_executable (${projectName} src/magul.cpp 
 src/image.cpp src/color.cpp src/circle.cpp src/vector2.cpp
 src/vector3.cpp src/ray.cpp src/hit.cpp src/camera.cpp 
 src/sphere.cpp src/basicscene.cpp src/constants.cpp

)

TARGET_LINK_LIBRARIES(${projectName}
 SDL2
 SDL2main
 
)

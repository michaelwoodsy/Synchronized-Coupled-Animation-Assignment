cmake_minimum_required(VERSION 2.8)

project(woodard_cosc363_asg1)

add_executable(main.out main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

configure_file(back.bmp back.bmp COPYONLY)
configure_file(down.bmp down.bmp COPYONLY)
configure_file(front.bmp front.bmp COPYONLY)
configure_file(left.bmp left.bmp COPYONLY)
configure_file(right.bmp right.bmp COPYONLY)
configure_file(up.bmp up.bmp COPYONLY)
configure_file(VaseTexture.bmp VaseTexture.bmp COPYONLY)
configure_file(WoodTexture.bmp WoodTexture.bmp COPYONLY)

target_link_libraries( main.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

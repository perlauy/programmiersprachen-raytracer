add_executable(main main.cpp)

target_link_libraries(main ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(main glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS main DESTINATION .)

add_executable(scene_tests scene_tests.cpp)
target_link_libraries(scene_tests ${GLFW_LIBRARIES} ${FRAMEWORK_NAME})
add_dependencies(scene_tests glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

add_executable(main main.cpp)

target_link_libraries(main ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(main glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS main DESTINATION .)


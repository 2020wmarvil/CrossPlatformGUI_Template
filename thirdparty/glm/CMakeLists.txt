add_subdirectory(glm)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE glm)
set_target_properties(glm PROPERTIES FOLDER "glm")
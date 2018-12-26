
message("[COPY]: " ${CMAKE_BINARY_DIR})

file(COPY cube_shader.vs DESTINATION ${CMAKE_BINARY_DIR})

file(COPY cube_shader.fs DESTINATION ${CMAKE_BINARY_DIR})

set(name Layer)
add_executable(${name} layer.cpp)
target_include_directories(${name} PUBLIC ${GTEST_DIR}/include)
target_link_libraries(${name} PUBLIC gtest.lib gtest_main.lib)
set_target_properties(${name} PROPERTIES FOLDER Tests)
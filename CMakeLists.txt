cmake_minimum_required(VERSION 3.1)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd /Od /Ob0 /ZI")

project(NeuronalNetwork)

set(PICOJSON_DIR "" CACHE FILEPATH "path to picojson dir")
set(GTEST_DIR "" CACHE FILEPATH "path to gtest dir")

include_directories(${PICOJSON_DIR})
link_directories(${GTEST_DIR}/lib)

set(name OwnNetwork)
add_executable(${name}
  include/config.h
  include/connection.h
  include/common_interface.hpp
  include/functions.h
  include/layer.hpp
  include/layer_impl.hpp
  include/network.hpp
  include/network_impl.hpp
  include/neuron.hpp 
  include/neuron_impl.hpp
  include/signal.hpp
  include/types.h
  src/config.cpp
  src/connection.cpp
  src/functions.cpp
  src/own_network_main.cpp
  src/types.cpp)

target_include_directories(${name} PUBLIC include)

add_subdirectory(test)
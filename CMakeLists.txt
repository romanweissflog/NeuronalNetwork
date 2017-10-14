cmake_minimum_required(VERSION 3.1)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd /Od /Ob0 /ZI")

project(NeuronalNetwork)

set(PICOJSON_DIR "" CACHE FILEPATH "path to picojson dir")
set(GTEST_DIR "" CACHE FILEPATH "path to gtest dir")

include_directories(${PICOJSON_DIR})
link_directories(${GTEST_DIR}/lib)

set(name Network) 
set(network_include
  include/network/common_interface.hpp
  include/network/config.h
  include/network/connection.h
  include/network/functions.h
  include/network/layer.hpp
  include/network/network.hpp
  include/network/neuron.hpp
  include/network/signal.hpp
  include/network/types.h
)
source_group(Lib\\network\\include FILES ${network_include})

set(network_src
  include/network/layer_impl.hpp
  include/network/network_impl.hpp
  include/network/neuron_impl.hpp
  src/network/config.cpp
  src/network/connection.cpp
  src/network/functions.cpp
  src/network/types.cpp
)
source_group(Lib\\network\\src FILES ${network_src})

set(train_include
  include/train/train_data.hpp
  include/train/train.hpp
  include/train/test.hpp
  include/train/eval.h
)
source_group(Lib\\train\\include FILES ${train_include})

set(train_src
  include/train/train_impl.hpp
  include/train/test_impl.hpp
  src/train/eval.cpp
)
source_group(Lib\\train\\src FILES ${train_src})

add_library(${name} ${network_include} ${network_src} ${train_include} ${train_src})

target_include_directories(${name} PUBLIC include)
set_target_properties(${name} PROPERTIES FOLDER Lib)

set(name TestApp)
add_executable(${name}
  src/apps/own_network_main.cpp
)
target_link_libraries(${name} Network)
target_include_directories(${name} PUBLIC include)
set_target_properties(${name} PROPERTIES FOLDER Apps)

add_subdirectory(test)
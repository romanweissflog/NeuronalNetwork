cmake_minimum_required(VERSION 3.1)

project(NeuronalNetwork)

set(PICOJSON "" CACHE FILEPATH "path to picojson dir")
include_directories(${PICOJSON})

set(name OwnNetwork)
add_executable(${name}
  include/config.h
  include/functions.h
  include/layer.hpp
  include/layer_impl.hpp
  include/network.hpp
  include/network_impl.hpp
  include/neuron.hpp 
  include/neuron_impl.hpp 
  include/signal.hpp
  include/signal_impl.hpp
  include/types.h
  src/config.cpp
  src/functions.cpp
  src/own_network_main.cpp)

target_include_directories(${name} PUBLIC include)
cmake_minimum_required(VERSION 3.1)

project(NeuronalNetwork)

set(name OwnNetwork)
add_executable( ${name}
  include/connection.hpp
  include/connection_impl.hpp
  include/functions.h
  include/layer.hpp
  include/layer_impl.hpp
  include/network.hpp
  include/network_impl.hpp
  include/neuron.hpp 
  include/neuron_impl.hpp 
  src/functions.cpp
  src/own_network_main.cpp)

target_include_directories(${name} PUBLIC include)
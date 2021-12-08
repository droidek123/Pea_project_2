cmake_minimum_required(VERSION 3.20)
project(Pea_project_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Pea_project_2 src/main.cpp src/Graph/Graph.cpp src/Graph/Graph.hpp src/TabuSearch/TabuSearch.cpp src/TabuSearch/TabuSearch.hpp)

file(COPY sample_data/tsp17.txt sample_data/tsp4.txt
        sample_data/tsp6_1.txt sample_data/tsp6_2.txt sample_data/tsp10.txt sample_data/tsp12.txt
        sample_data/tsp13.txt sample_data/tsp14.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
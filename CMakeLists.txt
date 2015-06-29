# /* 
#  * Copyright (C): None
#  * Authors: Jimmy Baraglia
#  * Public License for more details
# */

cmake_minimum_required(VERSION 2.8.7)



# find packgaes


add_definitions(-std=gnu++0x)

# BNet
add_executable(BNet main.cpp 
src/BNet.h src/BNet.cpp
src/BNode.h src/BNode.cpp
src/BEdge.h src/BEdge.cpp
src/BPVector.h src/BPVector.cpp

)

install(TARGETS BNet DESTINATION bin)
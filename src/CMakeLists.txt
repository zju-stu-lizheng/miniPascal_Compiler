cmake_minimum_required(VERSION 3.10)
project(opc)

find_package(LLVM REQUIRED CONFIG)
include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# For jsb: specific the address
include_directories(/usr/include/llvm-13)
include_directories(/usr/include/llvm-c-13)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

execute_process(COMMAND llvm-config-13 --cxxflags OUTPUT_VARIABLE LLVM_LINK_LIBRARIES)
string(STRIP "${LLVM_LINK_LIBRARIES}" LLVM_LINK_LIBRARIES)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-DLLVM_DISABLE_ABI_BREAKING_CHECKS_ENFORCING=1 ${CMAKE_CXX_FLAGS}")
message(STATUS "LLVM_DISABLE_ABI_BREAKING_CHECKS_ENFORCING=1") 

aux_source_directory(ast AST_SOURCE)
aux_source_directory(generator GEN_SOURCE)
aux_source_directory(contents CON_SOURCE)
aux_source_directory(type TYP_SOURCE)
# aux_source_directory(vis VIS_SOURCE)

add_custom_command(
    OUTPUT pascal.l.cpp
    COMMAND lex -o pascal.l.cpp ${CMAKE_CURRENT_LIST_DIR}/lexer/pascal.l
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/lexer/pascal.l pascal.y.cpp
)

add_custom_command(
    OUTPUT pascal.y.hpp pascal.y.cpp 
    COMMAND yacc -d -o pascal.y.cpp ${CMAKE_CURRENT_LIST_DIR}/parser/pascal.y
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/parser/pascal.y
)

# For jsb: "cannot find -lz", so must quote it
# llvm_map_components_to_libnames(LLVM_LINK_LIBRARIES core)

add_executable(
    opc
    main.cpp ${AST_SOURCE} ${GEN_SOURCE} ${CON_SOURCE} ${TYP_SOURCE} pascal.l.cpp
    pascal.y.cpp pascal.y.hpp)

llvm_map_components_to_libnames(llvm_libs support core irreader executionEngine interpreter nativecodegen mcjit)

target_link_libraries(opc LLVMSupport)
set_target_properties(opc PROPERTIES LINK_LIBRARIES "${LLVM_LINK_LIBRARIES}")
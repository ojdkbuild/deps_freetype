
cmake_minimum_required ( VERSION 2.8.12 )

# project
include ( ${CMAKE_CURRENT_LIST_DIR}/../../resources/cmake/ojdkbuild_common.cmake )
project ( ojdkbuild_freetype C CXX )
set ( ${PROJECT_NAME}_OJDKBUILD_VERSION 2.6.2.0 )

# static library
add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/resources/freetype_262_cmake ${CMAKE_CURRENT_BINARY_DIR}/lookaside_freetype )

# shared_library
add_library ( ${PROJECT_NAME} SHARED ${CMAKE_CURRENT_LIST_DIR}/resources/${PROJECT_NAME}.def )
set_target_properties ( ${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C )
target_link_libraries ( ${PROJECT_NAME} lookaside_freetype )

# pkg-config
set ( ${PROJECT_NAME}_MODULE ${PROJECT_NAME} )
set ( ${PROJECT_NAME}_PC_CFLAGS "-I${CMAKE_CURRENT_BINARY_DIR}/lookaside_freetype/include -I${CMAKE_CURRENT_LIST_DIR}/lookaside_freetype/include" )
set ( ${PROJECT_NAME}_PC_LIBS "-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY} -l${PROJECT_NAME}" )
configure_file ( ${CMAKE_CURRENT_LIST_DIR}/../../resources/cmake/pkg-config.in 
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/${PROJECT_NAME}.pc )

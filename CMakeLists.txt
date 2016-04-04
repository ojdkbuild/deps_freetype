
cmake_minimum_required ( VERSION 2.8.12 )

# project
include ( ${CMAKE_CURRENT_LIST_DIR}/../../resources/cmake/ojdkbuild_common.cmake )
project ( ojdkbuild_freetype C CXX )
set ( ${PROJECT_NAME}_OJDKBUILD_VERSION 2.4.11-1 )

# static library
add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/resources/freetype_2411_cmake ${CMAKE_CURRENT_BINARY_DIR}/lookaside_freetype )

# shared_library, name without "ojdkbuild_" prefix because
# freetype has a special handling in jdk sources/makefiles
add_library ( freetype SHARED ${CMAKE_CURRENT_LIST_DIR}/resources/${PROJECT_NAME}.def )
set_target_properties ( freetype PROPERTIES LINKER_LANGUAGE C )
target_link_libraries ( freetype lookaside_freetype )
add_custom_target ( ${PROJECT_NAME} DEPENDS freetype )

# pkg-config
set ( ${PROJECT_NAME}_MODULE freetype )
set ( ${PROJECT_NAME}_PC_CFLAGS "                             -I${CMAKE_CURRENT_BINARY_DIR}/lookaside_freetype/include" )
set ( ${PROJECT_NAME}_PC_CFLAGS "${${PROJECT_NAME}_PC_CFLAGS} -I${CMAKE_CURRENT_LIST_DIR}/../../lookaside/freetype/include" )
set ( ${PROJECT_NAME}_PC_LIBS "-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY} -lfreetype" )
configure_file ( ${CMAKE_CURRENT_LIST_DIR}/../../resources/cmake/pkg-config.in 
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/freetype.pc )

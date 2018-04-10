# Copyright 2016, akashche at redhat.com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required ( VERSION 2.8.12 )

# project
include ( ${CMAKE_CURRENT_LIST_DIR}/../../resources/cmake/ojdkbuild_common.cmake )
project ( ojdkbuild_freetype C CXX )
set ( ${PROJECT_NAME}_OJDKBUILD_VERSION 2.4.11-1 )

configure_file ( ${OJDKBUILD_DIR}/resources/buildres/deplib.rc
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc )


# static library
set ( freetype_LIBNAME_POSTFIX _static CACHE INTERNAL "" )
ojdkbuild_add_external ( ${OJDKBUILD_DIR}/external/freetype )

# shared_library, name without "ojdkbuild_" prefix because
# freetype has a special handling in jdk sources/makefiles
add_library ( freetype SHARED
        ${CMAKE_CURRENT_LIST_DIR}/resources/${PROJECT_NAME}.def
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc )
set_target_properties ( freetype PROPERTIES LINKER_LANGUAGE C )
target_link_libraries ( freetype freetype_static )
set_property ( TARGET freetype APPEND_STRING PROPERTY LINK_FLAGS "/manifest:no" )

add_custom_target ( ${PROJECT_NAME} DEPENDS freetype )

# pkg-config
set ( ${PROJECT_NAME}_MODULE freetype )
set ( ${PROJECT_NAME}_PC_CFLAGS "-I${freetype_LOOKASIDE_DIR}/include" )
set ( ${PROJECT_NAME}_PC_LIBS "-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY} -lfreetype" )
configure_file ( ${CMAKE_CURRENT_LIST_DIR}/../../resources/cmake/pkg-config.in 
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/freetype.pc )

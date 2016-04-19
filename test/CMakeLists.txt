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
include ( ${CMAKE_CURRENT_LIST_DIR}/../../../resources/cmake/ojdkbuild_common.cmake )
project ( ojdkbuild_freetype_test CXX )

# dependencies
ojdkbuild_add_subdirectory (  ${CMAKE_CURRENT_LIST_DIR}/../../freetype )
set ( ${PROJECT_NAME}_DEPS freetype )
ojdkbuild_pkg_check_modules ( ${PROJECT_NAME}_DEPS_PC REQUIRED ${PROJECT_NAME}_DEPS )

# tests
enable_testing ( )
# freetype_test
add_executable ( freetype_test ${CMAKE_CURRENT_LIST_DIR}/freetype_test.cpp )
target_include_directories ( freetype_test BEFORE PRIVATE ${${PROJECT_NAME}_DEPS_PC_INCLUDE_DIRS} )
target_link_libraries ( freetype_test ${${PROJECT_NAME}_DEPS_PC_LIBRARIES} )
target_compile_options ( freetype_test PRIVATE ${${PROJECT_NAME}_DEPS_PC_CFLAGS_OTHER} )
set_target_properties ( freetype_test PROPERTIES FOLDER "test" )
if ( DEFINED CMAKE_MEMORYCHECK_COMMAND )
    add_test ( freetype_test 
            ${CMAKE_MEMORYCHECK_COMMAND} ${CMAKE_MEMORYCHECK_COMMAND_OPTIONS} 
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/freetype_test )
else ( )
    add_test ( freetype_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/freetype_test )
endif ( )



cmake_minimum_required(VERSION 3.0.0)
project(urdf_demo VERSION 0.1.0)

add_executable(${PROJECT_NAME} main.cpp)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/urdf-parser/CMakeLists.txt")
    message(FATAL_ERROR "The urdf-parser was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()



add_subdirectory(external/urdf-parser)
target_include_directories(${PROJECT_NAME} PUBLIC external/urdf-parser/include)

target_link_directories(${PROJECT_NAME} PRIVATE external/urdf-parser/src)



target_link_libraries(${PROJECT_NAME} urdfparser)
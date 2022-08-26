cmake_minimum_required(VERSION 3.16.3)

project(bit_convert)

add_definitions("-std=c++11")
set(CMAKE_CXX_STANDARD 11)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Relase CACHE STRING "Build type" FORCE)
endif()

add_compile_options(-fPIC)

aux_source_directory(. SRC_LIST)

set(Python_DIR "/home/wpwl/anaconda3/envs/aspy")
set(PYTHON_INCLUDE_DIRS "/home/wpwl/anaconda3/envs/aspy/include/python3.10")
set(PYTHON_LIBRARIES "/home/wpwl/anaconda3/envs/aspy/lib")

# set(PYTHON_INCLUDE_DIRS ${python -c"from distutils.sysconfig import get_python_inc; print(get_python_inc())"})
# set(PYTHON_LIBRARIES ${python -c"import distutils.sysconfig as sysconfig; print(sysconfig.get_config_var('LIBDIR'))"})

# FIND_PACKAGE(PYTHON COMPONENTS Interpreter Development REQUIRED)
# FIND_PACKAGE(PythonInterp)
# FIND_PACKAGE(PythonLibs ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR} EXACT REQUIRED)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(bit_convert SHARED ${SRC_LIST})
link_directories(bit_convert STATIC ${PYTHON_LIBRARIES})

# echo "${CONAN_LIBS}"

target_link_libraries(bit_convert 
    PUBLIC
        ${CONAN_LIBS}  
        # ${PYTHON_LIBRARIES}
)

target_include_directories(bit_convert
    PRIVATE
        ${PYTHON_INCLUDE_DIRS}
)

set_target_properties(bit_convert
    PROPERTIES 
        PREFIX ""
)

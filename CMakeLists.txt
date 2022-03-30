cmake_minimum_required(VERSION 3.0)
project(snore)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(matlab MATLAB_SRC)

#add_link_options(-v)

set(INC_DIR include)
set(LIB_DIR lib)

include_directories(${INC_DIR})

#decide build exe or lib
set(EXEC OFF)

if (ANDROID)
    #    message("link directories ${LIB_DIR}/${ANDROID_ABI}")
    link_directories(${LIB_DIR}/${ANDROID_ABI})
    set(LINK_LIB sox omp log fftw3)
else ()
    link_directories(${LIB_DIR})
    set(LINK_LIB gomp sox-3 fftw3-3)
endif ()

if (${EXEC})
    add_executable(snore snore.h snore.cpp ${MATLAB_SRC})
else ()
    add_library(snore SHARED snore.h snore.cpp ${MATLAB_SRC})
endif ()

target_link_libraries(snore ${LINK_LIB})
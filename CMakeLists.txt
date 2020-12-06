cmake_minimum_required(VERSION 3.0.0)
project(cutils VERSION 0.1.0)

set(INCLUDE_PATH ${CMAKE_BINARY_DIR}/../include)
set(SRC_PATH ${CMAKE_BINARY_DIR}/../src)

file(
    GLOB_RECURSE  
    SRC_FILES
    
    "${SRC_PATH}/*.c"
)

if(MSVC OR MINGW)
    set(OS_FOLDER win)
elseif(APPLE)
    set(OS_FOLDER mac)
else()
    set(OS_FOLDER linux)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib/${OS_FOLDER})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib/${OS_FOLDER})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib/${OS_FOLDER})

add_library(
    ${PROJECT_NAME}
    STATIC

    ${SRC_FILES}
)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_PATH})

if(BUILD_TESTS)
    set(TEST_PATH ${CMAKE_BINARY_DIR}/../tests)
    file(
        GLOB_RECURSE  
        TEST_FILES

        "${TEST_PATH}/*.c"
    )
    add_executable(
        "${PROJECT_NAME}_tests"

        ${TEST_FILES}
    )

    target_include_directories("${PROJECT_NAME}_tests" PUBLIC ${INCLUDE_PATH})
    target_link_libraries("${PROJECT_NAME}_tests" ${PROJECT_NAME})
endif()

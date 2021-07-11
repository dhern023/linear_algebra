cmake_minimum_required(VERSION 3.11)

project("linear_algebra")

# Target
set(PROJECT_NAME linear_algebra)

# Source groups
include_directories(
	${PROJECT_SOURCE_DIR}/linear_algebra
)

file(GLOB all_SRCS
	${PROJECT_SOURCE_DIR}/linear_algebra/*.h
    ${PROJECT_SOURCE_DIR}/linear_algebra/*.cpp
)

# Target
add_library(${PROJECT_NAME} STATIC ${all_SRCS})

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME})
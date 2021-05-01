cmake_minimum_required(VERSION 3.8)

project("linear_algebra")

set(PROJECT_NAME linear_algebra)

# Source groups
set(Header_Files ${PROJECT_SOURCE_DIR}/*.h)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files ${PROJECT_SOURCE_DIR}/*.cpp)

source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)
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

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME} DESTINATION lib)

install(EXPORT ${PROJECT_NAME} NAMESPACE mp_ DESTINATION lib/${PROJECT_NAME})
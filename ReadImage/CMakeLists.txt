cmake_minimum_required(VERSION 3.7)

project(ReadImage)

FIND_PACKAGE(ITK)

IF(ITK_FOUND)
	INCLUDE (${ITK_USE_FILE})
ELSE(ITK_FOUND)
	MESSAGE(FATAL_ERROR
	"ITK not found. Please set ITK_DIR.")
ENDIF(ITK_FOUND)

add_executable(ReadImage ReadImage.cxx)
target_link_libraries(ReadImage ${ITK_LIBRARIES})

if(BUILD_TESTING)
  add_subdirectory(test)
endif()

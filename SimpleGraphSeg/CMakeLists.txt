cmake_minimum_required(VERSION 3.7)

project(SimpleGraphSeg)

# Check for and add the ITK library
FIND_PACKAGE(ITK)
IF(ITK_FOUND)
	INCLUDE (${ITK_USE_FILE})
ELSE(ITK_FOUND)
	MESSAGE(FATAL_ERROR "ITK not found. Please set ITK_DIR.")
ENDIF(ITK_FOUND)

# Graph library (for the segmentation)
INCLUDE_DIRECTORIES("E:/Libraries/optnet_vce_lib")

# Define (?) the executable
ADD_EXECUTABLE(SimpleGraphSeg main.cpp)
TARGET_LINK_LIBRARIES(SimpleGraphSeg ${ITK_LIBRARIES})
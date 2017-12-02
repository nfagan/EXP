get_filename_component(EXP_ROOT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)

list(APPEND CMAKE_MODULE_PATH 
	${CMAKE_SOURCE_DIR}/../EXPUtil
	${CMAKE_SOURCE_DIR}/../EXPGL
	${CMAKE_SOURCE_DIR}/../EXPTask
	${CMAKE_SOURCE_DIR}/../EXPSQL)

find_package(EXPUtil REQUIRED)
find_package(EXPGL REQUIRED)
find_package(EXPTask REQUIRED)
find_package(EXPSQL REQUIRED)

list(APPEND EXP_INCLUDE_DIRS 
	${EXPUtil_INCLUDE_DIR} 
	${EXPGL_INCLUDE_DIR} 
	${EXPTask_INCLUDE_DIR} 
	${EXPSQL_INCLUDE_DIR})

list(APPEND EXP_LIBRARY_DIRS 
	${EXPUtil_LIBRARY_DIR} 
	${EXPGL_LIBRARY_DIR} 
	${EXPTask_LIBRARY_DIR} 
	${EXPSQL_LIBRARY_DIR})

list(APPEND EXP_LIBRARIES
	${EXPUtil_LIBRARIES} 
	${EXPGL_LIBRARIES} 
	${EXPTask_LIBRARIES} 
	${EXPSQL_LIBRARIES})

set(EXP_EXAMPLE_BINARY_DIR ${EXP_ROOT_DIR}/examples/bin)

set(EXPGL_INCLUDE_DIR "${EXP_ROOT_DIR}/EXPGL/include")
set(EXPGL_LIBRARY_DIR "${EXP_ROOT_DIR}/EXPGL/lib")

set(EXPGL_LIBRARIES "EXPGL" "glfw3")

if (APPLE)
	list(APPEND EXPGL_LIBRARIES 
		"-framework OpenGL"
		"-framework CoreVideo" 
		"-framework IOKit" 
		"-framework Cocoa")
endif()
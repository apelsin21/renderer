set(SOURCES
  ${SOURCES}

	${CMAKE_CURRENT_SOURCE_DIR}/commandbucket.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/glbackend.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/glcontextparam.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/glshader_program.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphicsdevice.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/sdl2window.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/vertex_buffer.cpp

  PARENT_SCOPE
)
set(HEADERS
  ${HEADERS}
	
	${CMAKE_CURRENT_SOURCE_DIR}/commandbucket.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/glbackend.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/glcontextparam.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/glshader_program.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphicsdevice.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/icontextparam.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/irenderbackend.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/ishader_program.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/iwindow.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/sdl2window.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/texture.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/vertex_buffer.hpp

  PARENT_SCOPE
)

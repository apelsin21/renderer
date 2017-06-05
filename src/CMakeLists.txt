set(SOURCES
  ${SOURCES}

	${CMAKE_CURRENT_SOURCE_DIR}/commandbucket.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/glbackend.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/glcontextparam.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphicsdevice.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/sdl2window.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mesh.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/shader_program.hpp

  PARENT_SCOPE
)
set(HEADERS
  ${HEADERS}
	
	${CMAKE_CURRENT_SOURCE_DIR}/commandbucket.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/glbackend.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/glcontextparam.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphicsdevice.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/icontextparam.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/iwindow.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/sdl2window.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/texture.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/mesh.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/texture.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/shader.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/shader_program.hpp

  PARENT_SCOPE
)

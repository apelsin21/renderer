set(SOURCES
  ${SOURCES}

	${CMAKE_CURRENT_SOURCE_DIR}/glcontextparam.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/sdl2window.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/commandbucket.cpp

  PARENT_SCOPE
)
set(HEADERS
  ${HEADERS}
	
	${CMAKE_CURRENT_SOURCE_DIR}/icontextparam.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/glcontextparam.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/iwindow.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/sdl2window.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/commandbucket.hpp

  PARENT_SCOPE
)

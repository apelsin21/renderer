set(SOURCES
    ${SOURCES}

	${CMAKE_CURRENT_SOURCE_DIR}/glcontextparam.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/sdl2window.cpp

    PARENT_SCOPE
)
set(HEADERS
   	${HEADERS}
	
	${CMAKE_CURRENT_SOURCE_DIR}/icontextparam.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/glcontextparam.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/iwindow.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/sdl2window.hpp

    PARENT_SCOPE
)

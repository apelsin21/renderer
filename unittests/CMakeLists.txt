set(TEST_SOURCES
  ${TEST_SOURCES}

	${CMAKE_CURRENT_SOURCE_DIR}/glcontextparamtest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/sdl2windowtest.cpp

  PARENT_SCOPE
)
set(TEST_HEADERS
  ${TEST_HEADERS}
	
	${CMAKE_CURRENT_SOURCE_DIR}/sdl2windowtest.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/glcontextparamtest.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/catch.hpp

  PARENT_SCOPE
)

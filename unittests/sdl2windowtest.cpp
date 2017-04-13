#include "sdl2windowtest.hpp"

using namespace std;

SCENARIO("SDL2Window creates an OpenGL context", "[SDL2Window]") {
	GIVEN("An uninitialized SDL2 window") {
    SDL2Window window;

		WHEN("we call intialize using a standard resolution") {
			THEN("the context is valid") {
        REQUIRE(window.initialize(GLContextParam(2, 1, false, false)));
        const GLuint program = glCreateProgram();
        const bool isProgram = glIsProgram(program);
        REQUIRE(isProgram);

        if(isProgram) {
          glDeleteProgram(program);
        }
			}
		}
	}
}

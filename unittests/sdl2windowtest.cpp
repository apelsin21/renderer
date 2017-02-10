#include <string>
#include <iostream>

#include "sdl2windowtest.hpp"

using namespace std;

SCENARIO("SDL2Window creates an OpenGL context", "[SDL2Window]") {
	GIVEN("An uninitialized SDL2 window") {
    SDL2Window window;

		WHEN("we call intialize using a standard resolution") {
      const bool initializedSuccessfully = window.Init(800, 600);

			THEN("it is successful") {
				REQUIRE(initializedSuccessfully);
			}
			THEN("the OpenGL context that was created is valid") {
        const GLuint program = glCreateProgram();
        const bool isProgram = static_cast<bool>(glIsProgram(program));
        REQUIRE(isProgram);

        if(isProgram) {
          glDeleteProgram(program);
        }
			}
		}
	}
}

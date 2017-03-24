#include <string>
#include <iostream>

#include "sdl2windowtest.hpp"

using namespace std;

SCENARIO("SDL2Window creates an OpenGL context", "[SDL2Window]") {
	GIVEN("An uninitialized SDL2 window") {
    SDL2Window window;
    std::vector<GLContextParam> params = {
      GLContextParam(1, 0, 800, 600, false, false)
    };

		WHEN("we call intialize using a standard resolution") {
      bool initializedSuccessfully = window.Init();
      bool createdContext = window.CreateContext(params);

			THEN("it is successful") {
				REQUIRE(initializedSuccessfully);
				REQUIRE(createdContext);
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

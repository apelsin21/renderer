#include <string>
#include <iostream>

#include "sdl2windowtest.hpp"

using namespace std;

SCENARIO("SDL2Window creates an OpenGL context", "[SDL2Window]") {
	GIVEN("An uninitialized SDL2 window") {
    SDL2Window window;
    std::vector<GLContextParam> params = {
      GLContextParam(3, 0, false, false)
    };

		WHEN("we call intialize using a standard resolution") {
      const bool initializedSuccessfully = window.Init();
      const bool createdContext = window.CreateContext(params);

			THEN("initialization is successful") {
				REQUIRE(initializedSuccessfully);
				REQUIRE(createdContext);
			}
			THEN("the context is valid") {
        const GLuint program = glCreateProgram();
        const bool isProgram = glIsProgram(program);
        REQUIRE(isProgram);

        if(isProgram) {
          glDeleteProgram(program);
        }
			}
			THEN("the resulting context is as requested") {
        REQUIRE(params[0] == window.GetCurrentContextInfo());
			}
		}
	}
}

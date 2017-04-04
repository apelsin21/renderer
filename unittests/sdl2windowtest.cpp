#include "sdl2windowtest.hpp"

using namespace std;

SCENARIO("SDL2Window creates an OpenGL context", "[SDL2Window]") {
	GIVEN("An uninitialized SDL2 window") {
    SDL2Window window;
    GLContextParam param(2, 1, false, false);

		WHEN("we call intialize using a standard resolution") {
      const bool initializedSuccessfully = window.Init();
      const bool createdContext = window.CreateContext(param);

			THEN("initialization is successful") {
				REQUIRE(initializedSuccessfully);
			}
			THEN("the context is valid") {
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
        REQUIRE(param.ToString() == window.GetCurrentContextInfo().ToString());
			}
		}
	}
}

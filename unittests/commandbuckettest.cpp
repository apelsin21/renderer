#include "commandbuckettest.hpp"

using namespace std;

SCENARIO("CommandBucket can allocate and return drawcalls", "[CommandBucket]") {
	GIVEN("that we create an uint32 commandbucket") {
    CommandBucket<int> bucket(2048);

		WHEN("we create a new drawcall") {
      std::shared_ptr<Draw> call = bucket.AddCommand(1u);

			THEN("the drawcall is allocated memory") {
				REQUIRE(call != nullptr);
			}
      THEN("testing things!") {
				SDL2Window window;
				GLContextParam param(3, 0, false, false);

      	REQUIRE(window.Init());
      	REQUIRE(window.CreateContext(param));
        GLShaderProgram program;

        REQUIRE(program.Load("vs.glsl", "fs.glsl"));

        glGenVertexArrays(1, &call->vaoID);
        glBindVertexArray(call->vaoID);

        REQUIRE(glIsVertexArray(call->vaoID));

        glGenBuffers(1, &call->vboID);

        static const GLfloat triangle[] = {
        	-1.0f, -1.0f, 0.0f,
        	 1.0f, -1.0f, 0.0f,
        	 0.0f,  1.0f, 0.0f,
        };

        glBindBuffer(GL_ARRAY_BUFFER, call->vaoID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

        REQUIRE(glIsBuffer(call->vboID));

				program.Use();

			 	glBindBuffer(GL_ARRAY_BUFFER, call->vboID);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(
					 0,
					 3,
					 GL_FLOAT,
					 GL_FALSE,
					 0,
					 (void*)0
				);

				clock_t begin = clock();
				double diff = 0;

				glClearColor(0.f, 0.0f, 0.0f, 1.0f);
				while(diff < 0.05) {
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glDrawArrays(GL_TRIANGLES, 0, 3);

					window.Display();
					diff = double(clock() - begin) / CLOCKS_PER_SEC;
					std::cout << diff << std::endl;
				}

				glDisableVertexAttribArray(0);

				glDeleteBuffers(1, &call->vboID);
				glDeleteVertexArrays(1, &call->vaoID);
      }
		}
	}
}

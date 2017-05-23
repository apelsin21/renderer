#include "commandbuckettest.hpp"
#include <iostream>
#include <string>
#include <utility>

using namespace std;

SCENARIO("CommandBucket can allocate and return drawcalls", "[CommandBucket]") {
	GIVEN("that we create an uint32 commandbucket") {
    GLGraphicsDevice device;
    CommandBucket<unsigned> bucket(2048);

		WHEN("we create a new drawcall") {
      shared_ptr<Draw> call = bucket.AddCommand(1u);

			THEN("the drawcall is allocated memory") {
				REQUIRE(call != nullptr);
			}
      THEN("testing things!") {
        REQUIRE(device.Initialize(GLContextParam("Test Window", 3, 0, false, false)));

        device.EnableFeature(GLGraphicsDevice::feature::texturing);
        Texture<GLBackend> texture = device.Create<decltype(device)::TextureType>();
        texture.Load({"data/textures/brick_wall.png"});

        VertexBuffer<GLBackend> buffer = device.Create<decltype(device)::VertexBufferType>();
        buffer.Load({
          -1.0f, -1.0f, 0.0f,
           1.0f, -1.0f, 0.0f,
           0.0f,  1.0f, 0.0f
        });

        call->vboID = buffer.GetBufferHandle();
        call->vaoID = buffer.GetLayoutHandle();

        GLShaderProgram program;
        call->shaderProgram = program.GetProgramId();
        REQUIRE(glIsProgram(call->shaderProgram));
        REQUIRE(program.Load("vs.glsl", "fs.glsl"));

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

				clock_t begin = clock();
				double diff = 0;

        bool run = true;

				glClearColor(0.f, 0.0f, 0.0f, 1.0f);
				while(run) {
					device.Submit(bucket);
					device.Display();
          device.ConsumeEvents(
            [&]() -> void { std::cout << "window closed!" << std::endl; run = false; },
            [&](int w, int h) -> void { std::cout << "window resized to " << w << "x" << h << std::endl;
                                        glViewport(0, 0, w, h);  },
            [&](int x, int y) -> void { std::cout << "window moved to " << x << "." << y << std::endl; },
            [&]() -> void { std::cout << "window maximized" << std::endl; },
            [&]() -> void { std::cout << "window minimized" << std::endl; },
            [&]() -> void { std::cout << "window shown" << std::endl; },
            [&]() -> void { std::cout << "window hidden" << std::endl; },
            [&]() -> void { std::cout << "window exposed" << std::endl; },
            [&]() -> void { std::cout << "window mouse entered" << std::endl; },
            [&]() -> void { std::cout << "window mouse left" << std::endl; },
            [&]() -> void { std::cout << "window focused" << std::endl; },
            [&]() -> void { std::cout << "window blurred" << std::endl; },
            [&]() -> void { std::cout << "window restored" << std::endl; }
          );
				}
      }

      device.Deinitialize();
		}
	}
}

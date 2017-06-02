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
				const bool textureLoadedOk = texture.Load({"test.png"});
        REQUIRE(textureLoadedOk);

        const std::vector<float> positions = {
          -1.0f, -1.0f, //BL
           1.0f, -1.0f, //BR
          -1.0f,  1.0f, //TL

          -1.0f,  1.0f, //TL
           1.0f,  1.0f, //TR
           1.0f, -1.0f, //BR
        };
        const std::vector<float> uvs = {
           0.0f,  0.0f, //BL
           1.0f,  0.0f, //BR
           0.0f,  1.0f, //TL

           0.0f,  1.0f, //TL
           1.0f,  1.0f, //TR
           1.0f,  0.0f, //BR
        };

        Mesh<GLBackend> mesh = device.Create<decltype(device)::MeshType>();
        mesh.Load(positions, uvs);

        GLShaderProgram program;
        REQUIRE(program.Load("vs.glsl", "fs.glsl"));

        call->vaoID = mesh.GetLayoutHandle();
        call->shaderProgram = program.GetProgramId();
        call->textureID = texture.GetHandle();
        call->startVertex = 0;
        call->vertexCount = positions.size() / 2;

        REQUIRE(glIsProgram(call->shaderProgram));

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

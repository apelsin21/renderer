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

      THEN("testing things!") {
        REQUIRE(device.Initialize(GLContextParam("Test Window", 3, 0, false, false)));

        Texture<GLBackend> texture = device.Create<decltype(device)::TextureType>();
        Mesh<GLBackend> mesh = device.Create<decltype(device)::MeshType>();
        Shader<GLBackend> vertexShader = device.Create<decltype(device)::ShaderType>(ShaderType::Vertex);
        Shader<GLBackend> fragmentShader = device.Create<decltype(device)::ShaderType>(ShaderType::Fragment);
        ShaderProgram<GLBackend> shaderProgram = device.Create<decltype(device)::ShaderProgramType>();

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

        mesh.Load(positions, uvs);
        REQUIRE(vertexShader.Load("vs.glsl"));
        REQUIRE(fragmentShader.Load("fs.glsl"));
        REQUIRE(shaderProgram.Load(vertexShader, fragmentShader));
        REQUIRE(texture.Load({"testbild.jpg"}));

        call->vaoID = mesh.GetLayoutHandle();
        call->shaderProgram = shaderProgram.GetHandle();
        call->textureID = texture.GetHandle();
        call->startVertex = 0;
        call->vertexCount = positions.size() / 2;

				glClearColor(0.f, 0.0f, 0.0f, 1.0f);

        bool run = true;
				while(run) {
					device.Submit(bucket);
					device.Display();
          device.ConsumeEvents(
            [&]() -> void { run = false; },
            [&](int w, int h) -> void { glViewport(0, 0, w, h);  },
            [&](int x, int y) -> void {},
            [&]() -> void {},
            [&]() -> void {},
            [&]() -> void {},
            [&]() -> void {},
            [&]() -> void {},
            [&]() -> void {},
            [&]() -> void {},
            [&]() -> void {},
            [&]() -> void {},
            [&]() -> void {}
          );
				}
      }

      device.Deinitialize();
		}
	}
}

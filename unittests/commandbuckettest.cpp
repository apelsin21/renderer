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
      shared_ptr<Draw> leftCall = bucket.AddCommand(1u);
      shared_ptr<Draw> rightCall = bucket.AddCommand(2u);

      THEN("testing things!") {
        REQUIRE(device.Initialize(GLContextParam("Test Window", 3, 0, false, false)));

        Texture<GLBackend> texture = device.Create<decltype(device)::TextureType>();
        Mesh<GLBackend> leftMesh = device.Create<decltype(device)::MeshType>();
        Mesh<GLBackend> rightMesh = device.Create<decltype(device)::MeshType>();
        Shader<GLBackend> vertexShader = device.Create<decltype(device)::ShaderType>(ShaderType::Vertex);
        Shader<GLBackend> fragmentShader = device.Create<decltype(device)::ShaderType>(ShaderType::Fragment);
        ShaderProgram<GLBackend> shaderProgram = device.Create<decltype(device)::ShaderProgramType>();

        const vector<float> leftPositions = {
          -1.0f, -1.0f, 0.0f, //BL
           0.0f, -1.0f, 0.0f, //BR
          -1.0f,  1.0f, 0.0f, //TL

          -1.0f,  1.0f, 0.0f, //TL
           0.0f,  1.0f, 0.0f, //TR
           0.0f, -1.0f, 0.0f, //BR
        };
        const vector<float> rightPositions = {
           0.0f, -1.0f, 0.0f, //BL
           1.0f, -1.0f, 0.0f, //BR
           0.0f,  1.0f, 0.0f, //TL

           0.0f,  1.0f, 0.0f, //TL
           1.0f,  1.0f, 0.0f, //TR
           1.0f, -1.0f, 0.0f, //BR
        };
        const vector<float> uvs = {
           0.0f,  0.0f, //BL
           1.0f,  0.0f, //BR
           0.0f,  1.0f, //TL

           0.0f,  1.0f, //TL
           1.0f,  1.0f, //TR
           1.0f,  0.0f, //BR
        };

        REQUIRE(vertexShader.Load("vs.glsl"));
        REQUIRE(fragmentShader.Load("fs.glsl"));
        REQUIRE(shaderProgram.Load(vertexShader, fragmentShader));

        vector<ShaderAttribute> attributes = shaderProgram.GetAttributes();
        vector<ShaderAttribute> uniforms = shaderProgram.GetUniforms();

        cout << "Found " << attributes.size() << " attributes, "
             << "and " << uniforms.size() << " uniforms.\n";

        for(const auto& attribute : attributes) {
          cout << "Attribute " << attribute.GetName() << " @ " << attribute.GetLocation() << std::endl;
        }
        for(const auto& uniform : uniforms) {
          cout << "Uniform " << uniform.GetName() << " @ " << uniform.GetLocation() << std::endl;
        }

        const ShaderAttribute positionAttrib = shaderProgram.GetAttributeByName("in_pos");
        const ShaderAttribute uvAttrib = shaderProgram.GetAttributeByName("in_uv");

        cout << "Got attribute " << positionAttrib.GetName() << std::endl;
        cout << "Got attribute " << uvAttrib.GetName() << std::endl;

        leftMesh.Add(leftPositions, positionAttrib);
        leftMesh.Add(uvs, uvAttrib);

        rightMesh.Add(rightPositions, positionAttrib);
        rightMesh.Add(uvs, uvAttrib);

        REQUIRE(texture.Load({"testbild.jpg"}));

        leftCall->vaoID = leftMesh.GetLayoutHandle();
        leftCall->shaderProgram = shaderProgram.GetHandle();
        leftCall->textureID = texture.GetHandle();
        leftCall->startVertex = 0;
        leftCall->vertexCount = leftPositions.size() / 3;

        rightCall->vaoID = rightMesh.GetLayoutHandle();
        rightCall->shaderProgram = shaderProgram.GetHandle();
        rightCall->textureID = texture.GetHandle();
        rightCall->startVertex = 0;
        rightCall->vertexCount = rightPositions.size() / 3;

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

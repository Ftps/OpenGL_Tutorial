#include "display.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "camera.hpp"

int main(int argc, char* argv[])
{
    Display display(800, 600, "Kinky");
	/*Vertex vertices[3] = { 	Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0,0.0)),
							Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5,1.0)),
							Vertex(glm::vec3(0.5, 0-0.5, 0), glm::vec2(1.0,0.0)) };

	unsigned int indices[3] = {0, 1, 2};

	Mesh mesh(vertices, 3, indices, 3);*/

	Mesh mesh("./res/cube.obj");
	Shader shader("./res/basicShader");
	Texture texture("./tex/moon.jpg");
	Camera camera(glm::vec3(0,0,-7), 70.0f, 800.0/600.0, 0.01f, 1000.0f);
	Transform transform;

	float counter = 0.0f;

	while(!display.IsClosed()){
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		transform.getPos().x = sinf(counter);
		transform.getPos().z = cosf(counter);
		//transform.getRot().z = counter;
		transform.getRot().y = 2*counter;
		//transform.setScale(glm::vec3(cosf(counter), cosf(counter), cosf(counter)));

		shader.Bind();
		shader.Update(transform, camera);
		texture.Bind(0);
		mesh.Draw();

		display.Update();
		counter += 0.02f;
	}

    return 0;
}

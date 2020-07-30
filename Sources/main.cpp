#include "display.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "camera.hpp"

int main(int argc, char* argv[])
{
    Display display(800, 600, "Kinky");
	Vertex vertices[3] = { 	Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0,0.0)),
							Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5,1.0)),
							Vertex(glm::vec3(0.5, 0-0.5, 0), glm::vec2(1.0,0.0)) };

	Mesh mesh(vertices, 3);
	Shader shader("./res/basicShader");
	Texture texture("./tex/rock.jpg");
	Camera camera(glm::vec3(0,0,-3), 70.0f, 800.0/600.0, 0.01f, 1000.0f);
	Transform transform;

	float counter = 0.0f;

	while(!display.IsClosed()){
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		transform.getPos().x = sinf(counter);
		transform.getPos().z = cosf(counter);
		//transform.getRot().z = counter;
		transform.getRot().y = 3*counter;
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

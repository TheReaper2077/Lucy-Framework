#include "Sandbox.h"

#include "Math/Vec2.inl"
#include "Math/Vec3.inl"
#include "Math/Vec4.inl"

#include "Lucy/Lucy.h"

int x = 0, y = 0, w = 200, h = 200;

std::vector<Vec3> vertices = {
	Vec3(x, y, 0), 	Vec3(0, 0, 0),
	Vec3(x, y + h, 0), Vec3(0, 1, 0),
	Vec3(x + w, y + h, 0), Vec3(1, 1, 0),
	Vec3(x + w, y + h, 0), Vec3(1, 1, 0),
	Vec3(x + w, y, 0), Vec3(1, 0, 0),
	Vec3(x, y, 0), Vec3(0, 0, 0),
};

lf::Mesh* mesh, *grid, *line;
uint8_t size = 20;
static Shader* shader;

uint8_t matrix[100][100] = {0};

TextureArray *atlas;

Vec3 initposmouse;

void Sandbox::Init() {
	lf::CreateCamera("cam0", lf::ORTHOGRAPHIC);
	lf::CreateCamera("cam1", lf::PERSPECTIVE);
	lf::EnableCamera("cam0");

	shader = lf::RegisterShader("color", "D:\\C++\\Lucy Framework\\src\\Shaders\\default.vs", "D:\\C++\\Lucy Framework\\src\\Shaders\\ray.fs");
	mesh = lf::CreateMesh(lf::Vertex3D, lf::MeshType::TRIANGLES);
	grid = lf::CreateMesh(lf::Vertex3D, lf::MeshType::LINES);
	line = lf::CreateMesh(lf::Vertex3D, lf::MeshType::LINES);

	// lf::RenderRect(mesh, Vec3(-WIDTH/HEIGHT, -1), Vec3(2*WIDTH/HEIGHT, 2*1), Vec3(1, 1, 0), false);

	for (int y = 0; y < HEIGHT; y += size) {
		for (int x = 0; x < WIDTH; x += size) {
			lf::RenderRect(grid, Vec3(x, y, 0), Vec3(size, size, 0), Vec3(1, 1, 1), false);
		}
	}

	lf::TransferMesh(grid);
}

void RayCast() {

}

void Sandbox::Update() {
	lf::ToggleWireframe(lf::IsKeyToggled(LF_KEY_E));

	lf::EnableCamera("cam1");

	lf::EnableCamera("cam0");

	if (lf::IsMousePressed(LF_MOUSE_BUTTON_1)) {
		initposmouse.x = lf::GetMousePosX();
		initposmouse.y = lf::GetMousePosY();
	}

	if (lf::IsMousePressed(LF_MOUSE_BUTTON_2)) {
		matrix[(int)lf::GetMousePosY() / size][(int)lf::GetMousePosX() / size] = 1;
	}

	const auto& finalposmouse = lf::MouseGetVec3();

	Vec2 dir = (Vec2(finalposmouse.x, finalposmouse.y) - Vec2(initposmouse.x, initposmouse.y)).normalize();
	Vec2 stepsize = Vec2(std::sqrt(1 + (dir.y/dir.x)*(dir.y/dir.x)), std::sqrt(1 + (dir.x/dir.y)*(dir.x/dir.y)));
	Vec2 stepdir = Vec2(std::abs(dir.x)/dir.x, std::abs(dir.y)/dir.y);
	Vec2 initpos = Vec2((int)initposmouse.x/size, (int)initposmouse.y/size);
	Vec2 finalpos = initpos + dir*10;
	Vec2 raylen;
	Vec2 voxel = initpos;

	if (stepdir.x) {
		raylen.x = 1*stepsize.x;
	}
	if (stepdir.y) {
		raylen.y = 1*stepsize.y;
	}

	bool isfound = false;
	float maxraydist = 100;
	float raydist = 0;
	
	while (!isfound && raydist < maxraydist) {
		if (raylen.x > raylen.y) {
			voxel.x += stepdir.x;
			raylen.x += stepsize.x;
			raydist = raylen.x;
		} else {
			voxel.y += stepdir.y;
			raylen.y += stepsize.y;
			raydist = raylen.y;
		}

		if (voxel.x >= 0 && voxel.x < 100 && voxel.y >= 0 && voxel.y < 100) {
			if (matrix[(int)voxel.y][(int)voxel.x]) {
				lf::RenderRect(mesh, Vec3(voxel.x, voxel.y)*size, Vec3(size, size), Vec3(1, 0, 0), true);
				isfound = true;
			}
		}
	}

	std::cout << voxel.GetString() << ' ' << stepsize.GetString() << '\n';

	for (int y = 0; y < (int)(HEIGHT/size); y++) {
		for (int x = 0; x < (int)(WIDTH/size); x++) {
			if (matrix[y][x] == 1)
				lf::RenderRect(mesh, Vec3(x, y)*size, Vec3(size, size), Vec3(0, 1, 1), true);
		}
	}

	// lf::RenderRect(mesh, voxel*size, Vec3(size, size), Vec3(1, 0, 0), true);
	
	lf::RenderLine(line, { initposmouse, finalposmouse }, Vec3(1, 1, 0));
	// lf::RenderLine(line, { initposmouse, initposmouse + Vec3(stepsize.x, 1)*20 }, Vec3(0, 0, 1));

	static bool toggle;

	if (lf::IsMouseToggled(LF_MOUSE_BUTTON_3) && !toggle) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		lf::GetContext()->camera->mouse_enabled = true;
		toggle = true;
	}

	if (!lf::IsMouseToggled(LF_MOUSE_BUTTON_3) && toggle) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		lf::GetContext()->camera->mouse_enabled = false;
		toggle = false;
	}

	lf::RenderMesh(grid, "color");

	lf::TransferMesh(line);
	lf::RenderMesh(line, "color");

	lf::TransferMesh(mesh);
	lf::RenderMesh(mesh, "color");

	lf::ClearMesh(line);
	lf::ClearMesh(mesh);
}

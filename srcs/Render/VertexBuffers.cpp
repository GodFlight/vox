#include "Render/VertexBuffers.h"

float* VertexBuffers::_buffers[VertexBuffers::Size];
std::array<std::vector<float>, VertexBuffers::Size> VertexBuffers::_buffs;

void VertexBuffers::Init() {
	//?    Position
	//?                     Normal
	//?                                      UV
	_buffers[Top] = new float[48] {
		0.f, 1.f, 0.f,   0.f, 1.f, 0.f,   0.f, 1.f,
		0.f, 1.f, 1.f,   0.f, 1.f, 0.f,   0.f, 0.f,
		1.f, 1.f, 1.f,   0.f, 1.f, 0.f,   1.f, 0.f,

		1.f, 1.f, 1.f,   0.f, 1.f, 0.f,   1.f, 0.f,
		1.f, 1.f, 0.f,   0.f, 1.f, 0.f,   1.f, 1.f,
		0.f, 1.f, 0.f,   0.f, 1.f, 0.f,   0.f, 1.f,
	};
	_buffers[Bottom] = new float[48] {
		0.f, 0.f, 0.f,   0.f, -1.f, 0.f,  0.f, 0.f,
		1.f, 0.f, 1.f,   0.f, -1.f, 0.f,  1.f, 1.f,
		0.f, 0.f, 1.f,   0.f, -1.f, 0.f,  1.f, 0.f,

		1.f, 0.f, 1.f,   0.f, -1.f, 0.f,  1.f, 1.f,
		0.f, 0.f, 0.f,   0.f, -1.f, 0.f,  0.f, 0.f,
		1.f, 0.f, 0.f,   0.f, -1.f, 0.f,  0.f, 1.f,
	};
	_buffers[Right] = new float[48] {
		1.f, 1.f, 0.f,   1.f, 0.f, 0.f,   0.f, 1.f,
		1.f, 0.f, 1.f,   1.f, 0.f, 0.f,   1.f, 0.f,
		1.f, 0.f, 0.f,   1.f, 0.f, 0.f,   0.f, 0.f,

		1.f, 0.f, 1.f,   1.f, 0.f, 0.f,   1.f, 0.f,
		1.f, 1.f, 0.f,   1.f, 0.f, 0.f,   0.f, 1.f,
		1.f, 1.f, 1.f,   1.f, 0.f, 0.f,   1.f, 1.f,
	};
	_buffers[Left] = new float[48] {
		0.f, 0.f, 1.f,   -1.f, 0.f, 0.f,  1.f, 0.f,
		0.f, 1.f, 1.f,   -1.f, 0.f, 0.f,  1.f, 1.f,
		0.f, 1.f, 0.f,   -1.f, 0.f, 0.f,  0.f, 1.f,

		0.f, 1.f, 0.f,   -1.f, 0.f, 0.f,  0.f, 1.f,
		0.f, 0.f, 0.f,   -1.f, 0.f, 0.f,  0.f, 0.f,
		0.f, 0.f, 1.f,   -1.f, 0.f, 0.f,  1.f, 0.f,
	};
	_buffers[Back] = new float[48] {
		0.f, 0.f, 0.f,   0.f, 0.f, -1.f,  0.f, 0.f,
		0.f, 1.f, 0.f,   0.f, 0.f, -1.f,  0.f, 1.f,
		1.f, 1.f, 0.f,   0.f, 0.f, -1.f,  1.f, 1.f,

		1.f, 1.f, 0.f,   0.f, 0.f, -1.f,  1.f, 1.f,
		1.f, 0.f, 0.f,   0.f, 0.f, -1.f,  1.f, 0.f,
		0.f, 0.f, 0.f,   0.f, 0.f, -1.f,  0.f, 0.f,
	};
	_buffers[Front] = new float[48] {
		0.f, 1.f, 1.f,   0.f, 0.f, 1.f,   0.f, 1.f,
		0.f, 0.f, 1.f,   0.f, 0.f, 1.f,   0.f, 0.f,
		1.f, 0.f, 1.f,   0.f, 0.f, 1.f,   1.f, 0.f,

		1.f, 0.f, 1.f,   0.f, 0.f, 1.f,   1.f, 0.f,
		1.f, 1.f, 1.f,   0.f, 0.f, 1.f,   1.f, 1.f,
		0.f, 1.f, 1.f,   0.f, 0.f, 1.f,   0.f, 1.f,
	};
	_buffers[MultiTop] = new float[48] {
		0.f, 1.f, 0.f,   0.f, 1.f, 0.f,   0.25f, 1.f,
		0.f, 1.f, 1.f,   0.f, 1.f, 0.f,   0.25f, 0.5f,
		1.f, 1.f, 1.f,   0.f, 1.f, 0.f,   0.f, 0.5f,

		1.f, 1.f, 1.f,   0.f, 1.f, 0.f,   0.f, 0.5f,
		1.f, 1.f, 0.f,   0.f, 1.f, 0.f,   0.f, 1.f,
		0.f, 1.f, 0.f,   0.f, 1.f, 0.f,   0.25f, 1.f,
	};
	_buffers[MultiBottom] = new float[48] {
		0.f, 0.f, 0.f,   0.f, -1.f, 0.f,  0.25f, 1.f,
		1.f, 0.f, 1.f,   0.f, -1.f, 0.f,  0.25f, 0.5f,
		0.f, 0.f, 1.f,   0.f, -1.f, 0.f,  0.5f, 0.5f,

		1.f, 0.f, 1.f,   0.f, -1.f, 0.f,  0.5f, 0.5f,
		0.f, 0.f, 0.f,   0.f, -1.f, 0.f,  0.5f, 1.f,
		1.f, 0.f, 0.f,   0.f, -1.f, 0.f,  0.25f, 1.f,
	};
	_buffers[MultiRight] = new float[48] {
		1.f, 1.f, 0.f,   1.f, 0.f, 0.f,   0.5f, 0.5f,
		1.f, 0.f, 1.f,   1.f, 0.f, 0.f,   0.75f, 0.f,
		1.f, 0.f, 0.f,   1.f, 0.f, 0.f,   0.5f, 0.f,

		1.f, 0.f, 1.f,   1.f, 0.f, 0.f,   0.75f, 0.f,
		1.f, 1.f, 0.f,   1.f, 0.f, 0.f,   0.5f, 0.5f,
		1.f, 1.f, 1.f,   1.f, 0.f, 0.f,   0.75f, 0.5f,
	};
	_buffers[MultiLeft] = new float[48] {
		0.f, 0.f, 1.f,   -1.f, 0.f, 0.f,  0.f, 0.f,
		0.f, 1.f, 1.f,   -1.f, 0.f, 0.f,  0.f, 0.5f,
		0.f, 1.f, 0.f,   -1.f, 0.f, 0.f,  0.25f, 0.5f,

		0.f, 1.f, 0.f,   -1.f, 0.f, 0.f,  0.25f, 0.5f,
		0.f, 0.f, 0.f,   -1.f, 0.f, 0.f,  0.25f, 0.f,
		0.f, 0.f, 1.f,   -1.f, 0.f, 0.f,  0.f, 0.f,
	};
	_buffers[MultiBack] = new float[48] {
		0.f, 0.f, 0.f,   0.f, 0.f, -1.f,  0.5f, 0.f,
		0.f, 1.f, 0.f,   0.f, 0.f, -1.f,  0.5f, 0.5f,
		1.f, 1.f, 0.f,   0.f, 0.f, -1.f,  0.25f, 0.5f,

		1.f, 1.f, 0.f,   0.f, 0.f, -1.f,  0.25f, 0.5f,
		1.f, 0.f, 0.f,   0.f, 0.f, -1.f,  0.25f, 0.f,
		0.f, 0.f, 0.f,   0.f, 0.f, -1.f,  0.5f, 0.f,
	};
	_buffers[MultiFront] = new float[48] {
		0.f, 1.f, 1.f,   0.f, 0.f, 1.f,   0.5f, 1.f,
		0.f, 0.f, 1.f,   0.f, 0.f, 1.f,   0.5f, .5f,
		1.f, 0.f, 1.f,   0.f, 0.f, 1.f,   0.75f, .5f,

		1.f, 0.f, 1.f,   0.f, 0.f, 1.f,   0.75f, 0.5f,
		1.f, 1.f, 1.f,   0.f, 0.f, 1.f,   0.75f, 1.f,
		0.f, 1.f, 1.f,   0.f, 0.f, 1.f,   0.5f, 1.f,
	};
	//? \ First, / Second
	_buffers[Flower] = new float[96] { //! <----- doesn't work btw
		0.f, 0.f, 0.f,   0.f, 1.f, 0.f,   1.f,  0.f,
		1.f, 0.f, 1.f,   0.f, 1.f, 0.f,   0.f,  0.f,
		0.f, 1.f, 0.f,   0.f, 1.f, 0.f,   1.f,  1.f,

		1.f, 0.f, 1.f,   0.f, 1.f, 0.f,   0.f,  1.f,
		1.f, 1.f, 1.f,   0.f, 1.f, 0.f,   1.f,  1.f,
		0.f, 1.f, 0.f,   0.f, 1.f, 0.f,   1.f,  0.f,


		0.f, 0.f, 1.f,   0.f, 1.f, 0.f,   0.f,  0.f,
		1.f, 0.f, 0.f,   0.f, 1.f, 0.f,   1.f,  0.f,
		1.f, 1.f, 0.f,   0.f, 1.f, 0.f,   1.f,  1.f,

		0.f, 0.f, 1.f,   0.f, 1.f, 0.f,   0.f,  0.f,
		1.f, 1.f, 0.f,   0.f, 1.f, 0.f,   1.f,  1.f,
		0.f, 1.f, 1.f,   0.f, 1.f, 0.f,   0.f,  1.f,
	};
	_buffers[Skybox] = new float[8 * 6 * 6] {
		-1.0f,  1.0f, -1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,
		-1.0f, -1.0f, -1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,
		1.0f, -1.0f, -1.0f,  0.f, 0.f, 0.f, 0.f, 0.f,
		1.0f, -1.0f, -1.0f,  0.f, 0.f, 0.f, 0.f, 0.f,
		1.0f,  1.0f, -1.0f,  0.f, 0.f, 0.f, 0.f, 0.f,
		-1.0f,  1.0f, -1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,

		-1.0f, -1.0f,  1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,
		-1.0f, -1.0f, -1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,
		-1.0f,  1.0f, -1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,
		-1.0f,  1.0f, -1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,
		-1.0f,  1.0f,  1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,
		-1.0f, -1.0f,  1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,

		1.0f, -1.0f, -1.0f,  0.f, 0.f, 0.f, 0.f, 0.f,
		1.0f, -1.0f,  1.0f,  0.f, 0.f, 0.f, 0.f, 0.f,
		1.0f,  1.0f,  1.0f,  0.f, 0.f, 0.f, 0.f, 0.f,
		1.0f,  1.0f,  1.0f,  0.f, 0.f, 0.f, 0.f, 0.f,
		1.0f,  1.0f, -1.0f,  0.f, 0.f, 0.f, 0.f, 0.f,
		1.0f, -1.0f, -1.0f,  0.f, 0.f, 0.f, 0.f, 0.f,

		-1.0f, -1.0f,  1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,
		-1.0f,  1.0f,  1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,
		1.0f,  1.0f,  1.0f,  0.f, 0.f, 0.f, 0.f, 0.f,
		1.0f,  1.0f,  1.0f,  0.f, 0.f, 0.f, 0.f, 0.f,
		1.0f, -1.0f,  1.0f,  0.f, 0.f, 0.f, 0.f, 0.f,
		-1.0f, -1.0f,  1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,

		-1.0f,  1.0f, -1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,
		1.0f,  1.0f, -1.0f,  0.f, 0.f, 0.f, 0.f, 0.f,
		1.0f,  1.0f,  1.0f,  0.f, 0.f, 0.f, 0.f, 0.f,
		1.0f,  1.0f,  1.0f,  0.f, 0.f, 0.f, 0.f, 0.f,
		-1.0f,  1.0f,  1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,
		-1.0f,  1.0f, -1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,

		-1.0f, -1.0f, -1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,
		-1.0f, -1.0f,  1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,
		1.0f, -1.0f, -1.0f,  0.f, 0.f, 0.f, 0.f, 0.f,
		1.0f, -1.0f, -1.0f,  0.f, 0.f, 0.f, 0.f, 0.f,
		-1.0f, -1.0f,  1.0f, 0.f, 0.f, 0.f, 0.f, 0.f,
		1.0f, -1.0f,  1.0f,  0.f, 0.f, 0.f, 0.f, 0.f
	};
	_buffs[Cactus] = Geometry::ReadGeometry("./resources/Models/Cactus.obj");
}

void VertexBuffers::Destroy() {
	for (int i = First; i <= Last; i++)
		delete _buffers[i];
}

float* VertexBuffers::GetBuffer(BufferType t) {
	if (_buffers[t])
		return _buffers[t];
	else
		return _buffs[t].data();
}
#include "Types.h"
#include "World/Shard.h"
#include "Render/Objects.h"
#include "Engine/Locator.hpp"

void Shard::UpdateGeometry() {
	GLRenderer* r = _game->GetRenderer();
	//? If shard is active, remove models from the renderer
	if (_state) {
		for (RenderModel* model : _models) {
			r->RemoveModel(model);
		}
	}
	//? Delete old geometry and models
	for (RenderModel* model : _models) {
		delete model->GetGeometry();
		delete model;
	}
	_models.clear();
	//? For every block type
	for (uint t = (uint)BlockType::First + 1; t <= (uint)BlockType::Last; t++) {
		if (!HasType((BlockType)t))
			continue;
		RenderModel* model = GenerateModelOfType((BlockType)t);
		_models.push_back(model);
	}
	//? If shard is active, add models to the renderer
	if (_state) {
		for (RenderModel* model : _models) {
			r->AddModel(model);
		}
	}
}

RenderModel* Shard::GenerateModelOfType(BlockType type) {
	GLRenderer* r = _game->GetRenderer();
	ResourceLoader* rs = _game->GetResources();
	World* w = _game->GetWorld();
	uint count = CountType(type);
	std::vector<float> vertexBuffer;

	for (int x = 0; x < 16 && count > 0; x++)
		for (int y = 0; y < 16 && count > 0; y++)
			for (int z = 0; z < 16 && count > 0; z++) {
				if (_blocks[x][y][z] != type)
					continue;
				std::vector<float> block = GenerateBlock(w, _position * 16 + glm::ivec3(x, y, z));
				if (block.size() == 0)
					continue;
				for (int i = 0; i < block.size(); i += 8) {
					block[i + 0] += (float)x;
					block[i + 1] += (float)y;
					block[i + 2] += (float)z;
				}
				vertexBuffer.reserve(block.size());
				vertexBuffer.insert(vertexBuffer.end(), block.begin(), block.end());
				count--;
			}
	Geometry* g = new Geometry(vertexBuffer);
	RenderModel* model = new RenderModel(r, rs->GetShader("Base"), rs->GetTexture(type), g);
	model->SetPosition(_position * 16);
	return (model);
};

std::vector<float> Shard::GenerateBlock(World* w, glm::ivec3 globalBlockPos) {
	std::vector<float> res;

	//? Right face
	if (w->GetBlock(globalBlockPos + glm::ivec3(1, 0, 0)) == BlockType::Air) {
		float *buffer = Geometry::FaceRight();
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
		delete buffer;
	}
	//? Left face
	if (w->GetBlock(globalBlockPos + glm::ivec3(-1, 0, 0)) == BlockType::Air) {
		float *buffer = Geometry::FaceLeft();
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
		delete buffer;
	}
	//? Top face
	if (w->GetBlock(globalBlockPos + glm::ivec3(0, 1, 0)) == BlockType::Air) {
		float *buffer = Geometry::FaceTop();
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
		delete buffer;
	}
	//? Bottom face
	if (w->GetBlock(globalBlockPos + glm::ivec3(0, -1, 0)) == BlockType::Air) {
		float *buffer = Geometry::FaceBottom();
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
		delete buffer;
	}
	//? Front face
	if (w->GetBlock(globalBlockPos + glm::ivec3(0, 0, 1)) == BlockType::Air) {
		float *buffer = Geometry::FaceFront();
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
		delete buffer;
	}
	//? Back face
	if ((uint)w->GetBlock(globalBlockPos + glm::ivec3(0, 0, -1)) == (uint)BlockType::Air) {
		float *buffer = Geometry::FaceBack();
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
		delete buffer;
	}
	return res;
}
#pragma once

typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef long long int64;
typedef int int32;
typedef short int16;
typedef char int8;

typedef uint32 uint;

#define SECONDS_IN_A_DAY (120.f)


class Entity;
class Game;
class Locator;
class MapGeneration;
class Input;
class Player;
class Camera;
class CubeMap;
class DirLight;
class Geometry;
class GLRenderer;
class Material;
class RenderModel;
class Shader;
class Skybox;
class Texture;
class VertexBuffers;
class UIController;
class ILogger;
class NullLogger;
class TerminalLogger;
class Utilities;
class Chunk;
class ResourceLoader;
class Shard;
class World;
class NearestBlocks;
class ShadowRenderer;
class BlockType;
#include "World/BlockType.h"
class Block;
class Framebuffer;

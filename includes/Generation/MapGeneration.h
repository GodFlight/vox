#pragma once

// #include <vector>
// #include <unordered_map>
// #include <iostream>
// #include <math.h>
#include <string>

// #include <GL/glew.h>
// #include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>


// #include "BiomeDefine.h"
// #include "Engine/Engine.h"
// #include <cstdint>
#include "FastNoise.h"
#include "Types.h"

class MapGeneration
{
public:
    MapGeneration();
    ~MapGeneration() {};
public:
    struct StoredMapData
    {
        int elevation;
        int biom;
        BlockType firstBlockLayer;
        BlockType lastBlockLayer;
        StoredMapData() {};
    };

    enum GenerationType {
        Basic = 0,
        Testing,
        Land,
        BeachLand,
        HighLand,
        BiomeDefinition,
        First = Basic,
        Last = BiomeDefinition,
        Size = Last + 1
    };

    StoredMapData Generation(glm::ivec2 globalPos, glm::ivec2 blockPosition);
    StoredMapData Generation(glm::ivec2 globalPos, glm::ivec2 blockPosition, GenerationType genType);
    FastNoise& GetNoise(GenerationType);
    float GetExpValue();
    void SetExpValue(float value);
    float GetTeracceValue();
    void SetTerraceValue(float value);
	std::string GetNoiseName(GenerationType);
private:
    float _exp; // For sharp mountain peaks
    float _terraceValue; // For terrace
    FastNoise _noises[Size];
	std::string _noiseNames[Size];
  
    StoredMapData TestingDistance(glm::ivec2 pos, glm::ivec2 blockPosition);
    StoredMapData Voronoi(glm::ivec2 pos, glm::ivec2 blockPosition);
   
    float BasicGenerationColumn(glm::ivec2 pos);
    float LandGenerationColumn(glm::ivec2 pos, int biome);
    float HighLandGenerationColumn(glm::ivec2 pos, int biome);
  
    bool CheckingTheBiomeInTheNextColumn(glm::ivec3 middle);
    int BiomeGeneration(glm::ivec2 pos, glm::ivec2 blockPosition);

    float _Hash(const float n);
    float Noise(const glm::vec3 &x);
    float Smoothstep(float edge0, float edge1, float x);
    float VoronoiDistance(glm::vec2 x);
    glm::vec2 random2(glm::vec2 p);
    float random (glm::vec2 st)
    {
        return glm::fract(sin(glm::dot(st, glm::vec2(12.9898, 78.233))) * 43758.5453123);
    }
    template <typename T> inline T _Lerp(const T &v0, const T &v1, float t)
    {
        return v0 + (v1 - v0) * std::max(0.f, std::min(1.f, t));
    };
};


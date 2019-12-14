#include "Generation/MapGeneration.h"
#include "Generation/BiomeDefine.h"
#include <iostream>
#define LERP MapGeneration::_Lerp
#define VEC3 glm::vec3

// int MapGeneration::BiomeDefinition(float e, float m)
// {
//   if (e < 0.1)
//     return OCEAN;
//   if (e < 0.12) return BEACH;
  
//   if (e > 0.8) {
//     if (m < 0.1) return SCORCHED;
//     if (m < 0.2) return BARE;
//     if (m < 0.5) return TUNDRA;
//     return SNOW;
//   }

//   if (e > 0.6) {
//     if (m < 0.33) return TEMPERATE_DESERT;
//     if (m < 0.66) return SHRUBLAND;
//     return TAIGA;
//   }

//   if (e > 0.3) {
//     if (m < 0.16) return TEMPERATE_DESERT;
//     if (m < 0.50) return GRASSLAND;
//     if (m < 0.83) return TEMPERATE_DECIDUOUS_FOREST;
//     return TEMPERATE_RAIN_FOREST;
//   }

//   if (m < 0.16) return SUBTROPICAL_DESERT;
//   if (m < 0.33) return GRASSLAND;
//   if (m < 0.66) return TROPICAL_SEASONAL_FOREST;
//   return TROPICAL_RAIN_FOREST;
// }

glm::vec2 MapGeneration::random2(glm::vec2 p) {
    return glm::fract(glm::sin(glm::vec2(dot(p, glm::vec2(127.1f ,311.7f)), glm::dot(p, glm::vec2(269.5f, 183.3f)))) * 43758.5453f);
}
float MapGeneration::VoronoiDistance(glm::vec2 x)
{
    glm::ivec2 p = glm::ivec2(glm::floor( x ));
    glm::vec2  f = glm::fract( x );

    glm::ivec2 mb;
    glm::vec2 mr;

    float res = 8.f;
    for(int j= -1; j <= 1; j++)
    for(int i= -1; i <= 1; i++)
    {
        glm::ivec2 b = glm::ivec2(i, j);
         glm::vec2  r = glm::vec2(b) + random2(p + b) - f;
        float d = glm::dot(r,r);

        if( d < res )
        {
            res = d;
            mr = r;
            mb = b;
        }
    }

    res = 8.f;
    for(int j= -2; j <= 2; j++)
    for(int i= -2; i <= 2; i++)
    {
        glm::ivec2 b = mb + glm::ivec2(i, j);
        glm::vec2  r = glm::vec2(b) + random2(p + b) - f;
        float d = glm::dot(0.5f * (mr+r), glm::normalize(r - mr));

        res = glm::min( res, d );
    }

    return res;
}


float MapGeneration::Smoothstep(float edge0, float edge1, float x)
{
    x = glm::clamp((x - edge0) / (edge1 - edge0), 0.f, 1.f);
    return x * x * (3 - 2 * x);
}

bool MapGeneration::CheckingTheBiomeInTheNextColumn(glm::ivec3 middle) // x,y - coord. z - bioms
{
  FastNoise noise = _noises[BiomeDefinition];

  glm::ivec3 top = glm::ivec3(middle.x, middle.y + 1, 0);
  glm::ivec3 right = glm::ivec3(middle.x + 1, middle.y, 0);
  glm::ivec3 left = glm::ivec3(middle.x - 1, middle.y, 0);
  glm::ivec3 buttom = glm::ivec3(middle.x, middle.y - 1, 0);

  top.z = floorf((noise.GetNoise(top.x, top.y) * 0.5 + 0.5) * 10);
  if (top.z != middle.z)
    return true;

  right.z = floorf((noise.GetNoise(right.x, right.y) * 0.5 + 0.5) * 10);
  if (right.z != middle.z)
    return true;
 
  left.z = floorf((noise.GetNoise(left.x, left.y) * 0.5 + 0.5) * 10);
  if (left.z != middle.z)
    return true;

  buttom.z = floorf((noise.GetNoise(buttom.x, buttom.y) * 0.5 + 0.5) * 10);
  if (buttom.z != middle.z)
    return true;
  
  return false;
}

int MapGeneration::BiomeGeneration(glm::ivec2 pos, glm::ivec2 blockPosition)
{
  FastNoise noise = _noises[BiomeDefinition];

  float globalX = pos.x * 16, globalY = pos.y * 16;
  float nx = globalX + blockPosition.x, ny = globalY + blockPosition.y;
  
  int biom = floorf((noise.GetNoise(nx, ny) * 0.5 + 0.5) * 10);

  if (biom == 1)
    return OCEAN;
  else if (biom == 2)
    return BEACH;
  else if (biom >= 3 && biom <= 5)
    return GRASSLAND;
  else if (biom < 9)
    return TAIGA;
  else
    return GRASSLAND;
  
  // bool check = CheckingTheBiomeInTheNextColumn(glm::ivec3(nx, ny, biome.biom));
  // if (check == true)
  // {
  //   std::cout << "Border x: " << nx << " z: " << ny << std::endl;
  //   biome.elevation = 100;
  // // }
  // // else
  //   biome.elevation = 0;

  // if (biome.biom == 1)
  //   biome.biom = OCEAN;
  // else if (biome.biom == 2)
  //   biome.biom = BEACH;
  // else if (biome.biom >= 3 && biome.biom <= 5)
  //   biome.biom = GRASSLAND;
  // else if (biome.biom < 9)
  //   biome.biom = TAIGA;
  // else
  //   biome.biom = GRASSLAND;
  // return biome.biom;
}

float MapGeneration::_Hash(const float n)
{
    float x = sin(n) * 43758.5453f;
    return x - floor(x);
}



float MapGeneration::Noise(const glm::vec3 &x)
{
    glm::vec3 p(floor(x.x), floor(x.y), floor(x.z));
    glm::vec3 f(x.x - p.x, x.y - p.y, x.z - p.z);
    f = f * (f * (glm::vec3(3.f, 3.f, 3.f) - f * 2.f));
    float n = glm::dot(p, glm::vec3(1.f, 57.f, 113.f));
    return LERP(LERP(
                    LERP(_Hash(n +  0.f), _Hash(n +  1.f), f.x),
                    LERP(_Hash(n + 57.f), _Hash(n + 58.f), f.x), f.y),
                LERP(
                    LERP(_Hash(n + 113.f), _Hash(n + 114.f), f.x),
                    LERP(_Hash(n + 170.f), _Hash(n + 171.f), f.x), f.y), f.z);
}

MapGeneration::StoredMapData MapGeneration::TestingDistance(glm::ivec2 pos, glm::ivec2 blockPosition)
{
  FastNoise var = _noises[Testing];

  float globalX = pos.x * 16, globalY = pos.y * 16;
  float nx = globalX + blockPosition.x, ny = globalY + blockPosition.y;
  float evel = var.GetNoise(nx, ny);
  std::cout << evel << std::endl;
  StoredMapData test;
  test.elevation = (evel * 0.5 + 0.5) * 10;
  var.SetCellularReturnType(FastNoise::Distance2);
  float distance = var.GetNoise(nx, ny);
  std::cout << distance * 10 << std::endl;
  // test.elevation = distance;
  return test;
  // if (distance < 0.0057024 || (distance > -0.0157024 && distance < 0))
    // std::cout << "x: " << nx << "| z: " << ny << std::endl; 
  // if (nx >= 40 && nx <= 55 && ny >= 3 && ny <= 11) //0.0157024
  // {std::cout << "x: " << nx << "| z: " << ny << "  distance: ";
  // std::cout << distance << std::endl;}
  // distance = distance * 200.f;
}

float  MapGeneration::HighLandGenerationColumn(glm::ivec2 pos, int biome)
{
  FastNoise noise = _noises[HighLand];
  float exp = _exp;
  float terraceValue = _terraceValue;

  // float globalX = pos.x * 16, globalY = pos.y * 16;
  // float nx = globalX + blockPosition.x, ny = globalY + blockPosition.y;

  float e = 1.f * (noise.GetNoise(pos.x, pos.y));
  float e1 = 0.50f * (noise.GetNoise(2.f * pos.x, 2.f * pos.y));
  float e2 = 0.25f * (noise.GetNoise(4.f * pos.x, 4.f * pos.y));
  // float e3 = 0.13f * (noise.GetNoise(8.f * nx, 8.f * ny));
  // float e4 = 0.06f * (noise.GetNoise(16.f * nx, 16.f * ny));
  // float e5 = 0.03f * (noise.GetNoise(32.f * nx, 32.f * ny));
  // e += e1 + e2 + e3 + e4 + e5;
  e += e1 + e2;
  e = (e * 0.5f + 0.5f) * 10; // range 0..10

  float mountainPeaks = pow(e, exp);
  float terrace = round(mountainPeaks * terraceValue) / terraceValue;

  int elevation = (int)floorf(terrace);
  return elevation;
}

float MapGeneration::LandGenerationColumn(glm::ivec2 pos, int biome)
{
	FastNoise noise = _noises[Land];
  float terraceValue = _terraceValue;

  float e = 0.5f * (noise.GetNoise(2.f * pos.x, 2.f * pos.y));
  e = (e * 0.5f + 0.5f) * 10.f; // range 0..10;
  
  // if (CheckingTheBiomeInTheNextColumn(glm::ivec3(pos, biome)))
    // std::cout << "border: " << pos.x << " " << pos.y << std::endl;

  float terrace = round(e * terraceValue) / terraceValue;  
  int elevation = (int)floorf(terrace);
  return elevation;
}

float MapGeneration::BasicGenerationColumn(glm::ivec2 pos)
{
  FastNoise noise = _noises[Basic];
  float terraceValue = _terraceValue;

  float e = 1.f * (noise.GetNoise(1.f * pos.x, 1.f * pos.y));
  float e1 = 0.50f * (noise.GetNoise(2.f * pos.x, 2.f * pos.y));
  // float e2 = 0.25f * (noise.GetNoise(4.f * nx, 4.f * ny));
  // float e3 = 0.13f * (noise.GetNoise(8.f * nx, 8.f * ny));
  // float e4 = 0.06f * (noise.GetNoise(16.f * nx, 16.f * ny));
  // float e5 = 0.03f * (noise.GetNoise(32.f * nx, 32.f * ny));
  e += e1;
  // float m = 1.f * (noise.GetNoise(1.f * nx, 1.f * ny));
  // float m1 = 0.75f * (noise.GetNoise(2.f * nx, 2.f * ny));
  // float m2 = 0.33f * (noise.GetNoise(4.f * nx, 4.f * ny));
  // float m3 = 0.33f * (noise.GetNoise(8.f * nx, 8.f * ny));
  // float m4 = 0.33f * (noise.GetNoise(16.f * nx, 16.f * ny));
  // float m5 = 0.50f * (noise.GetNoise(32.f * nx, 32.f * ny));
  // m += m1 + m2 + m2;//+ m3 + m4 + m5;
  // m /= (1.0f + 0.75f + 0.33f + 0.33f + 0.33f + 0.50f);
  e = (e * 0.5f + 0.5f) * 10.f;

  float terrace = round(e * terraceValue) / terraceValue;  
  int elevation = (int)floorf(terrace);
  return elevation;
  // return block;
  // (umap)[position] = new StoredMapData(pow(e, EXP) - 0.42); // резкие горные пики
  // (umap)[position] = new StoredMapData((round((e * 16) / 16))); // терассы
}




MapGeneration::StoredMapData MapGeneration::Generation(glm::ivec2 globalPos, glm::ivec2 blockPosition)
{
  StoredMapData column;

  float globalX = globalPos.x * 16, globalY = globalPos.y * 16;
  glm::vec2 pos = glm::ivec2(globalX + blockPosition.x, globalY + blockPosition.y);

  column.biom = BiomeGeneration(globalPos, blockPosition);
  switch (column.biom)
  {
    case GRASSLAND:
    {
      column.firstBlockLayer = BlockType::Dirt;
      column.lastBlockLayer = BlockType::Grass;
      column.elevation = LandGenerationColumn(pos, column.biom);
      return column;
    }
      break;
    case BEACH:
    {
      column.firstBlockLayer = BlockType::Sand;
      column.lastBlockLayer = BlockType::Sand;
      column.elevation = LandGenerationColumn(pos, column.biom);
      return column;
    }
      break;
    default:
    {
      column.firstBlockLayer = BlockType::Dirt;
      column.lastBlockLayer = BlockType::Grass;
      column.elevation = LandGenerationColumn(pos, column.biom);
      return column;
    }
  }
}


MapGeneration::StoredMapData MapGeneration::Generation(glm::ivec2 globalPos, glm::ivec2 blockPosition, MapGeneration::GenerationType genType)
{
  StoredMapData column;

  float globalX = globalPos.x * 16, globalY = globalPos.y * 16;
  glm::vec2 pos = glm::ivec2(globalX + blockPosition.x, globalY + blockPosition.y);

  switch (genType)
  {
    case GenerationType::Basic:
    {
      column.biom = 0;
      column.elevation = BasicGenerationColumn(pos);
      column.firstBlockLayer = BlockType::Stone;
      column.lastBlockLayer = BlockType::Stone;
      return column;
    }
      break;
    case GenerationType::Land:
    {
      column.biom = 0;
      column.elevation = LandGenerationColumn(pos, column.biom);
      column.firstBlockLayer = BlockType::Dirt;
      column.lastBlockLayer = BlockType::Grass;
      return column;
    }
      break;
    case GenerationType::HighLand:
    {
      column.biom = 0;
      column.elevation = BasicGenerationColumn(pos);
      column.firstBlockLayer = BlockType::Sand;
      column.lastBlockLayer = BlockType::Sand;
      
      return column;
    }
      break;
    case GenerationType::Testing:
    {
      column.biom = 0;
      column.elevation = BasicGenerationColumn(pos);
      column.firstBlockLayer = BlockType::Stone;
      column.lastBlockLayer = BlockType::Stone;
      return column;
    }
      break;
    default:
    {
      column.biom = 0;
      column.elevation = BasicGenerationColumn(pos);
      column.firstBlockLayer = BlockType::Stone;
      column.lastBlockLayer = BlockType::Stone;
      return column;
    }
      break;
  }
}


MapGeneration::MapGeneration()
{
  _exp = 2.2f;
  _terraceValue = 32.f;
  _noises[BiomeDefinition].SetNoiseType(FastNoise::Cellular);
  _noises[BiomeDefinition].SetSeed(1330);
  _noises[BiomeDefinition].SetFrequency(0.001);
  _noises[BiomeDefinition].SetCellularReturnType(FastNoise::CellValue);
  _noises[BiomeDefinition].SetCellularDistanceFunction(FastNoise::Natural);
  _noises[Basic].SetNoiseType(FastNoise::Perlin);
  _noises[Basic].SetFrequency(0.1);
  _noises[Land].SetNoiseType(FastNoise::Simplex);
  _noises[Land].SetFrequency(0.01);
  _noises[HighLand].SetNoiseType(FastNoise::Perlin);
  _noises[HighLand].SetFrequency(0.01);
  _noises[Testing].SetNoiseType(FastNoise::Cellular);
  _noises[Testing].SetFrequency(0.05);
  _noises[Testing].SetSeed(1339);
  _noises[Testing].SetCellularDistanceFunction(FastNoise::Natural);
  _noiseNames[Testing] = "Testing";
  _noiseNames[Basic] = "Basic";
  _noiseNames[Land] = "Land";
  _noiseNames[HighLand] = "HighLand";
  _noiseNames[BiomeDefinition] = "BiomeDefinition";
}

FastNoise& MapGeneration::GetNoise(MapGeneration::GenerationType genType) {return _noises[genType];};

float MapGeneration::GetExpValue() {return _exp;};

float MapGeneration::GetTeracceValue() {return _terraceValue;};

void MapGeneration::SetExpValue(float value) {_exp = value;};

void MapGeneration::SetTerraceValue(float value) {_terraceValue = value;};

std::string MapGeneration::GetNoiseName(GenerationType t) {return _noiseNames[t];};
#include "Map.h"
#include "SuperStory.h"
#include <fstream>

Map::Map()
{
}

Map::~Map()
{

}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			SuperStory::AddTile(atoi(&tile), x * 32, y * 32);
			mapFile.ignore();
		}
	}

	mapFile.close();
}


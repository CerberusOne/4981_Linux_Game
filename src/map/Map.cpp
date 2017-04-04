/*------------------------------------------------------------------------------
* Source: Map.cpp
*
* Functions:
*       Map(string file);
*       int loadFileData();
*       void genWalls(const struct MapPoint wstart[MAX_WALLS]);
*       string getFile();
*       void setFile(string f);
*       void mapLoadToGame();
*       void printData();
*
* Date: March 23, 2017
*
* Revisions:
* Edited By : Name 2016/JAN/25 - Description
*
* Designer: Jordan Lin
*
* Author: Jordan Lin
*
* Notes:
* Map Class functions used for reading in a map file and loading the map into the game.
------------------------------------------------------------------------------*/
#include <initializer_list>
#include <type_traits>
#include "Map.h"

using namespace std;

/**
 * Date: Mar. 23, 2017
 * Author: Jordan Lin
 * Function Interface: Map(string file)
 * Parameters:
 *      file - File name, must be a CSV File
 * Description:
 * Map Object Constructor, creates a map object using the map selected file name.
 */
Map::Map(const string& file):fname(file) {
    AIMap = {};
    mapdata = {};
}

/**
 * Date: Mar. 23, 2017
 * Author: Jordan Lin
 * Function Interface: int loadFileData()
 * Description:
 * Read's the Map CSV file map data with the appropriate tile IDs
 */
int Map::loadFileData() {
    // Open file stream for selected map file
    ifstream file(fname.c_str());

    if (file.fail()) {
        logv("failed to open file\n");
        return 0;
    }

    // Vector of wallstart positions
    vector<MapPoint> wallStart;

    // Indices
    int i = 0;
    int j = 0;

    // Reading in the filestream into a buffer.
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    std::string buffer(size, ' ');
    file.seekg(0);
    file.read(&buffer[0], size);

    for (const char& ch : buffer) {
        switch (ch) {
            case ',':
                continue;
            case '\n':
                j = 0;
                ++i;
                continue;
            case WALL:              //Wall piece found, update AI Map
                AIMap[i][j] = 1;
                break;
            case WALL_START:        //Label start of wall rectangle
                wallStart.emplace_back( MapPoint{j, i} );
                ++wallStartCount;
                AIMap[i][j] = 1;
                break;
            // case CONCRETE_START:    //Start of concrete area
            case ZOMBIE_SPAWN:      //Zombie spawn Points
                zombieSpawn[zombieSpawnCount].x = j;
                zombieSpawn[zombieSpawnCount].y = i;
                ++zombieSpawnCount;
                break;
            case SHOP_SPOT:         // Shop spot points
                shops[shopCount].x = j;
                shops[shopCount].y = i;
                ++shopCount;
                break;
            case BASE_START:        //Start of base area
                base.x = j;
                base.y = i;
                break;
        }
        mapdata[i][j] = ch;               //Store map file value
        ++j;
    }
    genWalls(wallStart);
    return 1;
}

/**
 * Date: Mar. 23, 2017
 * Author: Jordan Lin
 * Function Interface: void genWalls(const struct MapPoint wstart[MAX_WALLS])
 * Parameters:
 *      wstart - Array of wall start MapPoints.
 * Description:
 * Read's the Map CSV file map data with the appropriate tile IDs
 */
void Map::genWalls(const vector<MapPoint>& wallStart) {
    for (const auto& w : wallStart) {
        logv("Point = %d, %d\n", w.x, w.y);
    }
    int startx;
    int starty;
    int nextx;
    int nexty;
    int endx;
    int endy;

    for (const auto& w : wallStart) {
        startx = w.x;
        starty = w.y;
        nextx = startx + 1;
        nexty = starty + 1;
        logv("nextx = %d nexty = %d\n", nextx, nexty);
        while (mapdata[starty][nextx] == WALL) {
            if(nextx > M_WIDTH) {
                break;
            }
            nextx ++;
        }
        endx = nextx;
        while (mapdata[nexty][startx] == WALL) {
            if(nexty > M_HEIGHT) {
                break;
            }
            nexty++;
        }
        endy = nexty;
        walls.emplace_back( MapWall{ startx * T_SIZE, starty * T_SIZE, (endx - startx) * T_SIZE,
                           (endy - starty) * T_SIZE });
    }
}

/**
 * Date: Mar. 23, 2017
 * Author: Jordan Lin
 * Function Interface: void mapLoadToGame()
 * Description:
 * Creates the wall structures using the GameManager createWall function.
 */
void Map::mapLoadToGame() {
    for (const auto& w : walls) {
        logv("Creating wall");
        GameManager::instance()->createWall(w.x, w.y, w.width, w.height);
    }
}

/**
 * Date: Mar. 23, 2017
 * Author: Jordan Lin
 * Function Interface: string getFile()
 * Parameters:
 * Description:
 * Print Map Data loaded includeing:
 *  - Base Position
 *  - Zombie spawn points
 *  - Shop Positions
 *  - Wall Position/Dimensions
 */
void Map::printData() {
    logv("MAP DATA\n");
    for (const auto& row : mapdata) {
        for (const char& elem : row) {
            logv("%c", elem);
        }
        logv("\n");
    }
    logv("\n");
    logv("BASE POSITION");
    logv("Position: %d, %d\n", base.x, base.y);

    logv("SPAWN POINTS");
    for(int i = 0; i < zombieSpawnCount; i++) {
        logv("Spawn Point: %d; Position: %d, %d\n", i, zombieSpawn[i].x, zombieSpawn[i].y);
    }
    logv("\n");

    logv("SHOP POINTS");
    for(int i = 0; i < shopCount; i++) {
        logv("Shop: %d; Position: %d, %d\n", i, shops[i].x, shops[i].y);
    }

    logv("AI MAP");
    for (const auto& i : AIMap) {
        for (const auto& j : i) {
            logv("%d", j);
        }
        logv("\n");
    }
    logv("\n");

    logv("WALL DATA\n");
    for (const auto& wall : walls) {
        logv("Position: %d, %d;\t\t width = %d, height = %d\n", wall.x / T_SIZE,
                wall.y / T_SIZE, wall.width / T_SIZE, wall.height / T_SIZE);
    }
}

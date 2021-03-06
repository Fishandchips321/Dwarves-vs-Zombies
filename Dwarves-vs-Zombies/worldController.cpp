#include "worldController.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/thread.hpp>
#include <boost/foreach.hpp>
#include <string>
#include "netController.h"
#include "tileController.h"
#include "blockController.h"
#include "eventController.h"

using boost::property_tree::ptree;

worldController::worldController()
{
}

bool worldController::loadMap(std::string map)
{
	ptree tree;

	try
	{
		read_xml(map, tree);

		metadata.version = tree.get<std::string>("header.version"); //read the mapfile version

		BOOST_FOREACH(ptree::value_type const& v, tree.get_child("world")) //iterate through each child node of the "world" node
		{
			if (v.first == "tile") //if a tile is found
			{
				tile* nTile = tileController::getTile(v.second.get("<xmlattr>.ID", 0)); //get the tile ID <tile ID=x>
				placedTile pTile; //create a tile container
				pTile.tile = nTile; //assign the tile pointer
				pTile.x = v.second.get("<xmlattr>.x", 0); //get the x coordinate
				pTile.y = v.second.get("<xmlattr>.y", 0); //get the y coordinate

				pTile.metadata.metadata = v.second.get("metadata", 0);//get the metadata

				tiles.push_back(pTile);//add the tile container to the vector
			}

			if (v.first == "block")
			{
				block* nBlock = blockController::getBlock(v.second.get("<xmlattr>.ID", 0)); //get the block ID <block ID=x>
				placedBlock pBlock; //create a tile container
				pBlock.block = nBlock; //assign the block pointer
				pBlock.x = v.second.get("<xmlattr>.x", 0); //get the x coordinate
				pBlock.y = v.second.get("<xmlattr>.y", 0);//get the y coordinate

				pBlock.metadata.metadata = v.second.get("metadata.<xmlattr>.metadata", 0); //get the metadata (default 0)
				pBlock.metadata.placerID = -1;//set the placer ID to the loader's ID (-1 to say that it was loaded and not placed by anyone)

				blocks.push_back(pBlock);//add the block to the vector
			}
		}
	}
	catch (std::exception &e) //an exception is thrown if the file can't be found or if an attribute can't be found
	{
		std::cout << "[ERROR]: Couldn't load map \"" << map << "\" error: " << e.what() << std::endl;
		return false;
	}


	return true;
}

bool worldController::loadMap(int map)
{
	if (map < maxMaps) //error checking
	{
		loadMap(mapPaths[map]);
	}
	return false;
}

void worldController::update()
{
	//update all tiles and blocks in two seperate threads
	boost::thread tileThread(boost::bind(&worldController::updateTiles, this));
	boost::thread blockThread(boost::bind(&worldController::updateTiles, this));
	//wait for both threads to finish before returning
	tileThread.join();
	blockThread.join();
}

void worldController::controlNetUpdate()
{
	if (netController::currentControlMessage.NCM == netController::LOAD_MAP) //if the server wants the clients to load the map
	{
		//get the map ID
		std::string map = netController::currentControlMessage.paramaters;
		map.erase(map.begin(), map.begin() + 9);
		
		netController::send(std::to_string(netController::LOAD_MAP)); //tell the server that the client is loading the map
		SDL_Event e; //event 
		SDL_memset(&e, 0, sizeof(e));

		if (loadMap(std::stoi(map)))//if the map was loaded, tell the server
		{
			netController::sendControl(std::to_string(netController::MAP_LOADED));
			
			e.type = eventController::mapLoaded;
		}
		else // if there was an error loading the map, tell the server
		{
			netController::sendControl(std::to_string(netController::MAP_LOAD_ERROR));

			e.type = eventController::mapLoadError;
		}

		SDL_PushEvent(&e);
	}
}

void worldController::draw()
{
	drawTiles();
	drawBlocks();
}

void worldController::updateTiles()
{
	for (size_t x = 0; x < tiles.size(); x++) //iterate through all tiles and call the update method with the x and y coordinates
	{
		tiles[x].tile->update(tiles[x].x, tiles[x].y);
	}
}

void worldController::updateBlocks()
{
	for (size_t x = 0; x < blocks.size(); x++) //iterate through all blocks and call the update method with the x and y coordinates
	{
		blocks[x].block->update(blocks[x].x, blocks[x].y);
	}
}

void worldController::drawTiles()
{
	for (size_t x = 0; x < tiles.size(); x++) //iterate through all tiles and call the draw method with the x and y coordinates
	{
		tiles[x].tile->draw(tiles[x].x, tiles[x].y);
	}
}

void worldController::drawBlocks()
{
	for (size_t x = 0; x < blocks.size(); x++) //iterate through all blocks and call the draw method with the x and y coordinates
	{
		blocks[x].block->draw(blocks[x].x, blocks[x].y);
	}
}

worldController::~worldController()
{
}

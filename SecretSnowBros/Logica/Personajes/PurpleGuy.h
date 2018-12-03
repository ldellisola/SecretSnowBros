#pragma once
#include "Monster.h"
#include<cstdlib>
#include<ctime>
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <limits> // for numeric_limits
#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>
#include "../juego/Cmap.h"
typedef int vertex_t;
typedef double weight_t;

const weight_t max_weight = std::numeric_limits<double>::infinity();

struct neighbor { //clase nodo.
	vertex_t target;
	weight_t weight;
	neighbor(vertex_t arg_target, weight_t arg_weight)
		: target(arg_target), weight(arg_weight) { }
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;


/*este irá hacia el jugador mas cercano(con probabilidad 0.6), se moverá
hacia una dirección aleatoria(probabilidad 0.3) o se quedará quieto
por 0.3s(probabilidad 0.1).
*/
//	/		Night man		/	//
class PurpleGuy :
	public Monster 
{
public:
	PurpleGuy(uint32_t x, uint32_t y, uint32_t ID = 0);
	virtual ~PurpleGuy(){}
	void chooseAction(void *);
	void next( World& map);//Define la proxima accion
	void chase(World &map_);
private:
	adjacency_list_t adjacency_list;
	void makegraph(World map, adjacency_list_t& adjacency_list);
	std::list<vertex_t> DijkstraGetShortestPathTo(vertex_t vertex, const std::vector<vertex_t> &previous);
	void DijkstraComputePaths(vertex_t source, const adjacency_list_t &adjacency_list, std::vector<weight_t> &min_distance, std::vector<vertex_t> &previous);
	uint16_t xTarget, yTarget;
};


#include "PurpleGuy.h"
#include <exception>

#define ms50 (3)

#define JumpTicks (ms50* 24)	// 1200ms
#define WalkTicks (ms50*6)	// 300ms
//#define WalkTicks (17)	// 270ms

#define FallTick (ms50*6)	// 300ms
#define StillTicks (ms50*6)	// 300ms

#define PointsAwarded (10)

PurpleGuy::PurpleGuy(uint32_t x, uint32_t y, uint32_t ID)
	:Monster(JumpTicks, WalkTicks, StillTicks, FallTick, x, y, ID, PointsAwarded)//Mirar negrada del año
{
	this->adjacency_list.reserve(12 * 16);
	this->lives = 1;
}
void PurpleGuy::chooseAction(void * mapWithPj) {
	World * map = (World*)mapWithPj;
	if (this->futureDirections.size() == 0) {
		next(*map);
	}
}

void PurpleGuy::next(World&  map) {
	uint16_t probs = rand() % 100;
	//uint16_t probs = 30;
	if (probs < 60)
		chase(map);
	else if (probs < 70) {
		futureDirections.push(BeingState::WalkingLeft);
		futureDirections.push(BeingState::StillWalk);
	}
	else if (probs < 80) {
		futureDirections.push(BeingState::WalkingRight);
		futureDirections.push(BeingState::StillWalk);
	}
	else if (probs < 90) {
		futureDirections.push(BeingState::Jumping);
		futureDirections.push(BeingState::StillJump);
	}
	else {
		futureDirections.push(BeingState::Waiting);
	}
}

void PurpleGuy::chase(World&  map_) {
		adjacency_list_t adjacency_list(12 * 16);
		this->makegraph(map_, adjacency_list);

		std::vector<weight_t> min_distance;
		std::vector<vertex_t> previous;
		int source = (this->getY()* (map_).columna + this->getX());
		int distance = 0xFFFF;
		int xdes, ydes;
		for (int i = 0; i < map_.x.size(); i++) {
			int temp = (int)sqrt(pow(this->getX() - map_.x[i], 2) + pow(this->getY() - map_.y[i], 2));
			if (distance > temp) {
				distance = temp;//Se fija cual esta mas cerca del monstruo
				xdes = map_.x[i];
				ydes = map_.y[i];
			}
		}

		int destiny = ydes * map_.columna + xdes; //Esto deberia ser la coordenada de un jugador
		DijkstraComputePaths(source, adjacency_list, min_distance, previous);
		std::list<vertex_t> path_ = DijkstraGetShortestPathTo(destiny, previous);
		std::vector<vertex_t> path;
		path_.reverse();
		if (path_.size() > 0) {
			for (int i = 0; i < path_.size(); i) {
				path.push_back(path_.back());
				path_.pop_back();
			}
			for (int i = 0; i < (path.size() - 1); i++) {
				if (path[i] - path[i + 1] == 1) {//uno para atras se movio
					this->futureDirections.push(BeingState::WalkingLeft);
					this->futureDirections.push(BeingState::StillWalk);
				}
				else if (path[i] - path[i + 1] == -1) {
					this->futureDirections.push(BeingState::WalkingRight);
					this->futureDirections.push(BeingState::StillWalk);
				}
				else if (path[i] - path[i + 1] == 16) {

					this->futureDirections.push(BeingState::Jumping);

					if (((i + 2) < path.size()) && ((path[i] - path[i + 2]) == 32)) {
						path.erase(path.begin() + i + 1);
						if (((i + 2) < path.size()) && path[i + 1] - path[i + 2] == 1) {//uno para atras se movio
							this->futureDirections.push(BeingState::WalkingLeft);
							this->futureDirections.push(BeingState::StillWalk);
							path.erase(path.begin() + i + 1);
						}
						else if (((i + 2) < path.size()) && path[i + 1] - path[i + 2] == -1) {
							this->futureDirections.push(BeingState::WalkingRight);
							this->futureDirections.push(BeingState::StillWalk);
							path.erase(path.begin() + i + 1);
						}
					}
					this->futureDirections.push(BeingState::StillJump);
				}
				else if (path[i] - path[i + 1] == -16) {
					this->futureDirections.push(BeingState::StillJump);
					this->futureDirections.push(BeingState::StillWalk);
				}
			}
		}
}




void PurpleGuy::DijkstraComputePaths(vertex_t source,
	const adjacency_list_t &adjacency_list,
	std::vector<weight_t> &min_distance,
	std::vector<vertex_t> &previous)
{
	int n = (int)adjacency_list.size();
	min_distance.clear();
	min_distance.resize(n, max_weight);
	min_distance[source] = 0;
	previous.clear();
	previous.resize(n, -1);
	std::set<std::pair<weight_t, vertex_t> > vertex_queue;
	vertex_queue.insert(std::make_pair(min_distance[source], source));

	while (!vertex_queue.empty())
	{
		weight_t dist = vertex_queue.begin()->first;
		vertex_t u = vertex_queue.begin()->second;
		vertex_queue.erase(vertex_queue.begin());

		// Visit each edge exiting u
		const std::vector<neighbor> &neighbors = adjacency_list[u];
		for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
			neighbor_iter != neighbors.end();
			neighbor_iter++)
		{
			vertex_t v = neighbor_iter->target;
			weight_t weight = neighbor_iter->weight;
			weight_t distance_through_u = dist + weight;
			if (distance_through_u < min_distance[v]) {
				vertex_queue.erase(std::make_pair(min_distance[v], v));

				min_distance[v] = distance_through_u;
				previous[v] = u;
				vertex_queue.insert(std::make_pair(min_distance[v], v));

			}

		}
	}
}


std::list<vertex_t> PurpleGuy::DijkstraGetShortestPathTo(
	vertex_t vertex, const std::vector<vertex_t> &previous)
{
	std::list<vertex_t> path;
	for (; vertex != -1; vertex = previous[vertex])
		path.push_front(vertex);
	return path;
}

void PurpleGuy::makegraph(World map, adjacency_list_t& adjacency_list) {
	/*
	Casos:
	-Si hay dos arriba, peso para arriba infinito, uno solo, 1
	-Si estoy en el aire y dos para abajo no hay piso, distancia par arriba infinito.
	-Si estoy en un bloque y arriba es piso, distancia infinito
	Si el de abajo es aire y arriba es piso entonces infinito arriba
	*/
	for (int i = 1; i < (map.fila - 1); i++) {
		for (int j = 1; j <= (map.columna - 1); j++) {
			if (map.map[i][j] == 'E') {//Si estoy en aire
				if (((map.map[i - 1][j] == 'F') && (((i - 2) <= 0) || (map.map[i - 2][j] == 'F') || (map.map[i + 1][j] == 'E'))) || (((i + 2) < map.fila) && (map.map[i + 2][j] == 'E') && (map.map[i + 1][j] == 'E'))) { //Y el de arriba es la primer fila o dos arriba hay piso, O tambien que dos abajo haya piso

					adjacency_list[((i)*map.columna) + j].push_back(neighbor(((i - 1)*map.columna) + j, max_weight));//maximo peso
				}
				else { //Si 2 arriba esta libre peso 1 O que el de arriba sea aire
					adjacency_list[((i)*map.columna) + j].push_back(neighbor(((i - 1)*map.columna) + j, 1));//peso 1
				}
				//Me tengo que fijar si a la derecha hay piso o aire, izquierda y si abajo es piso inf aire 1
				if (map.map[i + 1][j] == 'E') { //abajo
					adjacency_list[((i)*map.columna) + j].push_back(neighbor(((i + 1)*map.columna) + j, 1));//peso 1
				}
				else {
					adjacency_list[((i)*map.columna) + j].push_back(neighbor(((i + 1)*map.columna) + j, max_weight));//maximo peso
				}
				if (map.map[i][j + 1] == 'E' && (map.map[i + 1][j] == 'F' || map.map[i + 1][j + 1] == 'F')) { //derecha y abajo es piso o derecha diagonal abajo es piso
					adjacency_list[((i)*map.columna) + j].push_back(neighbor(((i)*map.columna) + j + 1, 1));//peso 1
				}
				else if (map.map[i][j + 1] == 'E' && map.map[i + 1][j] == 'E') {
					adjacency_list[((i)*map.columna) + j].push_back(neighbor(((i)*map.columna) + j + 1, 2));
				}
				else {
					adjacency_list[((i)*map.columna) + j].push_back(neighbor(((i)*map.columna) + j + 1, max_weight));//maximo peso
				}
				if (map.map[i][j - 1] == 'E' && (map.map[i + 1][j] == 'F' || map.map[i + 1][j - 1] == 'F')) { //izquierda
					adjacency_list[((i)*map.columna) + j].push_back(neighbor(((i)*map.columna) + j - 1, 1));//peso 1
				}
				else if (map.map[i][j - 1] == 'E' && map.map[i + 1][j] == 'E') { //izquierda
					adjacency_list[((i)*map.columna) + j].push_back(neighbor(((i)*map.columna) + j - 1, 2));//peso 1
				}
				else {
					adjacency_list[((i)*map.columna) + j].push_back(neighbor(((i)*map.columna) + j - 1, max_weight));//maximo peso
				}
			}
			else if (map.map[i][j] == 'F') {
				//Siempre que este en piso ir para abajo, izq o derecha es peso infinito
				adjacency_list[((i)*map.columna) + j].push_back(neighbor(((i)*map.columna) + j + 1, max_weight));//maximo peso  //derecha
				adjacency_list[((i)*map.columna) + j].push_back(neighbor(((i + 1)*map.columna) + j, max_weight));//maximo peso//abajo
				adjacency_list[((i)*map.columna) + j].push_back(neighbor(((i)*map.columna) + j - 1, max_weight));//maximo peso//izquierda
				if (map.map[i - 1][j] == 'E') {

					adjacency_list[((i)*map.columna) + j].push_back(neighbor(((i - 1)*map.columna) + j, 1));//maximo peso //arriba
				}
				else {

					adjacency_list[((i)*map.columna) + j].push_back(neighbor(((i - 1)*map.columna) + j, max_weight));//maximo peso
				}
			}
		}
	}
}
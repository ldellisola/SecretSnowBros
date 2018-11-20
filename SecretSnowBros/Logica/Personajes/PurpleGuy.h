#pragma once
#include "Monster.h"
#include <utility>
#include <list>
#include<cstdlib>
#include<ctime>
/*este irá hacia el jugador mas cercano(con probabilidad 0.6), se moverá
hacia una dirección aleatoria(probabilidad 0.3) o se quedará quieto
por 0.3s(probabilidad 0.1).
*/
#define WaitingTimePG 4 //numero de ticks que tarda 
//	/		GORDO ROSA		/	//
class Nodes {
public:
	uint16_t	sourceX;
	uint16_t	destinyX;
	uint16_t	sourceY;
	uint16_t	destinyY;
	uint16_t	weight;

};
class PurpleGuy :
	public Monster 
{
public:
	PurpleGuy(uint32_t x, uint32_t y, uint32_t ID = 0);
	virtual ~PurpleGuy(){}
	void next();//Define la proxima accion
	void chase(World map_); //Implementar algoritmo de Dijkstra para que lo persiga
	void startWait(); //Lo pone en modo diablo
	void freeWait();//Lo libera
	void findPlayer(void *);
private:
	
	void makeList(World map_); //arma la lista para el algoritmo de dijkstra  
	void getPath();//lo aplica
	uint16_t tickWaitStart;
	//CGAction doing;
	BeingState  currentState;
	uint16_t xTarget, yTarget;
	std::vector<std::list<Nodes>> preDijstra; //Cada componente del vector tiene los posibles casilleros a ocupar con sus conexiones y pesos cada una.
	std::vector<Nodes> dijstra; //Y son en este orden la lista que tiene todos los caminos, el par coordenado que dice el primero y el peso
	// siendo el primero las coordendas y luego el peso
};


#include "PurpleGuy.h"


#define Biggest 0xFFFF

#define ms50 (3)

#define JumpTicks (ms50* 24)	// 1200ms
#define WalkTicks (ms50*6)	// 300ms
#define FallTick (ms50*6)	// 300ms
#define StillTicks (ms50*6)	// 300ms

#define PointsAwarded (10)

void PurpleGuy::findPlayer(void *a)
{

}

PurpleGuy::PurpleGuy(uint32_t x, uint32_t y, uint32_t ID )
	:Monster(JumpTicks,WalkTicks,StillTicks,maxFallTicks,x,y,ID, PointsAwarded)
{
	 this->lives = 1; 
	// this->currentState = BeingState::Still; 
	// this->doing = CGAction::Straight; 
}

void PurpleGuy::next() {
	uint16_t probs = rand() % 100;
	//if (probs < 60)	this->doing = CGAction::Chase;
	//else if (probs < 90) this->doing = CGAction::Random;
	//else this->doing = CGAction::Still;
}

void PurpleGuy::chase(World map_) {
	findPlayer(nullptr);
	makeList(map_);
	getPath();

}
void PurpleGuy::startWait() {
	//this->tickWaitStart = this->getTick();
	this->currentState = BeingState::Waiting;
}
void PurpleGuy::freeWait() {
	/*if (this->getTick()> this->tickWaitStart+WaitingTimePG) {
		this->currentState = BeingState::Still;
		this->tickWaitStart = 0;
	}*/
}
void PurpleGuy::makeList(World map_) {
	int iterat = 0;
	Nodes node;
	for (int i = 1; i < (FILS - 1); i++) {
		for (int j = 1; j < (COLS - 1); j++) {
			if (map_.map[i][j] == 'F') {//Miro si estoy parado en cancer.
				{
					if (map_.map[i - 1][j] == 'F') {//Es la pared o el sopi
						node.destinyY = i - 1;
						node.destinyX = j;//la columna
						node.weight = Biggest;
						node.sourceY = i;
						node.sourceX = j;
						this->preDijstra[iterat].push_back(node);//Se me ocurre que capaz el vector deberia empezar lleno con nada
					}
					else {//sino es algo distinto por lo tanto el peso es 1
						node.destinyY = i - 1;
						node.destinyX = j;//la columna
						node.sourceY = i;
						node.sourceX = j;
						node.weight = 1;
						this->preDijstra[iterat].push_back(node);
					}
				}
				//Miro para arriba
				{
					if (map_.map[i + 1][j] == 'F') {//Es la pared o el sopi
						node.destinyY = i + 1;
						node.destinyX = j;
						node.sourceY = i;
						node.sourceX = j;
						node.weight = Biggest;
						this->preDijstra[iterat].push_back(node);
					}
					else {//sino es algo distinto por lo tanto el peso es 1
						node.destinyY = i + 1;
						node.destinyX = j;
						node.sourceY = i;
						node.sourceX = j;
						node.weight = 1;
						this->preDijstra[iterat].push_back(node);
					}
				}
				//abajo
				{
					if (map_.map[i][j - 1] == 'F') {//Es la pared o el sopi
						node.destinyY = i;
						node.destinyX = j-1;
						node.sourceY = i;
						node.sourceX = j;
						node.weight = Biggest;
						this->preDijstra[iterat].push_back(node);
					}
					else {//sino es algo distinto por lo tanto el peso es 1
						node.destinyY = i;
						node.destinyX = j-1;
						node.sourceY = i;
						node.sourceX = j;
						node.weight = 1;
						this->preDijstra[iterat].push_back(node);
					}
				}
				//izquierda
				{
					if (map_.map[i][j + 1] == 'F') {//Es la pared o el sopi
						node.destinyY = i;
						node.destinyX = j+1;
						node.sourceY = i;
						node.sourceX = j;
						node.weight = Biggest;
						this->preDijstra[iterat].push_back(node);
					}
					else {//sino es algo distinto por lo tanto el peso es 1

						node.destinyY = i;
						node.destinyX = j+1;
						node.sourceY = i;
						node.sourceX = j;
						node.weight = 1;
						this->preDijstra[iterat].push_back(node);
					}
				}
				//derecha
			}
			iterat++;
		}
	}
}


void PurpleGuy::getPath() {

	for (int i = 0; i < this->preDijstra.size(); i++) {

	}

	for (int i = 0; i < this->preDijstra.size(); i++) {//Tengo que asignar pesos hasta recorrer todo el vector. //TENIENDO DE REFERENCIA A MIS COORDENADAS.
		for (int j = 0; j < this->preDijstra[i].size(); j++) {
			//en el primero es el primer casillero y asi hasta el final.
//Tiene que mostrar tambien de donde vino.


		}
	}
}
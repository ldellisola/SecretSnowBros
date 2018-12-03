#pragma once
#include "Observer.h"
#include "AllwUI/WrittenBox.h"
#include "AllwBasics/AllegroFont.h"
#include <cstdint>
#include "Logica/Personajes/Score.h"
class ScoreObserver :
	public Observer
{
public:
//	//ScoreObserver() :font("Resources\Fonts\font.ttf"), wbox(,) {}; //DEBUG
//	void draw(void * sc) {//Estos numero claramente van a ser cambiados.
//		this->wbox.setText(std::to_string(((Score *)sc)->getActualScore()));
//		this->wbox.draw();
//		//AllegroWrittenBox score((float) ((Score *)sc)->getXCoord(), (float)((Score *)sc)->getYCoord(), 300, 100, std::to_string(((Score *)sc)->getActualScore()), &alfont, al_map_rgb(0, 0, 0), 0);
//	}
	~ScoreObserver(){}
//private:
//	AllegroFont font;
//	AllegroWrittenBox wbox;
};


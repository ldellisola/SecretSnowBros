#pragma once
#define COLS 16
#define FILS 12
#include <cstdint>
#include <string>
#include <fstream>
#include <vector>



struct World {
public:
	World(std::string file_) {

		std::fstream file;
		file.open(file_, std::ifstream::in);

		std::vector<std::string> temp;

		while (!file.eof()) {
			std::string tt = "";
			file >> tt;
			temp.push_back(tt);
		}
		file.close();


		for (int fil = 0; fil < FILS; fil++) {
			std::string filas = temp[fil];
			for (int col = 0; col < COLS; col++) {
				std::string a = filas.substr(0,filas.find_first_of(','));

				map[fil][col] = a[0];

				filas = filas.substr(filas.find_first_of(',')+1);
			}
		}
		
	}

	void purge() {
		isPurged = true;
		for (int fil = 0; fil < FILS; fil++) {
			for (int col = 0; col < COLS; col++) {
				if (map[fil][col] != 'F' && map[fil][col] != 'E') {
					map[fil][col] = 'E';
				}
			}
		}
	}

	char map[FILS][COLS];
	bool isPurged = false;
	uint16_t const fila = FILS;
	uint16_t const columna = COLS;
};
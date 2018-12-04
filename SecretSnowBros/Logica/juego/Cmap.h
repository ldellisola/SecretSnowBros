#pragma once
#define COLS 16
#define FILS 12
#include <cstdint>
#include <string>
#include <fstream>
#include <vector>



struct World { //Basic structure in wich the world is build.
public:
	// It loads a map from a csv file and it transforms it to a matrix
	World(std::string file_) {
		std::fstream file;
		file.open(file_, std::ifstream::in);

		std::vector<std::string> temp;

		// Reads the file
		while (!file.eof()) {
			std::string tt = "";
			file >> tt;
			temp.push_back(tt);
		}
		file.close();

		// Transforms it to a matrix
		for (int fil = 0; fil < FILS; fil++) {
			std::string filas = temp[fil];
			for (int col = 0; col < COLS; col++) {
				std::string a = filas.substr(0,filas.find_first_of(','));

				map[fil][col] = toupper(a[0]);	

				filas = filas.substr(filas.find_first_of(',')+1);
			}
		}
	}

	// It cleans the map from players and enemies so that there is only Empyt('E') and Wall('F')
	void purge() {
		isPurged = true;
		for (int fil = 0; fil < FILS; fil++) 
			for (int col = 0; col < COLS; col++) 
				if (map[fil][col] != 'F' && map[fil][col] != 'E') 
					map[fil][col] = 'E';

	}

	char map[FILS][COLS];
	bool isPurged = false;
	uint16_t const fila = FILS;
	uint16_t const columna = COLS;
	std::vector<uint16_t> x;
	std::vector<uint16_t>y;
};
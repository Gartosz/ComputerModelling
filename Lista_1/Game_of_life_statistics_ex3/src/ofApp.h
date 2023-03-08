#pragma once

#include "ofMain.h"
#include <vector>
#include <glm/gtc/random.hpp>
#include <fstream>
#include <algorithm>
#include <chrono>

class ofApp : public ofBaseApp{

	public:
		ofApp(int grid_length = 10, float alive_probability = 0.2f, size_t _n = 100)
		{
			ofSetVerticalSync(false);
			probability = alive_probability;
			n = _n;
			start_dimensions = {ofGetHeight(), ofGetWidth()};
			size = start_dimensions.first / grid_length;
			for (int y = 0; y < grid_length; ++y)
			{
				cells_matrix.push_back(std::vector<bool>{});
				for (int x = 0; x < grid_length; ++x)
					cells_matrix[y].push_back(ofRandom(1.0) < alive_probability ? true : false);
			}
			saved_generation = cells_matrix;
		}
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void update_cells();
		void insert_cell(int y, int x);
		void reset();
		void save_iteration();
		void update_grid_size();
		void reload_grid();
		char* get_current_time();
		void open_file();

	private:
		int size = 6;
		std::vector<std::vector<bool>> cells_matrix{};
		std::vector<std::vector<bool>> saved_generation{};
		std::vector<std::pair<int, int>> pos_to_check = {{-1, -1}, {-1, -0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
		bool paused = true;
		int frames = 0;
		size_t iteration = 0;
		int alive = 0;
		std::vector<int> grids{10, 100, 200, 500, 1000};
		std::vector<int>::iterator current = grids.begin();
		std::ofstream file;
		std::pair<size_t, size_t> start_dimensions{0, 0};
		size_t n = 0;
		float probability = 0;
		size_t max_frame = 1000;
};

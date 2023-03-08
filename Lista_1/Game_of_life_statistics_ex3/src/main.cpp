#include "ofMain.h"
#include "ofApp.h"
#include <filesystem>

double calculate_standard_error(std::vector<double> density_vector)
{
	double mean = std::reduce(density_vector.begin(), density_vector.end()) / density_vector.size();
	double std_deviation = 0;
	for(auto &density : density_vector)
		std_deviation += (density - mean) * (density - mean);
	std_deviation = sqrt(std_deviation/density_vector.size());
	return std_deviation/sqrt(density_vector.size());
}

double process_file_content(std::string file_name, size_t iterations_number)
{
	std::ifstream file(file_name);
	std::string date_time;
	std::getline(file, date_time);
	int n;
	double line_density;
	std::vector<double> density_vector{};
	for (int i = 0; i < iterations_number; ++i)
	{
		file >> n >> line_density;
		density_vector.push_back(line_density);
	}
	file.close();
	return calculate_standard_error(density_vector);
}

void process_files(size_t iterations_number)
{
	std::string dir = "data/";
	std::ofstream result_file("data/standard_error.txt");
	result_file << "size\tstandard error\n";
	for(auto& p: filesystem::directory_iterator(dir))
	{
		std::string file_name = p.path().filename().string();
		if ( file_name.find("size") == 0 )
		{
			std::string size = file_name.substr(file_name.find('_') + 1, file_name.find('.txt') - file_name.find('_') - 2);
			result_file << size.erase(0, size.find_first_not_of('0')) << "\t";
			result_file << process_file_content(dir + file_name, iterations_number) << std::endl;
		}
	}
	result_file.close();
}

//========================================================================
int main( )
{
	size_t iterations_number = 100;
	// Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(900, 900);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN
	
	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp>(10, 0.55, iterations_number));
	ofRunMainLoop();
	process_files(iterations_number);
	return 0;
}

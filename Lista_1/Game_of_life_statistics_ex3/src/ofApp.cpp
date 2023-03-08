#include "ofApp.h"
#include <algorithm>
#include <string>

#define KEY_SPACE 32

//--------------------------------------------------------------
void ofApp::setup()
{
    std::sort(grids.begin(), grids.end());
    open_file();
    paused = false;
    file << get_current_time();
    ofLog() << "grid size: " << *current;
}

void ofApp::open_file()
{
    std::string current_grid = to_string(*current);
    file.open("data/size_" + std::string(to_string(grids.back()).length() - current_grid.length(), '0') + current_grid + ".txt");
}

char* ofApp::get_current_time()
{
    std::time_t start_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    return std::ctime(&start_time);
}

void ofApp::update_cells()
{
    for (int col = 0; col < saved_generation.size(); ++col)
    {
        for (int row = 0; row < saved_generation[col].size(); ++row)
        {
            int neighbours = 0;
            for (auto &pos : pos_to_check)
                if (col + pos.first > 0 && col + pos.first < saved_generation.size() && row + pos.second > 0 && row + pos.second < saved_generation[col].size())
                    if (saved_generation[col + pos.first][row + pos.second])
                        ++neighbours;
            if (saved_generation[col][row])
            {
                ++alive;
                cells_matrix[col][row] = !(neighbours < 2 || neighbours > 3);
            }

            else if (neighbours == 3)
                cells_matrix[col][row] = true;
        }
    }
    saved_generation = cells_matrix;
    ++frames;
}

void ofApp::update_grid_size()
{
    file << get_current_time();
    file.close();
    if (++current == grids.end())
    {
        ofExit();
        return;
    }
    ofLog() << "grid size: " << *current;
    cells_matrix.resize(*current);
    for (auto &row : cells_matrix)
        row.resize(*current);
    open_file();
    file << get_current_time();
    size = start_dimensions.first / *current;
    reset();
    iteration = 0;
}

void ofApp::reload_grid()
{   
    save_iteration();
    reset();
    frames = 0;
    ++iteration;
}

//--------------------------------------------------------------
void ofApp::update()
{
    if (!paused)
        update_cells();

    if (iteration >= n)
        update_grid_size();

    else if(frames >= max_frame)
        reload_grid();

    alive = 0;
}

//--------------------------------------------------------------
void ofApp::draw()
{
    for (int row = 0; row < cells_matrix.size(); ++row)
        for (int col = 0; col < cells_matrix[row].size(); ++col)
            if (cells_matrix[row][col])
                ofDrawRectangle(col * size, row * size, size, size);
}

void ofApp::reset()
{
    for (auto &row : cells_matrix)
        for (auto col : row)
            col = ofRandom(1.0) < probability ? true : false;
    saved_generation = cells_matrix;
}

void ofApp::save_iteration()
{
    file << iteration << " " << 1.0 * alive / (*current * *current) << std::endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == KEY_SPACE)
        paused = !paused;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

void ofApp::insert_cell(int y, int x)
{
    x /= size;
    y /= size;
    if (y > 0 && y < cells_matrix.size() && x > 0 && x < cells_matrix[0].size())
        cells_matrix[y][x] = true;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    insert_cell(y, x);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    insert_cell(y, x);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}

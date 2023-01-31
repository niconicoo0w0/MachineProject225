/* Your code here! */
#include "maze.h"
using namespace std;
#include <iostream>

SquareMaze::SquareMaze() {}

void SquareMaze::makeMaze (int width, int height) {
    if (width <= 0 || height <= 0) {
        return;
    }
    width_ = width;
    height_ = height;
    down_wall_.resize(height);
    right_wall_.resize(height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            down_wall_[y].push_back(1);
            right_wall_[y].push_back(1);
        }
    }

    int dim = height*width;
    DisjointSets dset_;
    dset_.addelements(dim);

    int count = 0;
    while (count + 1 < dim) {
        int x = rand() % width;
        int y = rand() % height;
        int dir = rand() % 2;
        int current = dset_.find(x + y * width);

        if (dir == 1) {
            if (x + 1 < width) {
                int next = dset_.find((x+1) + y * width);
                if (right_wall_[y][x] == 1) {
                    if (current != next) {
                        right_wall_[y][x] = 0;
                        dset_.setunion(dset_.find(current), dset_.find(next));
                        count++;
                    }
                }
            }
        }

        if (dir == 0) {
            if (y + 1 < height) {
                int next = dset_.find(x + (y+1) * width);
                if (down_wall_[y][x] == 1) {
                    if (current != next) {
                        down_wall_[y][x] = 0;
                        dset_.setunion(dset_.find(current), dset_.find(next));
                        count++;
                    }
                }
            }
        }
    }
    return;
}

bool SquareMaze::canTravel (int x, int y, int dir) const {
    // check bound
    if (x < 0 || y < 0) {
        return false;
    }
    if (x >= width_ || y >= height_) {
        return false;
    }
    // dir = 0 represents a rightward step (+1 to the x coordinate)
    if (dir == 0) {
        if (x + 1 < width_ && right_wall_[y][x] == 0) { 
            return true;
        }
        return false;
    }
    // dir = 1 represents a downward step (+1 to the y coordinate)
    if (dir == 1) {
        if (y + 1 < height_ && down_wall_[y][x] == 0) {
            return true;
        }
        return false;
    }
    // dir = 2 represents a leftward step (-1 to the x coordinate)
    if (dir == 2) {
        if (x > 0 && right_wall_[y][x-1] == 0) {
            return true;
        }
        return false;
    }
    // dir = 3 represents an upward step (-1 to the y coordinate)
    if (dir == 3) {
        if (y > 0 && down_wall_[y-1][x] == 0) {
            return true;
        }
        return false;
    }
    return false;
}

void SquareMaze::setWall (int x, int y, int dir, bool exists) {
    if (x < 0 || y < 0) {
        return;
    }
    if (x >= width_ || y >= height_) {
        return;
    }
    int i = 0;
    if (exists) {
        i = 1;
    }
    if (dir == 0) {
        right_wall_[y][x] = i;
    }
    if (dir == 1) {
        down_wall_[y][x] = i;
    }
    return;
}

vector<int> SquareMaze::solveMaze () {
    vector<int> returnit;
    if (width_ <= 0 || height_<= 0) {
        return returnit;
    }
    
    vector<int> prev;
    vector<int> length;
    vector<bool> visited;
    vector<int> dir;
    for (int i = 0; i < width_*height_; i++) {
        prev.push_back(0);
        length.push_back(0);
        visited.push_back(false);
        dir.push_back(-1);
    }

    vector<int> offsets = {1, width_, -1, (-1)*width_};
    queue<int> que;

    que.push(0);
    visited[0] = true;

    int curr;
    while (que.empty() == false) {
        curr = que.front();
        int x = curr % width_;
        int y = curr / width_;
        for (int i = 0; i < 4; i++) {
            int offset = offsets[i];
            int next_idx = offset + curr;
            if (canTravel(x, y, i) && !visited[next_idx]) {
                visited[next_idx] = true;
                que.push(next_idx);
                prev[next_idx] = curr;
                length[next_idx] = length[curr] + 1;
                dir[next_idx] = i;
            }
        }
        que.pop();
    }

    int max = -1;
    int max_idx = 0;
    for (int i = (height_-1)*width_; i < width_*height_; i++) {
        if (length[i] > max) {
            max = length[i];
            max_idx = i;
        }
    }

    while (max_idx > 0) {
        returnit.push_back(dir[max_idx]);
        max_idx = prev[max_idx];
    }

    vector<int> result;
    for (int i = returnit.size()-1; i >= 0; i--) {
        result.push_back(returnit[i]);
    }
    return result;
}

PNG* SquareMaze::drawMaze () const {
    PNG* returnit = new PNG(width_*10+1, height_*10+1);
    for (unsigned i = 0; i < returnit->width(); i++) {
        if (i>=1 && i<=9) {
            continue;           // except(0,9)
        }
        HSLAPixel & pixel = returnit->getPixel(i,0);
        pixel = blacken(pixel);
    }
    for (unsigned j = 0; j < returnit->height(); j++) {
        HSLAPixel & pixel = returnit->getPixel(0,j);
        pixel = blacken(pixel);
    }
    for(int x = 0 ; x < width_ ; x++){
        for(int y = 0 ; y < height_ ; y++){
            if (right_wall_[y][x] == 1) {
                for (int i = 0 ; i < 11 ; i++){
                    HSLAPixel& pixel = returnit->getPixel((x+1)*10,y*10+i);
                    pixel = blacken(pixel);
                }
            }
            if (down_wall_[y][x] == 1) {
                for(int j = 0 ; j < 11 ; j++){
                    HSLAPixel& pixel = returnit->getPixel(x*10+j, (y+1)*10);
                    pixel = blacken(pixel);
                }
            }
        }
    }
    return returnit;
}

HSLAPixel& SquareMaze::blacken (HSLAPixel& pixel) const {
    pixel.h = 0;
    pixel.s = 0;
    pixel.l = 0;
    return pixel;
}

HSLAPixel& SquareMaze::red (HSLAPixel& pixel) const {
    pixel.h = 0;
    pixel.s = 1;
    pixel.l = 0.5;
    pixel.a = 1;
    return pixel;
}


PNG* SquareMaze::drawMazeWithSolution () {
    PNG* returnit = drawMaze();
    vector<int> dirs = solveMaze();

    // Start at pixel (5,5)
    int x = 5;
    int y = 5;

    for (auto dir : dirs) {
        if (dir == 0) {
            for (int i = 0 ; i < 10 ; i++) {
                HSLAPixel& pixel = returnit->getPixel(x,y);
                pixel = red(pixel);
                x++;
            }
        }
        if (dir == 1) {
            for(int i = 0 ; i < 10 ; i++){
                HSLAPixel& pixel = returnit->getPixel(x,y);
                pixel = red(pixel);
                y++;
            }
        }
        if (dir == 2) {
            for(int i = 0 ; i < 10 ; i++){
                HSLAPixel& pixel = returnit->getPixel(x,y);
                pixel = red(pixel);
                x--;
            }
        }
        if (dir == 3) {
            for(int i = 0 ; i < 10 ; i++){
                HSLAPixel& pixel = returnit->getPixel(x,y);
                pixel = red(pixel);
                y--;
            }
        }
    }
    HSLAPixel& pixel = returnit->getPixel(x, y);
    pixel = red(pixel);

    //whiten
    x -= 4;
    y += 5;
    for (int i = 0; i < 9; i++) {
        HSLAPixel& pixel = returnit->getPixel(x + i, y);
        pixel.l = 1;
    }
    return returnit;
}
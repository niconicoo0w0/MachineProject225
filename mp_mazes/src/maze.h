/* Your code here! */
#pragma once
#include <vector>
#include <queue>
#include "dsets.h"
#include "../lib/cs225/PNG.h"
using namespace std;
using namespace cs225;

class SquareMaze {
    public:
        SquareMaze();
        void makeMaze (int width, int height);
        bool canTravel (int x, int y, int dir) const;
        void setWall (int x, int y, int dir, bool exists);
        vector<int> solveMaze ();
        PNG* drawMaze () const;
        PNG* drawMazeWithSolution ();
        HSLAPixel& blacken (HSLAPixel& pixel) const;
        HSLAPixel& red (HSLAPixel& pixel) const;
    private:
        int width_;
        int height_;
        // 1 if detect wall, 0 otherwise
        vector<vector<int>> right_wall_;
        vector<vector<int>> down_wall_;
};
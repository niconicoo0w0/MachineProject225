// #include <catch2/catch_test_macros.hpp>
// #include "maze.h"
// #include <iostream>
// #include <string>

// using std::cout;
// using std::endl;
// using std::string;

// TEST_CASE("testSolutionCorrectSquare", "[weight=10][part2]")
// {
//     SquareMaze maze;
//     MazeReader soln = READ_SOLUTION_MAZE("testSolutionCorrectSquare",15, 15);
//     copyMaze(soln, &maze);
//     PNG* answer=maze.drawMazeWithSolution();
//     answer->writeToFile("answer.png");
//     vector<int> solution = maze.solveMaze();

//     int x = 0;
//     int y = 0;
//     for (size_t i = 0; i < solution.size(); i++)
//         advancePosition(&x, &y, solution[i]);

//     if (y != soln.getDestinationY())
//         FAIL("Didn't end up at the bottom row");
//     if (x != soln.getDestinationX()){
//         cout<<"x:"<<x<<endl;
//         cout<<"expected:"<<soln.getDestinationX()<<endl;
//         FAIL("Didn't end up at the correct bottom-row cell");
//     }
// }
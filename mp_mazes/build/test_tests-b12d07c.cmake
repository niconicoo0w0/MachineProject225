add_test( testMakeSmallMaze [==[/workspaces/CS 225/release-f22-main/mp_mazes/build/test]==] testMakeSmallMaze  )
set_tests_properties( testMakeSmallMaze PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS 225/release-f22-main/mp_mazes/build]==])
add_test( testMakeMazeConnected [==[/workspaces/CS 225/release-f22-main/mp_mazes/build/test]==] testMakeMazeConnected  )
set_tests_properties( testMakeMazeConnected PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS 225/release-f22-main/mp_mazes/build]==])
add_test( testMakeMazeAcyclic [==[/workspaces/CS 225/release-f22-main/mp_mazes/build/test]==] testMakeMazeAcyclic  )
set_tests_properties( testMakeMazeAcyclic PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS 225/release-f22-main/mp_mazes/build]==])
add_test( testMakeMazeTree750 [==[/workspaces/CS 225/release-f22-main/mp_mazes/build/test]==] testMakeMazeTree750  )
set_tests_properties( testMakeMazeTree750 PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS 225/release-f22-main/mp_mazes/build]==])
add_test( testMakeMazeRandom [==[/workspaces/CS 225/release-f22-main/mp_mazes/build/test]==] testMakeMazeRandom  )
set_tests_properties( testMakeMazeRandom PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS 225/release-f22-main/mp_mazes/build]==])
add_test( testSolveMazeValidPath [==[/workspaces/CS 225/release-f22-main/mp_mazes/build/test]==] testSolveMazeValidPath  )
set_tests_properties( testSolveMazeValidPath PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS 225/release-f22-main/mp_mazes/build]==])
add_test( testSolutionBottomRow [==[/workspaces/CS 225/release-f22-main/mp_mazes/build/test]==] testSolutionBottomRow  )
set_tests_properties( testSolutionBottomRow PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS 225/release-f22-main/mp_mazes/build]==])
add_test( testSolutionCorrectSquare [==[/workspaces/CS 225/release-f22-main/mp_mazes/build/test]==] testSolutionCorrectSquare  )
set_tests_properties( testSolutionCorrectSquare PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS 225/release-f22-main/mp_mazes/build]==])
add_test( testSolveMazeSmall [==[/workspaces/CS 225/release-f22-main/mp_mazes/build/test]==] testSolveMazeSmall  )
set_tests_properties( testSolveMazeSmall PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS 225/release-f22-main/mp_mazes/build]==])
add_test( testSolveMazeLarge [==[/workspaces/CS 225/release-f22-main/mp_mazes/build/test]==] testSolveMazeLarge  )
set_tests_properties( testSolveMazeLarge PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS 225/release-f22-main/mp_mazes/build]==])
add_test( testDrawMazeSmall [==[/workspaces/CS 225/release-f22-main/mp_mazes/build/test]==] testDrawMazeSmall  )
set_tests_properties( testDrawMazeSmall PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS 225/release-f22-main/mp_mazes/build]==])
add_test( testDrawMazeMed [==[/workspaces/CS 225/release-f22-main/mp_mazes/build/test]==] testDrawMazeMed  )
set_tests_properties( testDrawMazeMed PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS 225/release-f22-main/mp_mazes/build]==])
add_test( testDrawMazeLarge [==[/workspaces/CS 225/release-f22-main/mp_mazes/build/test]==] testDrawMazeLarge  )
set_tests_properties( testDrawMazeLarge PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS 225/release-f22-main/mp_mazes/build]==])
add_test( testDrawSolutionMed [==[/workspaces/CS 225/release-f22-main/mp_mazes/build/test]==] testDrawSolutionMed  )
set_tests_properties( testDrawSolutionMed PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS 225/release-f22-main/mp_mazes/build]==])
add_test( testDrawSolutionLarge [==[/workspaces/CS 225/release-f22-main/mp_mazes/build/test]==] testDrawSolutionLarge  )
set_tests_properties( testDrawSolutionLarge PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS 225/release-f22-main/mp_mazes/build]==])
set( test_TESTS testMakeSmallMaze testMakeMazeConnected testMakeMazeAcyclic testMakeMazeTree750 testMakeMazeRandom testSolveMazeValidPath testSolutionBottomRow testSolutionCorrectSquare testSolveMazeSmall testSolveMazeLarge testDrawMazeSmall testDrawMazeMed testDrawMazeLarge testDrawSolutionMed testDrawSolutionLarge)
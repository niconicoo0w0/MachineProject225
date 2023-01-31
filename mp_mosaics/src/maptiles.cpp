/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    int row = theSource.getRows();
    int col = theSource.getColumns();

    vector<Point<3>> color(theTiles.size());
    map<Point<3>, unsigned> map;
    // for (auto tile : theTiles) {
    //     color.push_back(convertToXYZ(tile.getAverageColor()));
    // }
    for (unsigned i = 0; i < theTiles.size(); i++) {
        auto temp = convertToXYZ(theTiles[i].getAverageColor());
        color[i] = temp;
        map[temp] = i;
    }

    MosaicCanvas *returnit = new MosaicCanvas(row, col);

    KDTree<3> tree(color);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        Point<3> nearest = tree.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(i, j)));
        unsigned index = map[nearest];
        returnit->setTile(i, j, &theTiles[index]);
      }
    }
    return returnit;
}
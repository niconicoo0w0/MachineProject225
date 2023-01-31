/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>
using namespace std;



class StickerSheet {
    public:
        StickerSheet(const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet &other);
        const StickerSheet& operator=(const StickerSheet &other);
        void changeMaxStickers(unsigned new_max);
        int addSticker(Image &sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image* getSticker(unsigned index);
        Image render() const;

    private:
        Image base_;       //base picture
        vector<Image*> stickers_;   //stickers on the picture

        vector<bool> check_;

        unsigned max_;       //max number of stickers (Images) with indices 0 through max - 1.

        vector<int> xcorr_;    //1d vector contains all x corrdinates
        vector<int> ycorr_;    //1d vector contains all y corrdinates

        unsigned sticker_count_;     //number of stickers
};


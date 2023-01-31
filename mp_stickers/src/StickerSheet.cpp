#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    base_ = picture;
    max_ = max;
    sticker_count_ = 0;
    stickers_ = vector<Image*>(max);
    xcorr_ = vector<int>(max);
    ycorr_ = vector<int>(max);
    check_ = vector<bool>(max);
    for (unsigned int i = 0; i < max; i++) {
        check_[i] = false;
        xcorr_[i] = -1;
        ycorr_[i] = -1;
        stickers_[i] = nullptr;
    }
}

StickerSheet::~StickerSheet() {
    sticker_count_ = 0;
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    if (this == &other) { return;}
    xcorr_ = vector<int>(other.max_);
    ycorr_ = vector<int>(other.max_);
    check_ = vector<bool>(other.max_);
    stickers_ = vector<Image*>(other.max_);
    base_ = other.base_;
    max_ = other.max_;
    sticker_count_ = other.sticker_count_;
    for (unsigned j = 0; j < max_; j++) {
        xcorr_[j] = other.xcorr_[j];
        ycorr_[j] = other.ycorr_[j];
        check_[j] = other.check_[j];
        stickers_[j] = other.stickers_[j];
    }
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
    if (this == &other) { return *this;}
    xcorr_ = vector<int>(other.max_);
    ycorr_ = vector<int>(other.max_);
    check_ = vector<bool>(other.max_);
    stickers_ = vector<Image*>(other.max_);
    base_ = other.base_;
    max_ = other.max_;
    sticker_count_ = other.sticker_count_;
    for (unsigned j = 0; j < max_; j++) {
        xcorr_[j] = other.xcorr_[j];
        ycorr_[j] = other.ycorr_[j];
        check_[j] = other.check_[j];
        stickers_[j] = other.stickers_[j];
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned new_max) {
    if (new_max == max_) {
        return;
    }
    xcorr_.resize(new_max);
    ycorr_.resize(new_max);
    check_.resize(new_max);
    stickers_.resize(new_max);

    if (new_max > max_) {
        for (unsigned int i = max_; i < new_max; i++) {      
            stickers_[i] = nullptr;
            xcorr_[i] = -1;
            ycorr_[i] = -1;
        }
    }
    if (new_max < max_) {
        sticker_count_ = new_max;
    }
    max_ = new_max;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index >= max_ || index < 0) {
        return false;
    }
    if (xcorr_[index] == -1 || ycorr_[index] == -1) {
        return false;
    }
    xcorr_[index] = x;
    ycorr_[index] = y;
    return true;
}

Image* StickerSheet::getSticker(unsigned index) {
    if (index >= max_ || index < 0 || check_[index] == false || xcorr_[index] == -1 || ycorr_[index] == -1) {
        return NULL;
    }
    return stickers_[index];
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    if (sticker_count_ < max_) {
        for (unsigned int i = 0; i < max_; i++) {
            if (!check_[i]) {
                stickers_[i] = &sticker;
                xcorr_[i] = x;
                ycorr_[i] = y;
                check_[i] = true;
                sticker_count_ += 1;
                return i;
            }
        }
	}
	return -1;
}

void StickerSheet::removeSticker(unsigned index) {
    if (index < 0 || index >= max_ || check_[index] == false) {
        return;
    }
    stickers_[index] = nullptr;
    sticker_count_--;
    check_[index] = false;
    xcorr_[index] = -1;
    ycorr_[index] = -1;
}

Image StickerSheet::render() const {
    Image returnit = base_;
	for (unsigned i = 0; i < check_.size(); i++) {
        if (check_[i] == true) {
            //resize
            if ((ycorr_[i] + stickers_[i]->height()) > returnit.height() && (xcorr_[i] + stickers_[i]->width()) > returnit.width()) { //resize height && width
                returnit.resize(stickers_[i]->width() + xcorr_[i], stickers_[i]->height() + ycorr_[i]);
            } else if ((ycorr_[i] + stickers_[i]->height()) > returnit.height()) {  //resize height
                returnit.resize(returnit.width(), stickers_[i]->height() + ycorr_[i]);
            } else if ((xcorr_[i] + stickers_[i]->width()) > returnit.width()) {    //resize width
                returnit.resize(stickers_[i]->width() + xcorr_[i], returnit.height());
            }
            //add stickers
            for (unsigned int w = xcorr_[i]; w < xcorr_[i] + stickers_[i]->width(); w++) {
                for (unsigned int h = ycorr_[i]; h < ycorr_[i] + stickers_[i]->height(); h++) {
                    unsigned int x = w - xcorr_[i];
                    unsigned int y = h - ycorr_[i];
                    cs225::HSLAPixel & pixel = returnit.getPixel(w, h);
                    cs225::HSLAPixel & new_pixel = stickers_[i]->getPixel(x, y);
                    if (new_pixel.a != 0) {
                        pixel = new_pixel;
                    }
                }
            }
        }
    }
    return returnit;
}



#include "Image.h"
using namespace std;

void Image::lighten() {
    lighten(0.1);
}

void Image::lighten(double amount) {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            if (this->getPixel(i, j).l + amount > 1) {
                this->getPixel(i, j).l = 1;
            } else {
                this->getPixel(i, j).l += amount;
            }
        }
    }
}

void Image::darken() {
    darken(0.1);
}

void Image::darken(double amount) {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            if (this->getPixel(i, j).l - amount < 0) {
                this->getPixel(i, j).l = 0;
            } else {
                this->getPixel(i, j).l -= amount;
            }
        }
    }
}

void Image::saturate() {
    saturate(0.1);
}

void Image::saturate(double amount) {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            if (this->getPixel(i, j).l != 0 || this->getPixel(i, j).l != 1) {
                if (this->getPixel(i, j).s + amount > 1) {
                    this->getPixel(i, j).s = 1;
                } else {
                    this->getPixel(i, j).s += amount;
                }
            }
        }
    }
}

void Image::desaturate() {
    desaturate(0.1);
}

void Image::desaturate(double amount) {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            if (this->getPixel(i, j).l != 0 || this->getPixel(i, j).l != 1) {
                if (this->getPixel(i, j).s - amount < 0) {
                    this->getPixel(i, j).s = 0;
                } else {
                    this->getPixel(i, j).s -= amount;
                }
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            if (this->getPixel(i, j).l != 0 || this->getPixel(i, j).l != 1) {
                this->getPixel(i, j).s = 0;
            }
        }
    }
}

void Image::rotateColor (double degrees) {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            if (this->getPixel(i, j).l != 0 || this->getPixel(i, j).l != 1) {
                if (this->getPixel(i, j).h + degrees > 360) {
                    this->getPixel(i, j).h = this->getPixel(i, j).h - 360 + degrees;
                } else if (this->getPixel(i, j).h + degrees < 0) {
                    this->getPixel(i, j).h = this->getPixel(i, j).h + 360 + degrees;
                } else {
                    this->getPixel(i, j).h += degrees;
                }
            }
        }
    }
}

double Image::illinifyHelper(double hue) {
    
    double diff_blue = double(abs(hue - 11));
    double diff_orange = double(abs(hue - 216));
    if (diff_blue < diff_orange) {
        return 11.0;
    }
    return 216.0;
}

void Image::illinify() {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            if (this->getPixel(i, j).l != 0 || this->getPixel(i, j).l != 1) {
                this->getPixel(i, j).h = illinifyHelper(this->getPixel(i, j).h);
            }
        }
    }
}

void Image::scale (double factor) {
    if (factor == 1) {
        return;         
    }
    Image * image_ = new Image(*this);
	this->resize(this->width() * factor, this->height() * factor);
	for (unsigned int i = 0; i < this->height(); i++) {
		for (unsigned int j = 0; j < this->width(); j++) {
			cs225::HSLAPixel & pixel = getPixel(j, i);
			cs225::HSLAPixel & new_pixel = image_->getPixel(j / factor, i / factor);
			pixel = new_pixel;
		}
	}
    delete image_;   //free
}   

void Image::scale (unsigned w, unsigned h) {

    double factor_width = (double)w / (double)(this->width());
    double factor_height = (double)h /(double)(this->height());

    if (factor_width < factor_height) {
        scale(factor_width);
        this->resize(w, this->height());
    } else if (factor_width == factor_height) {
        scale(factor_height);
        this->resize(w, h);
    } else {
        scale(factor_height);
        this->resize(this->width(), h);
    }
}
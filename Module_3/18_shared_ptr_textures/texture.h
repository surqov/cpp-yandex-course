#pragma once
#include "common.h"

class Texture {
public:
    explicit Texture(Image image)
        : image_(std::move(image)) {
    }

    Size GetSize() const {
        return GetImageSize(image_);
    }

    char GetPixelColor(Point p) const {
        return image_.at(p.x).at(p.y);
    }

private:
    Image image_;
};
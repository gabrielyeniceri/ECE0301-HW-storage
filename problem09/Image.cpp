#include "Image.hpp"
#include <stdexcept>
#include <algorithm>

Image::Image() : width(0), height(0), image_data(nullptr) { }
// Creates green square
Image::Image(int size) : width(size), height(size){
 int total_pixels = width * height;
 if (total_pixels > 0) {
    image_data = new RGBPIXEL[total_pixels];
    for (int i = 0; i < total_pixels; ++i) {
        image_data[i] = GREEN;
    }
 } else {
    image_data = nullptr;
 }
}
//creates green rectangle
Image::Image(int w, int h) : width(w), height(h) {
    int total_pixels = width * height;
    if (total_pixels > 0) {
        image_data = new RGBPIXEL[total_pixels];
        for (int i = 0; i < total_pixels; ++i) {
            image_data[i] = GREEN;
        }
    } else {
        image_data = nullptr;
    }
}
//copies
Image::Image(const Image &im) : width(im.width), height(im.height){
  int total_pixels = width * height;
    if (total_pixels > 0) {
        image_data = new RGBPIXEL[total_pixels];
        for (int i = 0; i < total_pixels; ++i) {
            image_data[i] = im.image_data[i];
        }
    } else {
        image_data = nullptr;
    }
}
//deallocates image data
Image::~Image(){
 delete[] image_data;
}
//copy
Image &Image::operator=(Image im)
{
    std::swap(width, im.width);
    std::swap(height, im.height);
    std::swap(image_data, im.image_data);
    return *this;
}

int Image::get_width() const
{
    return width;
}

int Image::get_height() const
{
    return height;
}

RGBPIXEL Image::get_pixel(int index) const
{
    if (index >= width*height) {
        throw std::out_of_range("Pixel index out of range");
    }
    return image_data[index];
}

void Image::set_pixel(int index, const RGBPIXEL color)
{
    if (index >= width*height) {
        throw std::out_of_range("Pixel index out of range");
    }
    image_data[index] = color;
}

bool Image::load_from_file(std::string filename)
{
    // BONUS
    return false;
}

bool Image::save_to_file(std::string filename)
{
    // BONUS
    return false;
}
//addition overloaded
Image operator+(const Image &im, const RGBPIXEL &val)
{
    int width = im.get_width();
    int height = im.get_height();
    Image result(width, height);
    int total_pixels = width * height;
    for (int i = 0; i < total_pixels; ++i) {
        RGBPIXEL pixel = im.get_pixel(i) + val;
        result.set_pixel(i, pixel);
    }
    return result;
}
// also addition overloaded
Image operator+(const RGBPIXEL &val, const Image &im)
{
    return im + val;
}

Image operator-(const Image &im, const RGBPIXEL &val)
{
    // OPTIONAL for bonus
}

Image operator-(const RGBPIXEL &val, const Image &im)
{
    // OPTIONAL for bonus
}

// Image.cpp

#include "Image.hpp"
#include <stdexcept>
#include <algorithm>  // For std::swap
#include "bitmap.hpp"
#include <iostream>   // For error output

// Default constructor
Image::Image() : width(0), height(0), image_data(nullptr) { }

// Constructor for a green square image
Image::Image(int size) : width(size), height(size) {
    int total_pixels = width * height;
    if (total_pixels > 0) {
        image_data = new RGBPIXEL[total_pixels];
        // Initialize all pixels to GREEN
        for (int i = 0; i < total_pixels; ++i) {
            image_data[i] = GREEN;
        }
    } else {
        image_data = nullptr;
    }
}

// Constructor for a green rectangular image
Image::Image(int w, int h) : width(w), height(h) {
    int total_pixels = width * height;
    if (total_pixels > 0) {
        image_data = new RGBPIXEL[total_pixels];
        // Initialize all pixels to GREEN
        for (int i = 0; i < total_pixels; ++i) {
            image_data[i] = GREEN;
        }
    } else {
        image_data = nullptr;
    }
}

// Copy constructor
Image::Image(const Image &im) : width(im.width), height(im.height) {
    int total_pixels = width * height;
    if (total_pixels > 0) {
        image_data = new RGBPIXEL[total_pixels];
        // Copy pixel data
        for (int i = 0; i < total_pixels; ++i) {
            image_data[i] = im.image_data[i];
        }
    } else {
        image_data = nullptr;
    }
}

// Destructor
Image::~Image() {
    delete[] image_data;
}

// Copy assignment operator using copy-swap idiom
Image& Image::operator=(Image im) {
    std::swap(width, im.width);
    std::swap(height, im.height);
    std::swap(image_data, im.image_data);
    return *this;
}

int Image::get_width() const {
    return width;
}

int Image::get_height() const {
    return height;
}

RGBPIXEL Image::get_pixel(int index) const {
    if (index < 0 || index >= width * height) {
        throw std::out_of_range("Pixel index out of range");
    }
    return image_data[index];
}

void Image::set_pixel(int index, const RGBPIXEL color) {
    if (index < 0 || index >= width * height) {
        throw std::out_of_range("Pixel index out of range");
    }
    image_data[index] = color;
}

// Load image data from a BMP file
bool Image::load_from_file(std::string filename) {
    // Use import_bmp to read the image data
    RGBIMAGEDATA imdata = import_bmp(filename);
    if (imdata.data == nullptr) {
        // Failed to load image
        std::cerr << "Failed to load image from file: " << filename << std::endl;
        return false;
    }

    // Deallocate current image data
    delete[] image_data;

    // Set new width, height, and image_data
    width = imdata.width;
    height = imdata.height;
    image_data = imdata.data; // Take ownership of the data

    // No need to delete imdata.data since we now own it
    return true;
}

// Save image data to a BMP file
bool Image::save_to_file(std::string filename) {
    if (image_data == nullptr || width == 0 || height == 0) {
        // No image data to save
        std::cerr << "No image data to save." << std::endl;
        return false;
    }

    // Create RGBIMAGEDATA struct
    RGBIMAGEDATA imdata;
    imdata.width = width;
    imdata.height = height;
    imdata.data = image_data; // Use existing image_data

    // Use export_bmp to save the image
    bool success = export_bmp(imdata, filename);
    if (!success) {
        std::cerr << "Failed to save image to file: " << filename << std::endl;
    }

    return success;
}

// Overloaded addition operator: Image + RGBPIXEL
Image operator+(const Image &im, const RGBPIXEL &val) {
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

// Overloaded addition operator: RGBPIXEL + Image
Image operator+(const RGBPIXEL &val, const Image &im) {
    return im + val;
}

// Overloaded subtraction operator: Image - RGBPIXEL
Image operator-(const Image &im, const RGBPIXEL &val) {
    int width = im.get_width();
    int height = im.get_height();
    Image result(width, height);
    int total_pixels = width * height;

    for (int i = 0; i < total_pixels; ++i) {
        RGBPIXEL pixel = im.get_pixel(i) - val;
        result.set_pixel(i, pixel);
    }
    return result;
}

// Overloaded subtraction operator: RGBPIXEL - Image
Image operator-(const RGBPIXEL &val, const Image &im) {
    int width = im.get_width();
    int height = im.get_height();
    Image result(width, height);
    int total_pixels = width * height;

    for (int i = 0; i < total_pixels; ++i) {
        RGBPIXEL pixel = val - im.get_pixel(i);
        result.set_pixel(i, pixel);
    }
    return result;
}

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "bitmap.hpp"
#include "Image.hpp"

#include <cstdint>

/* Provided test cases */
TEST_CASE("Test size constructor", "[image]"){
    int size = 10;
    Image im(size);

    REQUIRE(im.get_width() == size);
    REQUIRE(im.get_height() == size);
}

TEST_CASE("Test set/get pixels after size construction", "[image]"){
    int size = 8;
    Image im(size); 
    int first = 12;
    int second = 13;
    im.set_pixel(first, BLACK);
    im.set_pixel(second, RED);

    bool match = true;
    for (int i=0; i<size*size; i++) {
        if (i == first) {
            match = (im.get_pixel(i) == BLACK);
        } else if (i == second) {
            match = (im.get_pixel(i) == RED);
        } else {
            match = (im.get_pixel(i) == GREEN);
        }
        if (!match) {
            break;
        }
    }
    REQUIRE(match);
}

TEST_CASE("Test copy constructor", "[image]"){
    // initial image
    int width = 10;
    int height = 8;
    Image im(width, height);

    int first = 0;
    int last = width*height-1;
    int middle = (width*height-1)/2;

    im.set_pixel(first, BLACK);
    im.set_pixel(last, RED);

    // copy image
    Image imgcopy(im);

    // change initial
    im.set_pixel(first, RED);
    im.set_pixel(middle, BLUE);
    im.set_pixel(last, WHITE);

    // test copy
    bool match = true; 
    for (int i=0; i<width*height; i++) {
        if (i == first) {
            match = (imgcopy.get_pixel(i) == BLACK);
        } else if (i == last) {
            match = (imgcopy.get_pixel(i) == RED);
        } else {
            match = (imgcopy.get_pixel(i) == GREEN);
        }
        if (!match) {
            break;
        }
    }
    REQUIRE(match);
}


TEST_CASE("Test operator+", "[image]"){
    int width = 10;
    int height = 12;
    Image im(width, height);

    for (int i=0; i<width*height; i++) {
        im.set_pixel(i, {0x80, 0x05, 0xAA});
    }

    RGBPIXEL val = {0x21, 0x05, 0xFF};

    Image res = im+val;

    bool match = true;
    for (int i=0; i<width*height; i++) {
        match = (res.get_pixel(i) == im.get_pixel(i)+val);
        if (!match) {
            break;
        }
    }
    REQUIRE(match);
}

/* Your test cases here */

TEST_CASE("Test zero size image", "[image]") {
    Image im(0);
    REQUIRE(im.get_width() == 0);
    REQUIRE(im.get_height() == 0);

    REQUIRE_THROWS_AS(im.set_pixel(0, RED), std::out_of_range);
    REQUIRE_THROWS_AS(im.get_pixel(0), std::out_of_range);
}
TEST_CASE("Bonus: Remove red pixel noise", "[image][bonus]") {
    Image img;
    REQUIRE(img.load_from_file("bonus_test.bmp"));

    int width = img.get_width();
    int height = img.get_height();
    int total_pixels = width * height;

    // Remove red pixel noise
    for (int i = 0; i < total_pixels; ++i)
    {
        RGBPIXEL pixel = img.get_pixel(i);
        if (pixel == RED) {
            // Set pixel to BLACK or any other desired color
            img.set_pixel(i, BLACK);
        }
    }

    // Save the resulting image
    REQUIRE(img.save_to_file("bonus_result.bmp"));
}

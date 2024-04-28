#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <math.h>
#include <time.h>
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

const uint16_t W = 1920;
const uint16_t H = 1080;

int main() {
    clock_t begin;
    clock_t end;
    // // Load the image
    Mat base = imread("grayscale_image_l.png", IMREAD_GRAYSCALE);
    Mat ball = imread("grayscale_ball_l.png", IMREAD_GRAYSCALE);
    Mat bin_out(H, W, CV_8UC1);


    // Check if the image was loaded successfully
    if (base.empty() || ball.empty())
    {
        std::cout << "Error: Could not read the image." << std::endl;
        return -1;
    }
    else
    {
        std::cout << "Opened base images." << std::endl;
    }

    uint16_t temp;
    begin = clock();
    for(uint16_t x = 0; x < W; x++)
    {
        for(uint16_t y = 0; y < H; y++)
        {
            temp = base.at<uint16_t>(y, x) ^ ball.at<uint16_t>(y, x);

            bin_out.at<uint16_t>(y, x) = (temp >> 8) > 10 ? USHRT_MAX : 0;
        }
    }
    end = clock();

    cout << " execution time is: " << (double)(end - begin) / CLOCKS_PER_SEC << endl;


    imwrite("binary_out.png", bin_out);

    // Mat bin_out = imread("binary_out.png", IMREAD_GRAYSCALE);
    
    // uint16_t col_accum[1920] = {0};
    // uint16_t center;

    // clock_t begin = clock();
    // for(uint16_t row = 0; row < H; row++)
    // {
    //     for(uint16_t left_edge = 0; left_edge < W-1; left_edge++)
    //     {
    //         for(uint16_t right_edge = left_edge+1; right_edge < W; right_edge++)
    //         {
    //             if(bin_out.at<uint8_t>(row, left_edge) > 0 && bin_out.at<uint8_t>(row, right_edge) > 0)
    //             {
    //                 center = (left_edge + right_edge) / 2;
    //                 col_accum[center] += 1; 
    //             }
    //         }
    //     }
    // }
    // clock_t end = clock();

    // cout << " max element is: " << max_element(col_accum , col_accum+1920) - col_accum << endl;
    // cout << " execution time is: " << (double)(end - begin) / CLOCKS_PER_SEC << endl;


    vector<Vec3f> circles;
    begin = clock();
    HoughCircles(bin_out, circles, HOUGH_GRADIENT, 1,
    bin_out.rows, // change this value to detect circles with different distances to each other
    2, 1, 4, 10 // change the last two parameters
    // (min_radius & max_radius) to detect larger circles
    );
    end = clock();

    if(circles.empty()) cout << "You fucked up\n";

    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];

        cout << "coord: " << c[0] << "," << c[1] << endl;
        cout << "radius: " << c[2] << endl << endl;
    }
    cout << " execution time is: " << (double)(end - begin) / CLOCKS_PER_SEC << endl;

    return 0;
}

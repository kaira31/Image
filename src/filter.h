#ifndef FILTER_H
#define FILTER_H

#include <opencv2/opencv.hpp>

// Function to apply grayscale filter
int greyscale(cv::Mat& src, cv::Mat& dst);

// Function to apply sepia tone filter to an image
void sepiaToneFilter(cv::Mat& src, cv::Mat& dst);

// Function to implement 5x5_1 blur filter
int blur5x5_1(cv::Mat& src, cv::Mat& dst);

// Function to implement 5x5_2 blur filter
int blur5x5_2(cv::Mat& src, cv::Mat& dst);

// Function for calculating Sobel X
int sobelX3x3(cv::Mat &src, cv::Mat &dst);

// Function for calculating Sobel Y
int sobelY3x3(cv::Mat &src, cv::Mat &dst);

// Function that generates a gradient magnitude image from the X and Y Sobel images
int magnitude(cv::Mat &sx, cv::Mat &sy, cv::Mat &dst);

// Function that generates a blurQuantized frame
int blurQuantize(cv::Mat& src, cv::Mat& dst, int levels);

// Extension - Function to apply Sepia Tone Filter with Vignetting
void sepiaToneFilterWithVignetting(cv::Mat& src, cv::Mat& dst);

// Function to apply cartooning
int cartoon( cv::Mat &src, cv::Mat&dst, int levels, int magThreshold );

// Extension - Function to add caption
void addCaption(cv::Mat& image, const std::string& caption);

//Function  to apply brightness
int BrightnessContrast(cv::Mat& src, cv::Mat& dst, double alpha, int beta);
void embossFilter(cv::Mat& src, cv::Mat& dst); 
#endif // FILTER_H

#include <chrono>
#include <iostream>
#include "opencv2/opencv.hpp"

// prototypes for the functions to test
int blur5x5_1(cv::Mat &src, cv::Mat &dst);
int blur5x5_2(cv::Mat &src, cv::Mat &dst);

// returns a double which gives time in seconds
double getTime() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
    return duration.count() / 1e6; // convert to seconds
}

int main(int argc, char *argv[]) {
    cv::Mat src; // define a Mat data type (matrix/image), allocates a header, image data is null
    cv::Mat dst; // cv::Mat to hold the output of the process
    char filename[256]; // a string for the filename

    // usage: checking if the user provided a filename
    if (argc < 2) {
        std::cout << "Usage " << argv[0] << " <image filename>\n";
        exit(-1);
    }
    std::strcpy(filename, argv[1]); // copying 2nd command line argument to filename variable

    // read the image
    src = cv::imread(filename); // allocating the image data
    // test if the read was successful
    if (src.data == NULL) { // src.data is the reference to the image data
        std::cout << "Unable to read image " << filename << "\n";
        exit(-1);
    }

    const int Ntimes = 10;

    //////////////////////////////
    // set up the timing for version 1
    double startTime = getTime();

    // execute the file on the original image a couple of times
    for (int i = 0; i < Ntimes; i++) {
        blur5x5_1(src, dst);
    }

    // end the timing
    double endTime = getTime();

    // compute the time per image
    double difference = (endTime - startTime) / Ntimes;

    // print the results
    std::cout << "Time per image (1): " << difference << " seconds\n";

    //////////////////////////////
    // set up the timing for version 2
    startTime = getTime();

    // execute the file on the original image a couple of times
    for (int i = 0; i < Ntimes; i++) {
        blur5x5_2(src, dst);
    }

    // end the timing
    endTime = getTime();

    // compute the time per image
    difference = (endTime - startTime) / Ntimes;

    // print the results
    std::cout << "Time per image (2): " << difference << " seconds\n";

    // terminate the program
    std::cout << "Terminating\n";

    return 0;
}

#include <opencv2/opencv.hpp>
#include <algorithm>
#include "filter.h"

// Applying grayscale frame 
int greyscale(cv::Mat& src, cv::Mat& dst) {
    // Ensure that the destination image has the same size and type as the source
    dst.create(src.size(), src.type());

    // Loop through each column of the source image
    for (int i = 0; i < src.cols; i++) {
        // Loop through each row of the source image
        for (int j = 0; j < src.rows; j++) {
            // Access the color values (B, G, R) of the current pixel in the source image
            cv::Vec3b color = src.at<cv::Vec3b>(cv::Point(i, j));

            // Calculate the greyscale value by subtracting 255 from the green channel
            uchar grey_value = static_cast<uchar>(255 - color.val[1]);

            // Assign the greyscale value to all three color channels in the destination pixel
            dst.at<cv::Vec3b>(cv::Point(i, j)) = cv::Vec3b(grey_value, grey_value, grey_value);
        }
    }

    // Return 0 to indicate successful execution
    return 0;
}

// Sepia Tone Filter
// Applying a sepia tone effect to the image, giving it a warm, brownish tone
void sepiaToneFilter(cv::Mat& src, cv::Mat& dst) {
    // Ensure that the destination image has the same size and type as the source
    dst.create(src.size(), src.type());

    // Loop through each column of the source image
    for (int i = 0; i < src.cols; i++) {
        // Loop through each row of the source image
        for (int j = 0; j < src.rows; j++) {
            // Access the color values (B, G, R) of the current pixel in the source image
            cv::Vec3b color = src.at<cv::Vec3b>(cv::Point(i, j));

            // Calculate the new red value using the sepia tone coefficients
            uchar newRed = cv::saturate_cast<uchar>(0.393 * color.val[2] + 0.769 * color.val[1] + 0.189 * color.val[0]);

            // Calculate the new green value using the sepia tone coefficients
            uchar newGreen = cv::saturate_cast<uchar>(0.349 * color.val[2] + 0.686 * color.val[1] + 0.168 * color.val[0]);

            // Calculate the new blue value using the sepia tone coefficients
            uchar newBlue = cv::saturate_cast<uchar>(0.272 * color.val[2] + 0.534 * color.val[1] + 0.131 * color.val[0]);

            // Assign the sepia tone values to the destination pixel
            dst.at<cv::Vec3b>(cv::Point(i, j)) = cv::Vec3b(newBlue, newGreen, newRed);
        }
    }
}

// 5x5_1 blur filter
// Applying a Gaussian blur using a 5x5 kernel. This smoothens the image.
int blur5x5_1(cv::Mat& src, cv::Mat& dst) {
    // To ensure : The function should not modify the src image
    // Create a copy of the source image to initialize the destination image
    dst = src.clone();

    // 5x5 Gaussian kernel
    int kernel[5][5] = {
        {1, 2, 4, 2, 1},
        {2, 4, 8, 4, 2},
        {4, 8, 16, 8, 4},
        {2, 4, 8, 4, 2},
        {1, 2, 4, 2, 1}
    };

    // Loop through each pixel excluding the outer two rows and columns
    for (int i = 2; i < src.rows - 2; i++) {
        for (int j = 2; j < src.cols - 2; j++) {
            // Loop through each color channel (B, G, R)
            for (int k = 0; k < src.channels(); k++) {
                int sum = 0;

                // Applying the 5x5 Gaussian blur filter
                for (int u = -2; u <= 2; u++) {
                    for (int v = -2; v <= 2; v++) {
                        sum += src.at<cv::Vec3b>(i + u, j + v)[k] * kernel[u + 2][v + 2];
                    }
                }

                // Normalize the sum and assign it to the destination pixel
                dst.at<cv::Vec3b>(i, j)[k] = cv::saturate_cast<uchar>(sum / 100);
            }
        }
    }

    return 0;  // Return 0 to indicate successful execution
}


// 5x5_2 blur filter
// Applying a separable Gaussian blur in a combination of horizontal and vertical using a 1x5 kernel
int blur5x5_2(cv::Mat& src, cv::Mat& dst) {
    // To ensure: The function should not modify the src image
    // Create a copy of the source image to initialize the destination image
    dst = src.clone();

    // Separable 1x5 filters
    int kernel[5] = {1, 2, 4, 2, 1};

    // Loop through each pixel excluding the outer two rows and columns
    for (int i = 2; i < src.rows - 2; i++) {
        for (int j = 2; j < src.cols - 2; j++) {
            // Loop through each color channel (B, G, R)
            for (int k = 0; k < src.channels(); k++) {
                int sum = 0;

                // Applying the 1x5 vertical filter
                for (int u = -2; u <= 2; u++) {
                    sum += src.at<cv::Vec3b>(i + u, j)[k] * kernel[u + 2];
                }

                // Normalize the sum and assign it to the destination pixel
                dst.at<cv::Vec3b>(i, j)[k] = cv::saturate_cast<uchar>(sum / 10);
            }
        }
    }

    // Create a temporary matrix for the horizontal pass
    cv::Mat temp = dst.clone();

    // Loop through each pixel excluding the outer two rows and columns
    for (int i = 2; i < src.rows - 2; i++) {
        for (int j = 2; j < src.cols - 2; j++) {
            // Loop through each color channel (B, G, R)
            for (int k = 0; k < src.channels(); k++) {
                int sum = 0;

                // Applying the 1x5 horizontal filter
                for (int v = -2; v <= 2; v++) {
                    sum += temp.at<cv::Vec3b>(i, j + v)[k] * kernel[v + 2];
                }

                // Normalize the sum and assign it to the destination pixel
                dst.at<cv::Vec3b>(i, j)[k] = cv::saturate_cast<uchar>(sum / 10);
            }
        }
    }

    return 0;  // Return 0 to indicate successful execution
}

// Sobel X 3x3
// Applies the Sobel operator to detect horizontal edges in the image
int sobelX3x3(cv::Mat &src, cv::Mat &dst) {
    dst = cv::Mat::zeros(src.size(), CV_16SC3);

    for (int i = 1; i < src.rows - 1; i++) {
        // src pointer
        cv::Vec3b *rptrm1 = src.ptr<cv::Vec3b>(i - 1);
        cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);
        cv::Vec3b *rptrp1 = src.ptr<cv::Vec3b>(i + 1);

        // destination pointer
        cv::Vec3s *dptr = dst.ptr<cv::Vec3s>(i);

        // for each column
        for (int j = 1; j < src.cols - 1; j++) {
            // for each color channel
            for (int c = 0; c < 3; c++) {
                dptr[j][c] = (-1 * rptrm1[j - 1][c] + 1 * rptrm1[j + 1][c] +
                              -2 * rptr[j - 1][c] + 2 * rptr[j + 1][c] +
                              -1 * rptrp1[j - 1][c] + 1 * rptrp1[j + 1][c]) ;
            }
        }
    }

    return 0;
}

// Sobel Y 3x3
// Applies the Sobel operator to detect vertical edges in the image.
int sobelY3x3(cv::Mat &src, cv::Mat &dst) {
    dst = cv::Mat::zeros(src.size(), CV_16SC3);

    for (int i = 1; i < src.rows - 1; i++) {
        // src pointer
        cv::Vec3b *rptrm1 = src.ptr<cv::Vec3b>(i - 1);
        cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);
        cv::Vec3b *rptrp1 = src.ptr<cv::Vec3b>(i + 1);

        // destination pointer
        cv::Vec3s *dptr = dst.ptr<cv::Vec3s>(i);

        // for each column
        for (int j = 1; j < src.cols - 1; j++) {
            // for each color channel
            for (int c = 0; c < 3; c++) {
                dptr[j][c] = -rptrm1[j - 1][c] - 2 * rptrm1[j][c] - rptrm1[j + 1][c] +
                              rptrp1[j - 1][c] + 2 * rptrp1[j][c] + rptrp1[j + 1][c];
            }
        }
    }

    return 0;
}

// Function that generates a gradient magnitude image from the X and Y Sobel images
// Magnitude of Sobel Filters
// Calculates the gradient magnitude of the image using Sobel X and Y filters
int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst ) {
    // allocate destination space
    //dst = cv::Mat::zeros(sx.size(), CV_16SC3);
    dst = sx.clone();

    // loop through src and apply vertical filter
    // go through rows
    for (int i = 0; i < sx.rows; i++) {
        
        // source row pointer
        cv::Vec3s *rowptrsx = sx.ptr<cv::Vec3s>(i);
        cv::Vec3s *rowptrsy = sy.ptr<cv::Vec3s>(i);
    
        // destination pointer
        cv::Vec3s *dstptr = dst.ptr<cv::Vec3s>(i);

        // go through columes
        for (int j = 0; j < sx.cols; j++) {
            
            // go though each color channels
            for (int k = 0; k < 3; k++) {
                // calculate maginitude
                dstptr[j][k] = sqrt((rowptrsx[j][k] * rowptrsx[j][k]) + (rowptrsy[j][k] * rowptrsy[j][k]));
            }
        }
    }
    return 0;
}

// BlurQuantize
// Blurs and quantizes an image into a specified number of color levels
int blurQuantize(cv::Mat& src, cv::Mat& dst, int levels) {
    // Check if the source image is empty
    if (src.empty()) {
        printf("Source image is empty\n");
        return -1;
    }

    // Blur the source image
    cv::GaussianBlur(src, dst, cv::Size(5, 5), 0, 0);

    // Quantize the image into a fixed number of levels
    double bucketSize = 255.0 / levels;

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            for (int c = 0; c < src.channels(); c++) {
                // Quantize each color channel
                dst.at<cv::Vec3b>(y, x)[c] =
                    cv::saturate_cast<uchar>(bucketSize * cv::saturate_cast<int>(src.at<cv::Vec3b>(y, x)[c] / bucketSize));
            }
        }
    }

    return 0;
}


// Extension - Sepia Tone Filter with Vignetting
// Applies a sepia tone effect with a vignetting effect, which darkens the edges of the image
// Vignetting - draws the viewer's attention towards the center of the image, thus creating a natural focus point
void sepiaToneFilterWithVignetting(cv::Mat& src, cv::Mat& dst) {
    // The destination image has the same size and type as the source
    dst.create(src.size(), src.type());

    // Define the center of the image
    cv::Point center(src.cols / 2, src.rows / 2);

    // Loop through each column of the source image
    for (int i = 0; i < src.cols; i++) {
        // Loop through each row of the source image
        for (int j = 0; j < src.rows; j++) {
            // Access the color values (B, G, R) of the current pixel in the source image
            cv::Vec3b color = src.at<cv::Vec3b>(cv::Point(i, j));

            // Calculate the distance from the current pixel to the center of the image
            double distance = cv::norm(cv::Point(i, j) - center);

            // Calculate the vignetting factor based on distance from the center
            double vignette = 1.0 - (distance / (src.cols / 2));

            // Apply vignetting to the sepia tone coefficients
            double redCoeff = 0.272 * vignette;
            double greenCoeff = 0.534 * vignette;
            double blueCoeff = 0.131 * vignette;

            // Calculate the new red value using the sepia tone coefficients
            uchar newRed = cv::saturate_cast<uchar>(redCoeff * color.val[2] + 0.393 * color.val[1] + 0.769 * color.val[0]);

            // Calculate the new green value using the sepia tone coefficients
            uchar newGreen = cv::saturate_cast<uchar>(greenCoeff * color.val[2] + 0.349 * color.val[1] + 0.686 * color.val[0]);

            // Calculate the new blue value using the sepia tone coefficients
            uchar newBlue = cv::saturate_cast<uchar>(blueCoeff * color.val[2] + 0.272 * color.val[1] + 0.534 * color.val[0]);

            // Assign the sepia tone values to the destination pixel
            dst.at<cv::Vec3b>(cv::Point(i, j)) = cv::Vec3b(newBlue, newGreen, newRed);
        }
    }
}

// Cartooning
// Converts the image into a cartoon-like image using edge detection and color quantization
int cartoon( cv::Mat &src, cv::Mat&dst, int levels, int magThreshold ) {
    // initilize all the useful parameters
    cv::Mat sobelx;
    cv::Mat sobely;
    cv::Mat mag;
    cv::Mat quantize;

    // get the magnitude image
    sobelX3x3(src, sobelx);
    sobelY3x3(src, sobely);
    magnitude(sobelx, sobely, mag);

    // quantize and blur
    blurQuantize(src, quantize, levels);

    // allocate destination space
    dst = quantize.clone();

    for (int i = 0; i < dst.rows; i++) {
        
        // src pointer
        cv::Vec3s *rowptr = mag.ptr<cv::Vec3s>(i);

        // destination pointer
        cv::Vec3b *dstptr = dst.ptr<cv::Vec3b>(i);

        for (int j = 0; j < dst.cols; j++) {
           // loop thru all the magnitude
            if (rowptr[j][0] > magThreshold || rowptr[j][1] > magThreshold || rowptr[j][2] > magThreshold) {
                // make channels that are greater thatn the threashold black
                dstptr[j][0] = 0;
                dstptr[j][1] = 0;
                dstptr[j][2] = 0;
            }
        }
    }
    return 0;
}


// Extension
// Adds a caption to the bottom center of the image in white color
void addCaption(cv::Mat& image, const std::string& caption) {
    int fontFace = cv::FONT_HERSHEY_SIMPLEX;
    double fontScale = 0.5;
    int thickness = 1;
    int baseline = 0;
    cv::Size textSize = cv::getTextSize(caption, fontFace, fontScale, thickness, &baseline);
    cv::Point textOrg((image.cols - textSize.width) / 2, image.rows - 10);
    cv::putText(image, caption, textOrg, fontFace, fontScale, cv::Scalar(255, 255, 255), thickness);
}
// changes the brightness and contrast of the video
int BrightnessContrast(cv::Mat& src, cv::Mat& dst, double alpha, int beta) {
    // Adjust the brightness and contrast using the formula: dst = alpha * src + beta
    src.convertTo(dst, -1, alpha, beta);
    return 0;
}
void embossFilter(cv::Mat& src, cv::Mat& dst) {
    // Create a copy of the source image to initialize the destination image
    dst = src.clone();

    // Define the embossing kernel
    int kernel[3][3] = {
        {-2, -1, 0},
        {-1,  1, 1},
        { 0,  1, 2}
    };

    // Loop through each pixel excluding the outer two rows and columns
    for (int i = 1; i < src.rows - 1; i++) {
        for (int j = 1; j < src.cols - 1; j++) {
            // Loop through each color channel (B, G, R)
            for (int k = 0; k < src.channels(); k++) {
                int sum = 0;

                // Applying the 3x3 embossing kernel
                for (int u = -1; u <= 1; u++) {
                    for (int v = -1; v <= 1; v++) {
                        sum += src.at<cv::Vec3b>(i + u, j + v)[k] * kernel[u + 1][v + 1];
                    }
                }

                // Normalize the sum and assign it to the destination pixel
                dst.at<cv::Vec3b>(i, j)[k] = cv::saturate_cast<uchar>(sum);
            }
        }
    }
}
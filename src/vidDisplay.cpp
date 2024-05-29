#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <vector>
#include "filter.h"
#include "faceDetect.h"

double getTime() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
    return duration.count() / 1e6; // convert to seconds
}

int main(int argc, char* argv[]) {
    cv::VideoCapture* capdev;
    cv::Mat sobelXFrame;
    cv::Mat sobelYFrame;
    cv::Mat quantizedFrame;
    std::vector<cv::Rect> faces;
    cv::Rect last(0, 0, 0, 0);
    
    bool sobelXMode = false;
    bool sobelYMode = false;

    bool saveSobelX = false;
    bool saveSobelY = false;

    bool displaySobelX = false;
    bool displaySobelY = false;

    double startTime, endTime, difference;

    bool vignettingMode = false; // Flag to indicate if vignetting mode is enabled

    // Initializing the values to apply the filter in a loop to give a video output
    char face = '\0';
    char brightness = '\0';
    char cartoons = '\0';
    char gray = '\0';
    char magnitudes = '\0';
    char recording = '\0';

    // Open the video device
    capdev = new cv::VideoCapture(0);
    //capdev = new cv::VideoCapture("C:/Users/shrut/OneDrive/Desktop/1050505960-preview.mp4");
    if (!capdev->isOpened()) {
        printf("Unable to open video device\n");
        return (-1);
    }

    // Get some properties of the image
    cv::Size refS((int)capdev->get(cv::CAP_PROP_FRAME_WIDTH),
                  (int)capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
    printf("Expected size: %d %d\n", refS.width, refS.height);

    cv::namedWindow("Video", 1); // Identifies a window

    cv::Mat frame;
    cv::Mat altGrayscaleFrame;
    cv::Mat sepiaFrame;
    cv::Mat blurFrame;
    cv::Mat sepiafilteredFrame;
    int frames_per_second = capdev->get(cv::CAP_PROP_FPS);
    cv::VideoWriter record("/Users/aswinchanderaravindkumar/Desktop/record.avi", cv::VideoWriter::fourcc('M','J','P','G'),frames_per_second,cv::Size(refS.width, refS.height));
    bool frameCaptured = false;
    bool grayscaleMode = false;
    bool blurMode = false;
    bool calculateGradientMagnitude = false;
    //bool medianFilterMode = false;
    int medianFilterSize = 3;


    for (;;) {
        *capdev >> frame; // Get a new frame from the camera, treat as a stream
        if (frame.empty()) {
            printf("frame is empty\n");
            break;
        }
        char key = cv::waitKey(10);
        if (recording) {
        cv::Mat outputFrame;
        if (sobelXMode) {
            // Apply Sobel X filter
            sobelX3x3(frame, outputFrame);
        } else if (sobelYMode) {
            // Apply Sobel Y filter
            sobelY3x3(frame, outputFrame);
        } else {
            outputFrame = frame;
        }

        record.write(outputFrame);
        cv::imshow("Video", outputFrame);
    } else {
        if (grayscaleMode) {
            // Display grayscale mode
            cv::Mat grayscaleFrame;
            cv::cvtColor(frame, grayscaleFrame, cv::COLOR_BGR2GRAY);
            cv::imshow("Video", grayscaleFrame);
        } else {
            // Display color mode
            cv::imshow("Video", frame);
        }
    } 
        // See if there is a waiting keystroke
        
        
        // Quit
        if (key == 'q') {
            break;
        } if (key == 's') {
            cv::imwrite("captured_image.jpg", frame);
            printf("Color Image saved as captured_image.jpg\n");
            frameCaptured = true;
        } else if (key == 'p') {
            // 'p' - Pause until any key is pressed
            cv::waitKey(-1);
            printf("Paused\n");
        } else if (key == 'd' && frameCaptured) {
            // 'd' - Display the captured frame when 'd' is pressed
            cv::Mat capturedFrame = cv::imread("captured_image.jpg");
            if (!capturedFrame.empty()) {
                cv::imshow("Captured Frame", capturedFrame);
                printf("Displaying captured frame\n");
                cv::waitKey(0); // Wait until any key is pressed before continuing
            } else {
                printf("Failed to read captured_image.jpg\n");
            }
        } else if (key == 'g') {
            // Toggle grayscale mode
            grayscaleMode = !grayscaleMode;
            printf("Grayscale mode: %s\n", grayscaleMode ? "ON" : "OFF");
        } else if (key == 'k') {
            // Save the current frame in grayscale as an image file
            cv::Mat grayscaleFrame;
            cv::cvtColor(frame, grayscaleFrame, cv::COLOR_BGR2GRAY);

            // Check if the grayscale frame is not empty before saving
            if (!grayscaleFrame.empty()) {
                bool saved = cv::imwrite("captured_grey_image.jpg", grayscaleFrame);

                if (saved) {
                    printf("Grayscale Image saved as captured_grey_image.jpg\n");
                } else {
                    printf("Failed to save captured_grey_image.jpg\n");
                }
            } else {
                printf("Grayscale frame is empty\n");
            }
        } else if (key == 'r') {
            // Display the captured grayscale frame when 'r' is pressed
            cv::Mat capturedGreyFrame = cv::imread("captured_grey_image.jpg");
            if (!capturedGreyFrame.empty()) {
                cv::imshow("Captured Grey Frame", capturedGreyFrame);
                printf("Displaying captured grayscale frame\n");
                cv::waitKey(0); // Wait until any key is pressed before continuing
            } else {
                printf("Failed to read captured_grey_image.jpg\n");
            }
        } else if (key == 'h') {
            // Display the alternative greyscale mode
            greyscale(frame, altGrayscaleFrame);
            cv::imshow("Video", altGrayscaleFrame);
        } else if (key == 'o') {
            // Save the current frame in alternative greyscale as an image file
            greyscale(frame, altGrayscaleFrame);

            // Check if the alternative greyscale frame is not empty before saving
            if (!altGrayscaleFrame.empty()) {
                bool saved = cv::imwrite("captured_alt_image.jpg", altGrayscaleFrame);

                if (saved) {
                    printf("Alternative Greyscale Image saved as captured_alt_image.jpg\n");
                } else {
                    printf("Failed to save captured_alt_image.jpg\n");
                }
            } else {
                printf("Alternative greyscale frame is empty\n");
            }
        } else if (key == 'e') {
            // e- Display the captured alternative greyscale frame
            cv::Mat altCapturedGreyFrame = cv::imread("captured_alt_image.jpg");
            if (!altCapturedGreyFrame.empty()) {
                cv::imshow("Captured Alt Grey Frame", altCapturedGreyFrame);
                printf("Displaying captured alternative greyscale frame\n");
                cv::waitKey(0);
            } else {
                printf("Failed to read captured_alt_image.jpg\n");
            }
        } else if (key == 'f') {
            // Apply sepia filter to the current frame
            sepiaToneFilter(frame, sepiaFrame);
        } else if (key == 'i' && !sepiaFrame.empty()) {
            // 'i' - Save the sepia frame as an image file
            cv::imwrite("captured_sepia_image.jpg", sepiaFrame);
            printf("Sepia Image saved as captured_sepia_image.jpg\n");
        } else if (key == 'z' && !sepiaFrame.empty()) {
            // 'z' - Display the sepia frame when 'z' is pressed
            cv::imshow("Sepia Frame", sepiaFrame);
            printf("Displaying sepia frame\n");
        } else if (key == 'b') {
            // Toggle blur mode
            blurMode = !blurMode;
            printf("Blur mode: %s\n", blurMode ? "ON" : "OFF");
        } else if (key == '1' && blurMode) {
            // Implement blur filter_1
            startTime = getTime();
            blur5x5_1(frame, blurFrame);
            endTime = getTime();
            difference = endTime - startTime;
            printf("Blur filter_1 applied. Time taken: %.4lf seconds\n", difference);
        } else if (key == '2' && blurMode) {
            // Implement blur filter_2 (if available)
            startTime = getTime();
            blur5x5_2(frame, blurFrame);
            endTime = getTime();
            difference = endTime - startTime;
            printf("Blur filter_2 applied. Time taken: %.4lf seconds\n", difference);
        } else if (key == 'S' && blurMode) {
            // Save the blur frame as an image file
            cv::imwrite("captured_blur_image.jpg", blurFrame);
            printf("Blur Image saved as captured_blur_image.jpg\n");
        } else if (key == 'D' && blurMode) {
            // Display the captured blur frame
            cv::Mat capturedBlurFrame = cv::imread("captured_blur_image.jpg");
            if (!capturedBlurFrame.empty()) {
                cv::imshow("Captured Blur Frame", capturedBlurFrame);
                printf("Displaying captured blur frame\n");
                cv::waitKey(0);
            } else {
                printf("Failed to read captured_blur_image.jpg\n");
            }
        } else if (key == 'x') {
            // Apply Sobel X mode
            sobelXMode = true;
            sobelYMode = false;
            saveSobelX = false;
            displaySobelX = false;
            printf("Applying Sobel X\n");
        } else if (key == 'X' && sobelXMode) {
            // Save Sobel X frame
            saveSobelX = true;
            printf("Save Sobel X image\n");
        } else if (key == 'A' && sobelXMode) {
            // Display the saved Sobel X frame
            displaySobelX = true;
            printf("Display Sobel X image\n");
        } else if (key == 'y') {
            // Apply Sobel Y mode
            sobelYMode = true;
            sobelXMode = false;
            saveSobelY = false;
            displaySobelY = false;
            printf("Applying Sobel Y\n");
        } else if (key == 'Y' && sobelYMode) {
            // Save Sobel Y frame
            saveSobelY = true;
            printf("Save Sobel Y image\n");
        } else if (key == 'B' && sobelYMode) {
            // Display the saved Sobel Y frame
            displaySobelY = true;
            printf("Display Sobel Y image\n");
        } else if (sobelXMode) {
            // Apply Sobel X filter
            sobelX3x3(frame, sobelXFrame);

            // Show the absolute value of Sobel X output
            cv::Mat absSobelX;
            cv::convertScaleAbs(sobelXFrame, absSobelX);
            cv::imshow("Sobel X Frame", absSobelX);

            if (saveSobelX) {
                // Save Sobel X frame as an image file
                cv::imwrite("captured_sobelx_image.jpg", absSobelX);
                printf("Sobel X Image saved as captured_sobelx_image.jpg\n");
                saveSobelX = false;
            }

            if (displaySobelX) {
                // Display the saved Sobel X frame
                cv::Mat capturedSobelXFrame = cv::imread("captured_sobelx_image.jpg");
                if (!capturedSobelXFrame.empty()) {
                    cv::imshow("Captured Sobel X Frame", capturedSobelXFrame);
                    printf("Displaying captured Sobel X frame\n");
                    cv::waitKey(0);
                } else {
                    printf("Failed to read captured_sobelx_image.jpg\n");
                }
                displaySobelX = false;
            }
        } else if (sobelYMode) {
            // Apply Sobel Y filter
            sobelY3x3(frame, sobelYFrame);

            // Show the absolute value of Sobel Y output
            cv::Mat absSobelY;
            cv::convertScaleAbs(sobelYFrame, absSobelY);
            cv::imshow("Sobel Y Frame", absSobelY);

            if (saveSobelY) {
                // Save Sobel Y frame as an image file
                cv::imwrite("captured_sobely_image.jpg", absSobelY);
                printf("Sobel Y Image saved as captured_sobely_image.jpg\n");
                saveSobelY = false;
            }

            if (displaySobelY) {
                // Display the saved Sobel Y frame
                cv::Mat capturedSobelYFrame = cv::imread("captured_sobely_image.jpg");
                if (!capturedSobelYFrame.empty()) {
                    cv::imshow("Captured Sobel Y Frame", capturedSobelYFrame);
                    printf("Displaying captured Sobel Y frame\n");
                    cv::waitKey(0);
                } else {
                    printf("Failed to read captured_sobely_image.jpg\n");
                }

                displaySobelY = false;
            }
        }else if (key == 'm') {
            cv::Mat magFrame;
            cv::Mat displayFrame;
            cv::Mat sobelX;
            cv::Mat sobelY;
            // use previous functions to calculate maginitude
            sobelX3x3(frame, sobelX);
            sobelY3x3(frame, sobelY);
            // call mag function to filter image
            magnitude(sobelX, sobelY, magFrame);
            // convert negative values to positive for display purposes
            cv::convertScaleAbs(magFrame, displayFrame);
            cv::imshow("magintude", displayFrame);
            frame = displayFrame;
            cv::imwrite("captured_gradientmagnitude_image.jpg", displayFrame);
            printf("Quantized Image saved as captured_gradientmagnitude_image.jpg\n");
            //checker = 'm';
        }else if (key == 'l') {
        // Display and save the quantized frame
            blurQuantize(frame, quantizedFrame, 10); // You can adjust the number of levels as needed

        // Save the quantized frame as an image file
            cv::imwrite("captured_quantized_image.jpg", quantizedFrame);
            printf("Quantized Image saved as captured_quantized_image.jpg\n");

        // Display the quantized frame
            cv::imshow("Quantized Frame", quantizedFrame);
            printf("Displaying quantized frame\n");
            cv::waitKey(0); // Wait until any key is pressed before continuing

        } else if (key == 'v') {
            // Apply sepia filter to the current frame
            sepiaToneFilterWithVignetting(frame, sepiafilteredFrame);
        } else if (key == 'V' && !sepiafilteredFrame.empty()) {
            // 'i' - Save the sepia frame as an image file
            cv::imwrite("captured_sepia_vignetting_image.jpg", sepiafilteredFrame);
            printf("Sepia Image saved as captured_sepia_vignetting_image.jpg\n");
        } else if (key == 'Z' && !sepiafilteredFrame.empty()) {
            // 'z' - Display the sepia frame when 'z' is pressed
            cv::imshow("Sepia vignetting Frame", sepiafilteredFrame);
            printf("Displaying sepia vignetting frame\n");
        }else if (key == 'c'){
            // initilize parameters
            cv::Mat cartoonFrame;
            cv::Mat displayFrame;

            // cartoon(src, dest, levels, magThreadhold);
            // call cartoon function to filter image
            cartoon(frame, cartoonFrame, 10, 50000);
            cv::imshow("Cartooning", cartoonFrame);
            cv::imwrite("captured_cartoon_image.jpg", cartoonFrame);
            printf("Sepia Image saved as captured_cartoon_image.jpg\n");
            frame = cartoonFrame;
        }else if (key == 'a'|| brightness == 'a'){
            // initilize parameters
            cv::Mat outputImage;
            double alpha = 1.1;  //  brightness factor
            int beta = 100;       // contrast adjustment
            // call brightness function to filter image
            BrightnessContrast(frame, outputImage, alpha, beta);
            cv::imshow("brightnessmode", outputImage);
            brightness = 'a';
    
        }else if (key == 'j'|| face == 'j'){
            // initilize parameters
            cv::Mat grey;
            cv::cvtColor(frame, grey, cv::COLOR_BGR2GRAY,0);
            // detect faces
            detectFaces(grey, faces);
            // draw boxes around the faces
            printf("Number of Faces: %zu\n", faces.size());
            drawBoxes(frame, faces);

            // add a little smoothing by averaging the last two detections
            if( faces.size() > 0 ) {
                last.x = (faces[0].x + last.x)/2;
                last.y = (faces[0].y + last.y)/2;
                last.width = (faces[0].width + last.width)/2;
                last.height = (faces[0].height + last.height)/2;
            }
            printf("print");
            cv::imshow("Video", frame);
            face = 'j';
        }else if (key == '8') {
            cv::Mat embossFrame;
            // Apply emboss filter to the current frame
            embossFilter(frame, embossFrame);

            // Show the emboss filtered frame
            cv::imshow("Emboss Frame", embossFrame);

            // Save emboss filtered frame as an image file
            cv::imwrite("captured_emboss_image.jpg", embossFrame);
            printf("Emboss Image saved as captured_emboss_image.jpg\n");
        }else if (key == '6' || recording == '6') {
            printf("Start recording\n");
            cv::Mat outputFrame;
            if (sobelXMode) {
                // Apply Sobel X filter
                sobelX3x3(frame, outputFrame);
            } else if (sobelYMode) {
                // Apply Sobel Y filter
                sobelY3x3(frame, outputFrame);
            }else if (grayscaleMode){
                greyscale(frame, outputFrame);
            } else {
                outputFrame = frame;
            }
            if (outputFrame.size() != refS) {
            cv::resize(outputFrame, outputFrame, refS);
            }
            record.write(outputFrame);
            cv::imshow("Video", outputFrame);
            recording = '6';
            if(key == '5') {
            printf("Stop recording\n");
            record.release();
            recording = '\0';
        }
    }
    }

    delete capdev;
    return 0;
}
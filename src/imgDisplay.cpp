#include <stdio.h>
#include <cstring>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "filter.h" // Filter header file

int main(int argc, char *argv[]) {
    
    cv::Mat src; // Image data type
    char filename[256];
    const char* outputFolder = "C:/Users/shrut/OneDrive/Desktop/PROJECT1/build/Debug/Still Images/"; // Folder to save the images

    // Check if Enough Command Line Arguments
    if (argc < 2) {
        printf("usage: %s <image filename\n", argv[0]);
        exit(-1);
    }

    strcpy(filename, argv[1]);
    
    
    // Reading the image
    src = cv::imread(filename); // Allocates image data, reads as a BGR 8-bit per channel image

    // Test if the image read is successful
    if (src.data == NULL) { // Checking to see if there is no image present
        printf("error: unable to open the image %s\n", filename);
        exit(-1);
    }
    
    // Gives properties of the image
    // Successfully read an image file
    printf("Image size:    %d rows %d columns \n", src.rows, src.cols);
    // src.rows, src.cols also work for height (rows) and width (cols)
    printf("Number of channels: %d\n", (int)src.channels());
    printf("Bytes per channel: %d\n", (int)src.elemSize() / src.channels());

    cv::namedWindow(filename, 1);
    cv::setWindowProperty(filename, cv::WND_PROP_FULLSCREEN, cv::WND_PROP_FULLSCREEN);

    cv::imshow(filename, src);

    
    // Enter a loop, checking for keypress
    while (true) {
        int key = cv::waitKey(0);

        // Check for different keypresses
        if (key == 'q' || key == 'Q') {
            break; // Quit the program if 'q' is pressed
        } else if (key == 27)  {
            //printf("Escape key: Quitting the program\n");
            //break;             
            
        } else if (key == 'f') {
            // Apply sepia filter to the current frame
            cv::Mat sepiaFrame;
            sepiaToneFilter(src, sepiaFrame);

            // Save the sepia frame without captions
            std::string sepiaFilename = std::string(outputFolder) + "sepia_frame.jpg";
            cv::imwrite(sepiaFilename, sepiaFrame);
            printf("Saved sepia frame as: %s\n", sepiaFilename.c_str());

            // Display the sepia frame without captions
            cv::imshow("Sepia Frame", sepiaFrame);

            // Add captions to the sepia frame
            addCaption(sepiaFrame, "Captions for Sepia Frame !");

            // Display the sepia frame with captions
            cv::imshow("Captioned Sepia Frame", sepiaFrame);

            // Save the captioned sepia frame
            std::string captionedSepiaFilename = std::string(outputFolder) + "captioned_sepia_frame.jpg";
            cv::imwrite(captionedSepiaFilename, sepiaFrame);
            printf("Saved captioned sepia frame as: %s\n", captionedSepiaFilename.c_str());
        
        } else if (key == 'l') {
            // Apply blur and quantize filter
            cv::Mat blurQuantizedFrame;
            blurQuantize(src, blurQuantizedFrame, 10); // Adjusting the blur quantization levels
            //Display blurred frame
            cv::imshow("Blur Quantized Frame", blurQuantizedFrame);

            // Save the blur quantized frame
            std::string blurQuantizedFilename = std::string(outputFolder) + "blur_quantized_frame.jpg";
            cv::imwrite(blurQuantizedFilename, blurQuantizedFrame);
            printf("Saved blur quantized frame as: %s\n", blurQuantizedFilename.c_str());

            // Add captions to the sepia frame
            addCaption(blurQuantizedFrame, "Captions for Blur Quantized Frame !");

            // Display the sepia frame with captions
            cv::imshow("Captioned Blur Quantized Frame", blurQuantizedFrame);

            // Save the captioned sepia frame
            // Save the captioned blur quantized frame
            std::string captionedBlurQuantizedFilename = std::string(outputFolder) + "captioned_blurquant_frame.jpg";
            cv::imwrite(captionedBlurQuantizedFilename, blurQuantizedFrame);
            printf("Saved captioned blur quantized frame as: %s\n", captionedBlurQuantizedFilename.c_str());

            
        } else if (key == 'v') {
            // Apply sepia filter with vignetting
            // By applying vignetting we aim to darken the corners and edges of the image
            cv::Mat sepiaVignettingFrame;
            sepiaToneFilterWithVignetting(src, sepiaVignettingFrame);
            // Display the Sepia image after applying vignetting
            cv::imshow("Sepia Vignetting Frame", sepiaVignettingFrame);

            // Save the sepia vignetting frame
            std::string sepiaVignettingFilename = std::string(outputFolder) + "sepia_vignetting_frame.jpg";
            cv::imwrite(sepiaVignettingFilename, sepiaVignettingFrame);
            printf("Saved sepia vignetting frame as: %s\n", sepiaVignettingFilename.c_str());

            // Add captions to the sepia vignetting frame
            addCaption(sepiaVignettingFrame, "Captions for Sepia Vignetting Frame !");

            // Display the sepia Vignetting frame with captions
            cv::imshow("Captioned Sepia Vignetting Frame", sepiaVignettingFrame);

            
            // Save the captioned sepia vignetting frame
            std::string captionedsepiavignettingFilename = std::string(outputFolder) + "captioned_sepiavignette_frame.jpg";
            cv::imwrite(captionedsepiavignettingFilename, sepiaVignettingFrame);
            printf("Saved captioned Sepia vignetting frame as: %s\n", captionedsepiavignettingFilename.c_str());

        } else if (key == 'g') {
            // Convert the image to grayscale
            cv::Mat grayscaleFrame;
            greyscale(src, grayscaleFrame);
            //Display greyscale frame
            cv::imshow("Grayscale Frame", grayscaleFrame);

            // Save the grayscale frame
            std::string grayscaleFilename = std::string(outputFolder) + "grayscale_frame.jpg";
            cv::imwrite(grayscaleFilename, grayscaleFrame);
            printf("Saved grayscale frame as: %s\n", grayscaleFilename.c_str());

            // Add captions to the grayscale frame
            addCaption(grayscaleFrame, "Captions for Gray Scale Frame !");

            // Display the grayscale frame with captions
            cv::imshow("Captioned Grayscale Frame", grayscaleFrame);

            
            // Save the captioned grayscale frame
            std::string captionedsgrayscaleFilename = std::string(outputFolder) + "captioned_blurquant_frame.jpg";
            cv::imwrite(captionedsgrayscaleFilename, grayscaleFrame);
            printf("Saved captioned Sepia vignetting frame as: %s\n", captionedsgrayscaleFilename.c_str());

        } else if (key == '1') {
            // Apply blur 1
            cv::Mat blurFrame1;
            blur5x5_1(src, blurFrame1);
            cv::imshow("Blur Frame 1", blurFrame1);

            // Save blur frame 1
            std::string blurFrame1Filename = std::string(outputFolder) + "blur_frame1.jpg";
            cv::imwrite(blurFrame1Filename, blurFrame1);
            printf("Saved blur frame 1 as: %s\n", blurFrame1Filename.c_str());
        } else if (key == '2') {
            // Apply blur 2
            cv::Mat blurFrame2;
            blur5x5_2(src, blurFrame2);
            cv::imshow("Blur Frame 2", blurFrame2);

            // Save blur frame 2
            std::string blurFrame2Filename = std::string(outputFolder) + "blur_frame2.jpg";
            cv::imwrite(blurFrame2Filename, blurFrame2);
            printf("Saved blur frame 2 as: %s\n", blurFrame2Filename.c_str());
        } else if (key == 'x') {
            // Apply Sobel X
            cv::Mat sobelXFrame;
            cv::Sobel(src, sobelXFrame, CV_16S, 1, 0);
            cv::convertScaleAbs(sobelXFrame, sobelXFrame);
            cv::imshow("Sobel X Frame", sobelXFrame);

            // Save the Sobel X frame
            std::string sobelXFilename = std::string(outputFolder) + "sobel_x_frame.jpg";
            cv::imwrite(sobelXFilename, sobelXFrame);
            printf("Saved Sobel X frame as: %s\n", sobelXFilename.c_str());
        } else if (key == 'y') {
            // Apply Sobel Y
            cv::Mat sobelYFrame;
            cv::Sobel(src, sobelYFrame, CV_16S, 0, 1);
            cv::convertScaleAbs(sobelYFrame, sobelYFrame);
            cv::imshow("Sobel Y Frame", sobelYFrame);

            // Save the Sobel Y frame
            std::string sobelYFilename = std::string(outputFolder) + "sobel_y_frame.jpg";
            cv::imwrite(sobelYFilename, sobelYFrame);
            printf("Saved Sobel Y frame as: %s\n", sobelYFilename.c_str());
        } else if (key == 'm') {
            // Calculate gradient magnitude
            cv::Mat sobelXFrame, sobelYFrame;
            cv::Mat gradientMagnitudeFrame;
            cv::Sobel(src, sobelXFrame, CV_16S, 1, 0);
            cv::Sobel(src, sobelYFrame, CV_16S, 0, 1);
            magnitude(sobelXFrame, sobelYFrame, gradientMagnitudeFrame);
            cv::imshow("Gradient Magnitude Frame", gradientMagnitudeFrame);

            // Save the Gradient Magnitude frame
            std::string gradientMagnitudeFilename = std::string(outputFolder) + "gradient_magnitude_frame.jpg";
            cv::imwrite(gradientMagnitudeFilename, gradientMagnitudeFrame);
            printf("Saved Gradient Magnitude frame as: %s\n", gradientMagnitudeFilename.c_str());
        } else if (key == 'c') {
            cv::Mat cartoonFrame;
            cartoon(src, cartoonFrame, 10, 100);
            
            cv::imshow("Cartoon Frame", cartoonFrame);

            // Save the Cartoon frame
            std::string cartoonFilename = std::string(outputFolder) + "cartoon_frame.jpg";
            cv::imwrite(cartoonFilename, cartoonFrame);
            printf("Saved Cartoon frame as: %s\n", cartoonFilename.c_str());

            // Add captions to the cartoon frame
            addCaption(cartoonFrame, "Captions for Cartoon Frame !");

            // Display the cartooning frame with captions
            cv::imshow("Captioned Cartoon Frame", cartoonFrame);
            
            // Save the captioned cartooning frame
            std::string captionedCartoonFilename = std::string(outputFolder) + "captioned_cartoon_frame.jpg";
            cv::imwrite(captionedCartoonFilename, cartoonFrame);
            printf("Saved captioned cartoon frame as: %s\n", captionedCartoonFilename.c_str());

        }
    }

    cv::destroyWindow(filename);

    return 0;
}

# RealTimeImageVideoFiltering

## Description
Real Time Image Video Filtering is a comprehensive C/C++ application that utilizes OpenCV for real-time image and video processing and filtering. This project is designed to showcase various techniques for manipulating and transforming images and video streams in real-time. The focus is not just on applying predefined filters but also on creating custom extensions to delve deeper into the concepts of image and video processing.

## Installation

OpenCV

C++ Compiler (Visual Studio)

Visual Studio Code (IDE)

MinGW

## Tasks Completed:

1. **Read an image from a file and display it** : Created an **imgDisplay.cpp** file that reads an image file and displays it in a window using OpenCV

2. **Displaying & Capturing Live video** :Created a vidDisplay.cpp to open a video channel, create a display window, and loop through capturing and displaying frames in real-time using OpenCV. Also used certain keystrokes to quit the program or save a frame to a file.

3. **Update to display greyscale video** : Enhanced the vidDisplay.cpp application to support toggling between color and greyscale video display modes in real-time. Stored the last keypress and applied the corresponding image conversion for each frame

4. **Creating filter.cpp** : Created a filter.cpp file to define the video manipulation functions that will be used to apply various filters, including a custom greyscale filter, to live video streams.

5. **Create a filter.h header file** :Created a header file to declare the functions defined in filter.cpp. This allows the functions to be invoked from any other .cpp file in the project, facilitating modular programming and code reuse.

6. **Create a CMake file** : Prepared a CMake file for building the video manipulation application. This includes compiling filter.cpp, linking against OpenCV libraries, and generating an executable.

7. **Implementing a greyscale filter** : Developed a greyscale filter using OpenCV's `cvtColor` function to transform live video stream frames from color to grayscale in real-time, highlighting the transition of pixel brightness levels from black (lowest intensity) to white (highest intensity).
  
8. **Implementing a alternate greyscale filter** : Unlike using the usual 'cvtColor' function implemented an alternate greyscale filter that inverts the green channel of 
each pixel and applies this value across all three color channels (red, green, blue) for a greyscale effect

9. **Implementing a sepia tone filter** : Implemented a sepia tone filter for live video streams by manipulating the RGB color channels based on predetermined coefficients to create a vintage sepia effect.

   Coefficients:

   0.272, 0.534, 0.131    // Blue coefficients for R, G, B  

   0.349, 0.686, 0.168    // Green coefficients

   0.393, 0.769, 0.189    // Red coefficients

10.**Implement a 5x5 blur filter** : Writing a function blur5x5_1(cv::Mat &src, cv::Mat &dst) that implements a naive 5x5 Gaussian blur using the integer approximation matrix. This function should handle each color channel separately, ensuring the output image (dst) is a blurred version of the input (src), with untouched outer two rows and columns.

11.**Optimized 5x5 blur filter** : Developed a faster version of the blur filter, blur5x5_2(cv::Mat &src, cv::Mat &dst), by employing optimizations such as separable 1x5 filters for both vertical and horizontal passes. Avoid direct pixel access methods like at to enhance performance.

12.**Develop Sobel X Filter**: Created a function sobelX3x3(cv::Mat &src, cv::Mat &dst) to apply a 3x3 Sobel filter focusing on horizontal gradients, accentuating vertical edges. The filter direction should be positive to the right.

13.**Develop Sobel Y Filter**: Writing a function sobelY3x3(cv::Mat &src, cv::Mat &dst) for applying a 3x3 Sobel filter that captures vertical gradients, emphasizing horizontal edges. The filter direction should be positive upwards.

14.**Computing gradient magnitude**: Created a function to calculate the gradient magnitude of an image using the Euclidean distance formula on the Sobel X and Y filter outputs. This process emphasizes the intensity of edges, regardless of their orientation

15.**Blur and Quantize Color Image** : Developed a function that blurs a color image and then quantizes it into a fixed number of levels per color channel, resulting in a visually distinct image with reduced color complexity

16.**Implementing a Cartoonization filter**: Developed a cartoonization filter that simplifies an image's color , enhances edges, and reduces fine details to create a whimsical, exaggerated representation similar to a cartoon. 

17.**Achieving Face Detection , Applying Emboss Filter & Adjusting Brightness & Contrast** : Performing face detection to identify and frame faces with boxes for easy recognition, and an emboss filter to give images a textured, three-dimensional effect by highlighting edges and contours.



## EXTENSIONS IMPLEMENTED

**Sepia Filter with Vignetting** : Combined a warm sepia tone with a vignetting effect to darken the image edges and draw attention to the center, creating a focal point that enhances the visual appeal of your images.

**Sobel X and Y Short Video Sequence**: Implemented a functionality to capture video sequences that highlight the effectiveness of Sobel X and Y filters in real-time. This feature, activated by keypresses, demonstrates edge detection capabilities vividly, especially against structured backgrounds like grid lines on paper.

**Applying Filters to Still Images**: Extended the project by integrating filter.cpp with imgDisplay.cpp, allowing for easy application of various filters—grayscale, sepia, blur quantization, and more—to still images. This integration facilitates the exploration and demonstration of filter effects on static content.

**Image Captioning Feature:** Introduced an addCaption function to overlay captions onto images, offering a way to annotate and highlight key aspects or effects applied. Customize text appearance with font settings and ensure captions are centered, enhancing the informational value of your processed images.

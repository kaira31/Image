## Image-Video Filtering Effects

## Overview
Real Time Image Video Filtering is a powerful C/C++ application leveraging OpenCV for real-time image and video processing and filtering. This project provides a comprehensive platform to explore various techniques for manipulating and transforming images and video streams in real-time, going beyond simple filter application to delve deeper into the realm of computer vision.

## Installation
To get started with Real Time Image Video Filtering, you'll need:

OpenCV: OpenCV library for image and video processing.
C++ Compiler: You can use Visual Studio or any other C++ compiler.
Integrated Development Environment (IDE): Visual Studio Code is recommended.
MinGW: If you're on Windows, you'll need MinGW for compiling.

## Features 

**Image Display:**
Created imgDisplay.cpp to facilitate the display of images from files.
Utilized OpenCV to read image files and display them in a window.
Implemented error handling for file loading and display operations.

**Live Video Display & Capture:**
Developed vidDisplay.cpp to handle live video display and capture functionality.
Initialized video capture from the default camera device.
Created a window to display the live video stream.
Implemented a loop to continuously capture frames and display them in real-time.
Integrated keystroke functionality to allow users to quit the program or save frames to files.

**Greyscale Video Display:**
Enhanced vidDisplay.cpp to support toggling between color and greyscale video display modes.
Stored the last keypress to determine the current display mode.
Applied the corresponding image conversion to each frame based on the selected mode.

**Filter Functions:**
Developed filter.cpp to define functions for applying various filters to live video streams.
Implemented functions for custom greyscale and sepia filters.
Ensured compatibility with OpenCV for seamless integration into the project.

**Header File:**
Created filter.h to declare the filter functions defined in filter.cpp.
Provided function prototypes and necessary declarations for modular programming.
Facilitated code reuse and maintainability by separating declarations from implementations.

**CMake Configuration:**
Prepared a CMake file for building the video manipulation application.
Specified compilation of filter.cpp and linking against OpenCV libraries.
Configured generation of an executable for easy deployment and execution.
These tasks collectively form the foundation of the Real Time Image Video Filtering project, providing essential functionalities for image and video processing, filtering, and display in a real-time environment. Each task contributes to the project's overall functionality and showcases the capabilities of OpenCV for computer vision applications.

**Greyscale Filter:**
Implemented both traditional and alternate greyscale filters in filter.cpp.
Utilized OpenCV's cvtColor function for traditional greyscale conversion, providing a straightforward approach to transform color images to greyscale.
Developed an alternate greyscale filter within filter.cpp that inverted the green channel of each pixel and applied this value across all three color channels (red, green, blue) for a unique greyscale effect.

**Sepia Tone Filter:**
Introduced a sepia tone filter for live video streams within filter.cpp.
Implemented the sepia effect by manipulating RGB color channels based on predetermined coefficients, creating a vintage sepia effect reminiscent of old photographs.
Provided flexibility in adjusting the intensity of the sepia effect by fine-tuning the coefficients used for color channel manipulation.

**5x5 Blur Filter**:
Implemented both naive and optimized versions of a 5x5 Gaussian blur filter in filter.cpp.
Developed a naive implementation that applied the Gaussian blur directly using an integer approximation matrix.
Enhanced performance by implementing an optimized version of the blur filter, utilizing separable 1x5 filters for both vertical and horizontal passes, thereby reducing computational complexity.

**Sobel Filters:**
Created functions within filter.cpp to apply Sobel X and Y filters for detecting horizontal and vertical gradients in images.
Leveraged the Sobel operator to compute gradient magnitude, highlighting edges and contours in the image.
Provided users with the capability to detect edges in real-time video streams, enhancing the overall utility of the application for image analysis and processing tasks.

**Gradient Magnitude Calculation:**
Implemented a function within filter.cpp to calculate the gradient magnitude of an image using the Euclidean distance formula on the outputs of Sobel X and Y filters.
Emphasized the intensity of edges in the image, irrespective of their orientation, enabling users to identify and analyze prominent features in real-time video streams.

**Color Image Processing:**
Developed functionalities within filter.cpp to blur and quantize color images for reduced complexity.
Applied Gaussian blur to color images to smoothen transitions between color regions and reduce noise.
Quantized color images into a fixed number of levels per color channel, simplifying color complexity and enhancing visual clarity.

**Cartoonization Filter:**
Implemented a cartoonization filter within filter.cpp to simplify color, enhance edges, and reduce fine details, creating a whimsical, cartoon-like representation of images.
Applied a combination of edge detection, color simplification, and noise reduction techniques to achieve the cartoon effect.
Provided users with a creative tool for transforming images into cartoon-like renderings, adding a touch of whimsy to their projects.

**Face Detection & Emboss Filter:**
Developed functionalities within filter.cpp to perform face detection and apply emboss filters to images.
Leveraged OpenCV's built-in face detection algorithms to identify and frame faces within images and video streams.
Applied emboss filters to images to add texture and depth, highlighting edges and contours and providing a three-dimensional effect.

## Implemented Extensions

**Sepia Filter with Vignetting:**
Enhanced the project by combining a warm sepia tone with a vignetting effect.
This addition darkens the edges of images while drawing attention to the center, creating a focal point that enhances the visual appeal.

**Sobel X and Y Short Video Sequence:**
Introduced a feature to capture short video sequences that showcase the effectiveness of Sobel X and Y filters in real-time.
This functionality, activated by keypresses, vividly demonstrates edge detection capabilities, particularly against structured backgrounds like grid lines on paper.

**Applying Filters to Still Images:**
Extended the project by integrating the filter functionalities with the image display module (imgDisplay.cpp).
This integration allows for the easy application of various filters—such as grayscale, sepia, blur quantization, and more—to still images.
Users can explore and demonstrate filter effects on static content, enhancing the versatility and utility of the project.

**Image Captioning Feature:**
Introduced an image captioning feature, enabling users to overlay captions onto images.
The addCaption function facilitates annotation and highlights key aspects or effects applied to the images.
Users can customize text appearance with font settings and ensure captions are centered, enhancing the informational value of processed images.












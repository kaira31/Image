# RealTimeImageVideoFiltering

## Overview
RealTime Image Video Filtering is an advanced application built using C/C++ and OpenCV, designed for real-time manipulation of images and video streams. This project demonstrates a variety of image and video processing techniques, from applying standard filters to developing custom solutions that extend the capabilities of OpenCV.

# Setup
# Requirements 
OpenCV
C++ Compiler (Visual Studio recommended)
Visual Studio Code (IDE)
MinGW
Installation Instructions
Clone the repository and install the required tools to set up the environment. Ensure OpenCV is linked correctly with your C++ IDE for smooth operation.

# Features
# Image Processing
Image Display: Utilize imgDisplay.cpp to load and display images using OpenCV.
Custom Filters: filter.cpp includes functions to apply custom filters like greyscale, sepia, and more.
# Video Processing
Live Video Handling: Capture and display live video streams with options to save snapshots using vidDisplay.cpp.
Greyscale & Sepia Tones: Toggle video streams between color and greyscale; apply a vintage sepia tone in real-time.
# Advanced Filtering
5x5 Gaussian Blur: Implement both naive and optimized versions of the Gaussian blur to enhance image smoothness.
Sobel Filters: Apply Sobel filters to detect horizontal and vertical edges distinctly.
Cartoonization: Transform images into cartoon-style visuals by simplifying colors and enhancing edges.
# Performance Benchmarks
Conduct benchmarks against other solutions like MediaPipe Pose, focusing on efficiency in single-pose scenarios.
# Additional Extensions
Sepia Filter with Vignetting: Enhance images with a sepia filter complemented by a vignette effect to focus attention.
Dynamic Captioning: Implement addCaption to overlay customizable text on images, useful for annotations.
# Usage
The project is structured to facilitate easy testing and expansion:

**Filters Application:** Integrate various filters with image and video processing tasks using modular .cpp files.
**Performance Analysis:** Utilize the included CMake file to compile and run performance tests.
# Contributions
Contributions are welcome! Please fork the project, make your improvements, and submit a pull request.

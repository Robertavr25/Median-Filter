# Median-Filter
Median Filter for PGM Images  This program applies a Median Filter on a Portable GrayMap (PGM) image using either the Bubble Sort or Merge Sort algorithm to sort the pixel values within a specified filter window. The filtered image is then saved to a new file.
Features:
Supports PGM files in ASCII format (P2).
Implements two sorting algorithms:
Bubble Sort (simpler, slower).
Merge Sort (more efficient, faster for larger inputs).
Reads an input image, applies a median filter, and writes the filtered image to an output file.
Handles edge cases by replicating boundary pixels where the filter window overlaps the edges.
How It Works
Input Image: A PGM image file in ASCII format is read.
Median Filter: A window of specified dimensions slides across the image, and the median pixel value within the window is calculated.
Output Image: A new PGM image is written with the filtered pixel values.
How to Compile:
Use any C++ compiler (e.g., g++) to compile the program:

	g++ -o MedianFilter main.cpp
How to Run:
Run the program with the following inputs:

	Sorting Algorithm (bubble or merge).
	Window Dimension (an odd integer for the filter window size, e.g., 3).
	Input PGM File Name.
	Output PGM File Name.
Example:

./MedianFilter bubble 3 input.pgm output.pgm
Input File Format:
The input file should be in the PGM format (P2), for example:

P2
// Comment line
5 5
255
10 20 30 40 50
60 70 80 90 100
110 120 130 140 150
160 170 180 190 200
210 220 230 240 250
Breakdown:
P2: ASCII grayscale image.
5 5: Width and height.
255: Maximum grayscale value.
Grayscale values for the image pixels.
Output File Format:
The output will be saved in the same format as the input:

P2
5 5
255
...
Code Overview
Key Functions:
readPGM: Reads a PGM file into a 2D vector.
writePGM: Writes a 2D vector as a PGM file.
bubbleSort: Sorts a vector of pixel values using Bubble Sort.
mergeSort: Sorts a vector of pixel values using Merge Sort.
MedianFilter: Applies a median filter using the selected sorting algorithm.
Median Filter Logic:
Extracts a pixel window around the target pixel.
Sorts the window using the chosen algorithm.
Replaces the target pixel with the median value from the sorted window.
Limitations
Supports only PGM files in ASCII format (P2).
The filter window size must be an odd integer.
Sorting large pixel windows with Bubble Sort may be slow; prefer Merge Sort for better performance.

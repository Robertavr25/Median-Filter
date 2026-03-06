#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <stdint.h>
#include <istream>
#include <ostream>

using namespace std;

//BubbleSort Algorithm
void bubbleSort(vector<uint8_t> &vec){
    for (auto i = 0; i < vec.size(); ++i) {
        for (auto j = 0; j < vec.size() - i - 1; ++j) {
            if(vec[j] > vec[j + 1])
                swap(vec[j],vec[j+1]);
        }
    }
}


//MergeSort Algorithm
void merge(vector<uint8_t>& vec, int left, int mid, int right) {
    vector<uint8_t> leftVec(vec.begin() + left, vec.begin() + mid + 1);
    vector<uint8_t> rightVec(vec.begin() + mid + 1, vec.begin() + right + 1);

    size_t i = 0, j = 0, k = left;
    while (i < leftVec.size() && j < rightVec.size()) {
        if (leftVec[i] <= rightVec[j]) {
            vec[k++] = leftVec[i++];
        } else {
            vec[k++] = rightVec[j++];
        }
    }

    while (i < leftVec.size()){
        vec[k++] = leftVec[i++];
    }
    while (j < rightVec.size()){
        vec[k++] = rightVec[j++];
    }
}

void mergeSort(vector<uint8_t>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

//Finding which pixel to place
uint8_t getPixelValue(const vector<vector<uint8_t>>& image, int x, int y, int width, int height) {
    x = max(0, min(x, width - 1));
    y = max(0, min(y, height - 1));
    return image[y][x];
}

//Reading the input file
void readPGM(const char* fileName, vector<vector<uint8_t>>& image, int& width, int& height, int& maxVal) {
    ifstream file(fileName);

    string line;
    getline(file, line);

    while (getline(file, line) && line[0] == '#');

    stringstream ss(line);
    ss >> width >> height;
    file >> maxVal;

    image.resize(height, vector<uint8_t>(width));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int pixel;
            file >> pixel;
            image[i][j] = static_cast<uint8_t>(pixel);
        }
    }

    file.close();
}

//Writing the output file
void writePGM(const char* fileName, const vector<vector<uint8_t>>& image, int width, int height, int maxVal) {
    ofstream file(fileName);

    file << "P2" << endl;
    file << width << " " << height << endl;
    file << maxVal << endl;

    for (const auto& row : image) {
        for (const auto& pixel : row) {
            file << static_cast<int>(pixel) << " ";
        }
        file << endl;
    }

    file.close();
}

//Applying the Median Filter on the input file
void MedianFilter(vector<vector<uint8_t>>& image, vector<vector<uint8_t>>& output, int width, int height, int windowDim, const char* alg) {
    int offset = windowDim / 2;
    output = image;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            vector<uint8_t> window;

            for (int y1 = -offset; y1 <= offset; ++y1) {
                for (int x1 = -offset; x1 <= offset; ++x1) {
                    window.push_back(getPixelValue(image, x + x1, y + y1, width, height));
                }
            }

            if (strcmp(alg, "bubble") == 0) {
                bubbleSort(window);
            } else if (strcmp(alg, "merge") == 0) {
                mergeSort(window, 0, window.size() - 1);
            }

            output[y][x] = window[window.size() / 2];
        }
    }
}

int main() {
    char alg[255], inputName[255], outputName[255];
    int windowDim;
    cin >> alg >> windowDim >> inputName >> outputName;

    ifstream inputFile(inputName);
    ofstream outputFile(outputName);

    vector<vector<uint8_t>> image, filteredImage;
    int width, height, maxVal;

    readPGM(inputName, image, width, height, maxVal);
    MedianFilter(image, filteredImage, width, height, windowDim, alg);
    writePGM(outputName, filteredImage, width, height, maxVal);
    return 0;

}

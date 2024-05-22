#include "data_handler.h"
#include <opencv2/opencv.hpp>
#include <iostream> 
#include <vector> 
// #include <omp.h>


DataLoader::DataLoader(std::string path) {
    this->path = path; 
}


int DataLoader::load_raw_video() {
    this->cap.open(this->path);
    if(!cap.isOpened()) {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }
    return 0;
}   


void DataLoader::process_frames() { 
    cv::Mat frame; 
    int frame_count = 0;
    while(this->cap.read(frame)) {
        cv::Mat processed_frame = process_single_frame(frame);
        this->processed_frames.push_back(processed_frame);
        
        // Output result
        std::string save_to = SAVE_PROCESSED_FRAMES_PATH + "preprocessed_frame_" + std::to_string(frame_count++) + ".png";
        cv::imwrite(save_to, processed_frame);

    }
}


cv::Mat DataLoader::process_single_frame(cv::Mat& frame) {
    cv::Mat gray, blurred, binary, morph, kernel, edges;

    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);
    cv::adaptiveThreshold(blurred, binary, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY_INV, 11, 2);
    return binary;
}

#ifndef DATA_HANDLER_H 
#define DATA_HANDLER_H

#include <opencv2/opencv.hpp> 
#include <stdlib.h>
#include <vector>
#include <filesystem> 

const std::string SAVE_PROCESSED_FRAMES_PATH = std::__fs::filesystem::path(__FILE__).parent_path() / "processed_frames/";

class DataLoader {
    public: 
        // Class attributes
        cv::VideoCapture cap;
        std::vector<cv::Mat> processed_frames;
        std::string path;

        DataLoader(std::string path);

        int load_raw_video();
        void process_frames();
        cv::Mat process_single_frame(cv::Mat& frame);
};

#endif
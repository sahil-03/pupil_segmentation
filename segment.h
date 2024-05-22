#ifndef SEGMENT_H 
#define SEGMENT_H

#include <opencv2/opencv.hpp>
#include <stdio.h> 
#include <vector> 
#include <filesystem> 

const std::string SAVE_ANNOTATED_FRAMES_PATH = std::__fs::filesystem::path(__FILE__).parent_path() / "annotated_frames/";
const std::string SAVE_PUPIL_DATA_PATH = std::__fs::filesystem::path(__FILE__).parent_path() / "data/eye_tracking_pupil_coordinates.csv";

class Segment {
    public: 
        // Class attributes
        std::vector<std::pair<cv::Point, double>> pupil_coordinates;

        Segment(); 

        void segment_pupil_frames(std::vector<cv::Mat>& processed_frames);
        std::pair<cv::Point, double> find_pupil_coordinates(cv::Mat& frame);
        void save_pupil_coordinates();
        void annotate_pupil_on_frame(std::vector<cv::Mat>& processed_frames, int num_frames);

};

#endif 
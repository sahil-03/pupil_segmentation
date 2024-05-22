#include "segment.h"
#include <opencv2/opencv.hpp> 
#include <iostream>
#include <fstream>
#include <stdio.h> 
#include <vector> 
// #include <omp.h>


Segment::Segment() {
    // Default constructor
}


void Segment::segment_pupil_frames(std::vector<cv::Mat>& processed_frames) {
    this->pupil_coordinates.resize(processed_frames.size());
    for (int i = 0; i < processed_frames.size(); ++i) {
        this->pupil_coordinates[i] = this->find_pupil_coordinates(processed_frames[i]);
    }
}


std::pair<cv::Point, double> Segment::find_pupil_coordinates(cv::Mat& frame) {
    cv::Mat threshold; 
    cv::threshold(frame, threshold, 50, 255, cv::THRESH_BINARY_INV);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(threshold, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    if (!contours.empty()) {
        auto largestContour = *std::max_element(contours.begin(), contours.end(), [](const std::vector<cv::Point>& a, const std::vector<cv::Point>& b) {
            return cv::contourArea(a) < cv::contourArea(b);
        });

        cv::Moments M = cv::moments(largestContour);
        if (M.m00 != 0) {
            cv::Point centroid(static_cast<int>(M.m10 / M.m00), static_cast<int>(M.m01 / M.m00));
            double fitQuality = cv::contourArea(largestContour) / (frame.rows * frame.cols);
            return std::make_pair(centroid, fitQuality);
        }
    }
    return std::make_pair(cv::Point(-1, -1), 0.0);
}


void Segment::save_pupil_coordinates() {
    std::ofstream file(SAVE_PUPIL_DATA_PATH);
    file << "frame_no,x,y,fit_quality\n";
    for (int i = 0; i < this->pupil_coordinates.size(); i++) {
        std::pair<cv::Point, double> coordinate = this->pupil_coordinates[i];
        file << i << "," << coordinate.first.x << "," << coordinate.first.y << "," << coordinate.second << "\n";
    }
    file.close();
}


void Segment::annotate_pupil_on_frame(std::vector<cv::Mat>& processed_frames, int num_frames) {
    // Correct if num_frames > processed_frames.size()
    num_frames = std::min(num_frames, static_cast<int>(processed_frames.size()));
    for (int i = 0; i < num_frames; i++) {
        cv::Mat frame = processed_frames[i];
        cv::Point& centroid = this->pupil_coordinates[i].first;

        if (centroid.x != -1 && centroid.y != -1) {
            cv::circle(frame, centroid, 20, cv::Scalar(255, 0, 0), -1);
            std::string text = "Frame: " + std::to_string(i) + " Pupil: (" + std::to_string(centroid.x) + ", " + std::to_string(centroid.y) + ")";
            cv::putText(frame, text, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);
        }

        std::string outputFilename = SAVE_ANNOTATED_FRAMES_PATH + "output_frame_" + std::to_string(i) + ".png";
        cv::imwrite(outputFilename, frame);
    }
}


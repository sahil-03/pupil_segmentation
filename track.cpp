#include "segment.h"
#include "data_handler.h"
#include <opencv2/opencv.hpp>
#include <iostream> 
#include <fstream> 
#include <stdio.h> 
#include <vector>
#include <filesystem>

/*
This is the main driver function for the pupil segmentation pipeline.
We create a DataLoader object that contains the path, raw video, and processed frames. 
We create a Segment object that segments the pupil and determines + saves pupil coordinates.
*/
int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Error: Please enter path to video file." << std::endl;
        return -1; 
    }

    // Create data loader object
    std::string path = argv[1];
    DataLoader data_loader(path);

    // Load video
    int load_status = data_loader.load_raw_video();
    if (load_status == 0) std::cout << "Load was successful." << std::endl;
    else std::cout << "Load was not successful." << std::endl;
    
    // Preprocess frames
    data_loader.process_frames();
    std::cout << "Completed processing " << data_loader.processed_frames.size() << " frames." << std::endl;  

    // Create segment object
    Segment segment; 

    // Segment pupil frames
    segment.segment_pupil_frames(data_loader.processed_frames);
    std::cout << "Computed coordinates for " << segment.pupil_coordinates.size() << " frames." << std::endl;

    // Save pupil coordinates (for data visualization)
    segment.save_pupil_coordinates();
    std::cout << "Saved pupil coordinates." << std::endl;

    // Draw coordinate on frame (for data visualization)
    segment.annotate_pupil_on_frame(data_loader.processed_frames, data_loader.processed_frames.size());
    std::cout << "Annotated pupil coordinates on frames." << std::endl;
}
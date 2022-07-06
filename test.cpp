#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/img_hash/img_hash_base.hpp>
#include <opencv2/img_hash/average_hash.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <fstream>
using namespace cv;
using namespace std;


int main()
{
    //open the video file for reading
    VideoCapture cap("TestCard.mp4"); 

    // if not success, exit program
    if (cap.isOpened() == false)  
    {
        cout << "Cannot open the video file" << endl;
        cin.get(); //wait for any key press
        return -1;
    }

    //Uncomment the following line if you want to start the video in the middle
    //cap.set(CAP_PROP_POS_MSEC, 300); 

    //get the frames rate of the video
    double fps = cap.get(CAP_PROP_FPS); 
    cout << "Frames per seconds : " << fps << endl;

    String window_name = "My First Video";

    namedWindow(window_name, WINDOW_NORMAL); //create a window
    int counter = 1;
    Mat preFrame, preFrameHash, currFrame, currFrameHash;
    preFrame = imread("template.bmp");
    fstream fs;
    fs.open("resultDiff.txt");
    Ptr <img_hash::AverageHash> hasher = img_hash::AverageHash::create();
    while (true)
    {       
        bool bSuccess = cap.read(currFrame); // read a new frame from video 
        // if(counter == 1)
        //     preFrame = currFrame.clone();

        //Breaking the while loop at the end of the video
        if (bSuccess == false) 
        {
            cout << "Found the end of the video" << endl;
            break;
        }

        //show the frame in the created window
        imshow(window_name, currFrame);

        int test;
               
        hasher->compute(preFrame,preFrameHash);
        hasher->compute(currFrame,currFrameHash);      
        
        double result = hasher->compare(preFrameHash, currFrameHash);

        fs << counter << " - " << result << (result < 3 ? " - catch the frame!": "")  << endl;

        if (result == 0)
        {

        }
        
        //imwrite("Frames/image_" + std::to_string(counter) + ".bmp" , currFrame);
        //wait for for 10 ms until any key is pressed.  
        //If the 'Esc' key is pressed, break the while loop.
        //If the any other key is pressed, continue the loop 
        //If any key is not pressed withing 10 ms, continue the loop
        if (waitKey(10) == 27)
        {
            cout << "Esc key is pressed by user. Stoppig the video" << endl;
            break;
        }
        counter++;
       //preFrame = currFrame.clone();

    }
    fs.close();
    return 0;
}
#include <iostream>

#include <opencv2/video.hpp> //CANVI FET PER ENTRADA SORTIDA V
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>
#include<dirent.h>
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void images(string dir_location, string name){

    String dirName = dir_location + name + "/";
    cout << dirName << endl;
    DIR *dir;
    dir = opendir(dirName.c_str());

    string imgName;
    struct dirent *ent;

    namedWindow("Viewer");

    if (dir != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            imgName= ent->d_name;
            //I found some . and .. files here so I reject them.
            if(imgName.compare(".")!= 0 && imgName.compare("..")!= 0)
            {
                //Image name
                string aux;
                aux.append(dirName);
                aux.append(imgName);
                cout << "IMG - " << imgName << endl;

                Mat image = imread(aux, -3); // A negative number means that I load the image as it is (16 bit)
                normalize(image, image, 0, 255, NORM_MINMAX, CV_8U);
                imshow("Viewer", image);
                int key = waitKey(0);
                if (key == 27) //Escape key breaks the loop, any other key takes the next image.
                {
                    break;
                }

            }
        }
        closedir (dir);

    } else {
        cout<<"not present"<<endl;
    }

}


int main(int argc, char *argv[])
{
    bool debug = false;

    if (debug)
        namedWindow("Viewer", WINDOW_NORMAL);


    String word = "depth"; //argv[1]; //Put the name of your folder, If yo want to load it as command line
    //parameter, uncoment the argv.

    images("", word); //The "" parameter is the folder path.

    return 0;
}


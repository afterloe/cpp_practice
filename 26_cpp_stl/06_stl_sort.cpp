#include <iostream>
#include <stdlib.h>

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void printfP(vector<Point2f> &);
void sortP(vector<Point2f> &, Size &);

int main()
{
    vector<Point2f> srcTri(4);
    srcTri.push_back(Point2f(715, 169));
    srcTri.push_back(Point2f(174, 210));
    srcTri.push_back(Point2f(227, 577));
    srcTri.push_back(Point2f(731, 495));
    printfP(srcTri);
    Size coordinate(1024, 768);
    sortP(srcTri, coordinate);
    printfP(srcTri);

    return EXIT_SUCCESS;
}

void printfP(vector<Point2f> &v)
{
    printf("========= vector ::: \n");
    for (vector<Point2f>::iterator it = v.begin(); it < v.end(); it++)
    {
        if (it->x == 0)
            continue;
        printf("x: %.f, y: %.f \n", it->x, it->y);
    }
    printf("\n");
}

void sortP(vector<Point2f> &v, Size &coordinate)
{
    Point2f *arr = (Point2f *)malloc(sizeof(Point2f) * 4);
    for (vector<Point2f>::iterator it = v.begin(); it < v.end(); it++)
    {
        if (it->x == 0)
        {
            continue;
        }
        if (it->x < coordinate.width / 2)
        {
            if (it->y > coordinate.height / 2)
            {
                arr[3] = *it;
            }
            else
            {
                arr[0] = *it;
            }
        }
        else
        {
            if (it->y > coordinate.height / 2)
            {
                arr[2] = *it;
            }
            else
            {
                arr[1] = *it;
            }
        }
    }

    v.clear();

    for (int idx = 0; idx < 4; idx++)
    {
        v.push_back(*arr);
        arr++;
    }
}
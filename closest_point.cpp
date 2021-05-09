/*
-------------------------
| - | X | - | - | - | - |
-------------------------
| - | - | - | O | - | - |
-------------------------
| O | - | - | - | - | - |
-------------------------
| - | O | - | - | - | - |
-------------------------
| - | - | - | - | O | - |
-------------------------
| - | - | - | - | - | - |
-------------------------
**find the closest points of O's to x position**
*/
#include "kdtree.hpp"
#include <opencv2/opencv.hpp>

typedef unsigned int uint;

/*==========================MAIN FUNCTION================================*/
int main()
{
    float X, Y;
    std::cout << "ENTER X VALUE ";
    std::cin >> X;
    std::cout << "ENTER Y VALUE ";
    std::cin >> Y;

    Point p(X,Y);
    std::cout << "your point is ==> ";
    p.printPoint();
    
    std::vector<Point> points;

    std::ifstream ifs("./points.txt");
    std::string line;

    //O( Nlog(N) )
    while(std::getline(ifs, line))//O(N)
    {
        std::string num_1;
        std::string num_2;
        bool before_comma = true;

        for(uint i=0; i<line.size(); i++)
        {
            if(line.at(i) == ',')
            {
                before_comma = false;
                continue;
            }
            if(before_comma)
                num_1.push_back(line.at(i));
            if(!before_comma)
                num_2.push_back(line.at(i));
        }

        float x = std::stof(num_1);
        float y = std::stof(num_2);
        points.push_back({x,y});
    }
    
    KdTree* tree(new KdTree());
    
    for(const auto& point : points)
    {
        tree->insert(point);
    }

    std::map<float, Point> dis_point = tree->search(p);
    
    std::cout << "the closest point to your point is ==> ";
    dis_point.begin()->second.printPoint();
    std::cout << "the distance from your point to the closest point is ==> "<< dis_point.begin()->first << std::endl;
    
    
    //visualize result using OpenCV
    cv::Mat img = cv::Mat::zeros(cv::Size(500, 500), CV_8UC3);    
     
    for(auto pt : points)
    {
        cv::circle(img, cv::Point2d(pt.get(0), (500-pt.get(1))), 3, cv::Scalar(0, 255, 255), -1);
    }
    cv::circle(img, cv::Point2d(p.get(0), (500-p.get(1))), 3, cv::Scalar(0, 255, 0), -1);
    
    float x_closest = dis_point.begin()->second.get(0);
    float y_closest = dis_point.begin()->second.get(1);
    
    cv::line(img, cv::Point2d(p.get(0), (500-p.get(1))), cv::Point2d(x_closest, (500-y_closest)), cv::Scalar(0, 0, 255), 1 );
    
    cv::imshow("visulaization of the result", img);
    cv::waitKey(0);
    
    return 0;
}

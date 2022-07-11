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
#include <kdtree.hpp>
#include <opencv2/opencv.hpp>
#include <cstring>
#include <rapidcsv.h>
#include <chrono>

#define WIDTH 500
#define HEIGHT 500

template<typename T>
void readTextFile(std::vector<Point<T>>& points, const std::string& filePath) {

    std::ifstream ifs(filePath);
        std::string line;
        
        while(std::getline(ifs, line)) {
            std::string num_1 = "";
            std::string num_2 = "";

            num_1 = line.substr(0, line.find(","));
            num_2 = line.substr(num_1.size()+1, line.find("\n"));

            double x, y;
            x = stod(num_1);
            y = stod(num_2);
            points.push_back({x,y});
        }
}

template<typename T>
void readCsvFile(const std::string& filePath, std::vector<Point<T>>& points = std::vector<Point<T>>()) {
    std::vector<T> Xs;
    std::vector<T> Ys;
    rapidcsv::Document doc(filePath);
    Xs = doc.GetColumn<T>("X");
    Ys = doc.GetColumn<T>("Y");
    auto size = Xs.size()>Ys.size() ? Ys.size() : Xs.size();
    points.reserve(Xs.size());
    for(size_t i=0; i<size; ++i) {
        points.emplace_back( Xs[i], Ys[i] );
    }
    return;
}

/*==========================MAIN FUNCTION================================*/
int main(int argc, char* argv[]) {
    if(!argv[1]) {
        std::cout << "ENTER THE FILE OF POINTS\n";
        return 1;
    }

    auto X{0.0L};
    auto Y{0.0L};
    std::cout << "ENTER X VALUE ";
    std::cin >> X;
    std::cout << "ENTER Y VALUE ";
    std::cin >> Y;

    Point<decltype(X)> p{X,Y};
    std::cout << "your point is ==> " << p;
    
    std::vector<Point<decltype(X)>> points;
    
    readCsvFile<decltype(X)>(argv[1], points);    
    
    std::unique_ptr<KdTree<decltype(X)>> tree =  std::make_unique<KdTree<decltype(X)>>(KdTree<decltype(X)>());
    
    for(const auto& point : points) {
        tree->insert(point);
    }

    std::map<decltype(X), Point<decltype(X)>> dis_point = tree->search(p);
    
    std::cout << "the closest point to your point is ==> ";
    std::cout << dis_point.begin()->second;
    std::cout << "the distance from your point to the closest point is ==> "<< dis_point.begin()->first << std::endl;
    

    cv::Mat img = cv::Mat::zeros(cv::Size(WIDTH, HEIGHT), CV_8UC3);    
     
    for(auto& pt : points) {
        cv::circle(img, cv::Point2d(pt[0], (HEIGHT-pt[1])), 3, cv::Scalar(0, 255, 255), -1);
    }
    cv::circle(img, cv::Point2d(p[0], (HEIGHT-p[1])), 3, cv::Scalar(0, 255, 0), -1);
    
    auto x_closest = dis_point.begin()->second[0];
    auto y_closest = dis_point.begin()->second[1];
    
    cv::line(img, cv::Point2d(p[0], (HEIGHT-p[1])), cv::Point2d(x_closest, (HEIGHT-y_closest)), 
                  cv::Scalar(0, 0, 255), 1 );
    cv::imshow("visulaization of the result", img);
    cv::waitKey(0);
    return 0;
}
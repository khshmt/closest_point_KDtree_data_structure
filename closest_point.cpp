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
        
        auto it = std::find(line.begin(), line.end(), ','); //O(log(N))
        for(auto i=line.begin(); i != it; i++)
            num_1.push_back(*i);
        for(auto i=it+1; i!=line.end(); i++)
            num_2.push_back(*i);
        
        float x = std::stof(num_1);
        float y = std::stof(num_2);
        points.push_back({x,y});
    }
    
    std::shared_ptr<KdTree> tree(std::make_shared<KdTree>());
    int id = 0;
    for(auto point: points)
    {
        tree->insert(point, id);
        ++id;
    }

    std::map<float, Point> dis_point = tree->search(p);
    
    std::cout << "the closest point to your point is ==> ";
    dis_point.begin()->second.printPoint();
    std::cout << "the distance from your point to the closest point is ==> "<< dis_point.begin()->first << std::endl;
 
    return 0;
}

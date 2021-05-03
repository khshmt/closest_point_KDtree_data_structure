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
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <map>
#include <fstream>
#include <memory>
#include <numeric>

typedef unsigned int unit;

class Point
{
    public:
        Point(float x_=0, float y_=0) : x{x_}, y{y_}{} 

        friend float eculdianDistance(Point& p1, Point& p2);
        
        float  get(int dim)
        {
            if(dim == 0)
                return this->x;
            else
                return this->y;
        }
  
        void printPoint()
        {
            std::cout << "("<<this->x <<", "<<this->y <<")" << std::endl;
        }
    private:
        float x, y;
};

float eculdianDistance(Point& p1, Point& p2)
{
    float x_diff_sq = pow((p2.x-p1.x), 2);
    float y_diff_sq = pow((p2.y-p1.y), 2);
    return std::sqrt(x_diff_sq+y_diff_sq);
}

/*===========================================*/
struct Node
{
	Point point;
	int id;
	Node* left;
	Node* right;

	Node(Point p, int setId) : point(p), id(setId), left(NULL), right(NULL)
	{}
};


struct KdTree
{
	Node* root;
	KdTree():root(NULL)
	{}
/*=========================================Insert method==================================================================
Insert method used to insert point in the KDtree architecture 
*/
	void insertHelper(Node** node, unit depth, Point point, int id)
	{
		if(*node == NULL)
			*node = new Node(point, id);
		else
		{
			unit cd = depth % 2;
			
			if(point.get(cd) < (*node)->point.get(cd))
			       insertHelper(&((*node)->left), depth+1, point, id);
			else	
			       insertHelper(&((*node)->right), depth+1, point, id);
		}
	}

	void insert(Point point, int id)
	{
		insertHelper(&root, 0, point, id);	
	}
/*==================================================search methods======================================================
Search method used to search allover the tree for points which is the closest to a given point according
to a specific distance tolerance
*/
	void searchHelper(Point target, Node* node, int depth, std::vector<int>& ids, std::map<float, Point>& dis_point)
	{
        float min_distance = std::numeric_limits<double>::max();
		if(node != NULL)
		{

			float distance = eculdianDistance(node->point, target);
			if(distance < min_distance)
            {
				dis_point.emplace(std::make_pair(distance, node->point));
                ids.push_back(node->id);
            }

			if((target.get(depth%2)) < node->point.get(depth%2))
				searchHelper(target, node->left, depth+1, ids, dis_point);
			if((target.get(depth%2)) > node->point.get(depth%2))
				searchHelper(target, node->right, depth+1, ids, dis_point);
		}
	}

	std::map<float, Point> search(Point target)
	{
		std::vector<int> ids;
        std::map<float, Point> dis_point;
		searchHelper(target, root, 0, ids, dis_point);
		return dis_point;
	}
	

};
/*==========================MAIN FUNCTION================================*/
int main()
{
    float X, Y;
    std::cout << "ENTER X VALUE ";
    std::cin >> X;
    std::cout << "ENTER Y VALUE ";
    std::cin >> Y;

    Point p(X,Y);
    
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
 
    dis_point.begin()->second.printPoint();
    std::cout << dis_point.begin()->first << std::endl;
 

    return 0;
}

/*
-------------------------
| - | x | - | - | - | - |
-------------------------
| - | - | - | o | - | - |
-------------------------
| o | - | - | - | - | - |
-------------------------
| - | - | - | - | - | - |
-------------------------
| - | - | - | - | o | - |
-------------------------
| - | - | - | - | - | - |
-------------------------
**find the closet point of O's to x position**
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <map>
#include <fstream>

typedef unsigned int unit;

class Point
{
    public:
        Point(float x_=0, float y_=0) : x{x_}, y{y_}{} 

        friend Point operator+(const Point& point_1, const Point& point_2);
        
        friend Point  operator-(const Point& point_1, const Point& point_2);
        friend Point  findClosestPoint(std::vector<Point>& vec);
        friend double eculdianDistance(Point& p1, Point& p2);
        
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

Point operator+(const Point& point_1, const Point& point_2)
{
    float x__ = point_1.x + point_2.x;
    float y__ = point_1.y + point_2.y;
    return Point(x__, y__);
}
Point operator -(const Point& point_1, const Point& point_2)
{
    float x__ = point_1.x - point_2.x;
    float y__ = point_1.y - point_2.y;
    return Point(x__, y__);
}

double eculdianDistance(Point& p1, Point& p2)
{
    double x_diff_sq = pow((p2.x-p1.x), 2);
    double y_diff_sq = pow((p2.y-p1.y), 2);
    return std::sqrt(x_diff_sq+y_diff_sq);
}

//O(N)
Point findClosestPoint(std::vector<Point>& points, Point base)
{
    std::map<float, Point> map_; 
    for(auto point : points)
    {
        float dist = eculdianDistance(base, point);
        map_.emplace(std::make_pair(dist, point));
    }
    auto it = map_.begin();
    return it->second;
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
	void searchHelper(Point target, Node* node, int depth, float distanceTol, std::vector<int>& ids)
	{
		if(node != NULL)
		{
			if( (node->point.get(0) >= (target.get(0)-distanceTol) && node->point.get(0) <= (target.get(0)+distanceTol)) && (node->point.get(1) >= (target.get(1)-distanceTol) && node->point.get(1) <= (target.get(1)+distanceTol)))
			{
				float x_diff = node->point.get(0) - target.get(0);
				float y_diff = node->point.get(1) - target.get(1);
				float distance = std::sqrt( (x_diff*x_diff) + (y_diff*y_diff) );
				if(distance < distanceTol)
					ids.push_back(node->id);
			}

			if((target.get(depth%2)-distanceTol) < node->point.get(depth%2))
				searchHelper(target, node->left, depth+1, distanceTol, ids);
			if((target.get(depth%2)+distanceTol) > node->point.get(depth%2))
				searchHelper(target, node->right, depth+1, distanceTol, ids);
		}
	}

	std::vector<int> search(Point target, float distanceTol)
	{
		std::vector<int> ids;
		searchHelper(target, root, 0, distanceTol, ids);
		return ids;
	}
	

};
/*==========================MAIN FUNCTION================================*/
int main()
{
    float X, Y, disTol;
    std::cout << "ENTER X VALUE ";
    std::cin >> X;
    std::cout << "ENTER Y VALUE ";
    std::cin >> Y;
    std::cout << "ENTER THE WANTED TOLERANCE ";
    std::cin >> disTol;

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
    KdTree* tree(new KdTree) ;
    int id = 0;
    for(auto point: points)
    {
        tree->insert(point, id);
        ++id;
    }

    std::vector<int> ids = tree->search(p, disTol);
    if(ids.size()>0)
    { 
        for(auto id_ : ids)
        {
            points.at(id_).printPoint();
        }
    }
    else
        std::cout << "there is no points match that tolerance !!"<< std::endl;

    
    return 0;
}
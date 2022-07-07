#ifndef __KDTREE_H__
#define __KDTREE_H__

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <map>
#include <fstream>
#include <memory>
#include <numeric>


class Point
{
    public:
        Point(double x_=0, double y_=0) : x{x_}, y{y_}{} 

        friend double eculdianDistance(Point& p1, Point& p2);
        
        double  get(int dim)
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
        double x, y;
};

double eculdianDistance(Point& p1, Point& p2)
{
    double x_diff_sq = pow((p2.x-p1.x), 2);
    double y_diff_sq = pow((p2.y-p1.y), 2);
    return std::sqrt(x_diff_sq+y_diff_sq);
}

/*==================================================================================*/
class Node
{
    public:
        Point point;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(Point p) : point(p)
        {}
};


class KdTree
{
    public:
        Node* root = nullptr;
        KdTree()
        {}
/*=========================================Insert method=======================================
Insert method used to insert point in the KDtree architecture */

        void insertHelper(Node** node, uint32_t depth ,Point point)
        {
            if(*node == NULL)
                *node = new Node(point);
            else
            {
                uint32_t cd = depth % 2;
                
                if(point.get(cd) < (*node)->point.get(cd))
                    insertHelper(&((*node)->left), depth+1, point);
                else	
                    insertHelper(&((*node)->right), depth+1, point);
            }
        }
        void insert(Point point)
        {
            insertHelper(&root, 0 ,point);	
        }

/*==================================================search methods================================
Search method used to search allover the tree for points which is the closest to a given point according
to a specific distance tolerance
*/
        void searchHelper(Point target, Node* node, int depth, std::map<double, Point>& dis_point, double min_distance)
        {
            if(node != NULL)
            {

                double distance = eculdianDistance(node->point, target);
                
                if(distance < min_distance)
                    dis_point.emplace(std::make_pair(distance, node->point));
                
                if((target.get(depth%2)) <= node->point.get(depth%2))
                {
                    searchHelper(target, node->left, depth+1, dis_point, min_distance);
                    searchHelper(target, node->right, depth+1, dis_point, min_distance);
                }
                if((target.get(depth%2)) >= node->point.get(depth%2))
                {
                    searchHelper(target, node->right, depth+1, dis_point, min_distance);
                    searchHelper(target, node->left, depth+1, dis_point, min_distance);
                }
            }
        }
        std::map<double, Point> search(Point target)
        {
            std::map<double, Point> dis_point;
            double min_distance = std::numeric_limits<double>::max();
            searchHelper(target, root, 1, dis_point, min_distance);
            return dis_point;
        }
	

};



#endif
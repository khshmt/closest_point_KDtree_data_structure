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

template<typename T>
class Point {
public:
    Point(T _x=0, T _y=0) : x{_x}, y{_y} {
        //Empty
    } 

    decltype(auto) get(int dim) {
        if(dim == 0) {
            return this->x;
        } else {
            return this->y;
        }
    }

    void printPoint() {
        std::cout << "("<<this->x <<", "<<this->y <<")" << std::endl;
    }

    static decltype(auto) eculdianDistance(const Point<T>& p1, const Point<T>& p2) {
        auto x_diff_sq = pow((p2.x-p1.x), 2);
        auto y_diff_sq = pow((p2.y-p1.y), 2);
        return std::sqrt(x_diff_sq+y_diff_sq);
    }
private:
    T x, y;
};


/*==================================================================================*/
template<typename T>
class Node
{
public:
    Node(Point<T> p) : point(p) {   
        //Empty
    }
    Point<T> point{0, 0};
    std::shared_ptr<Node<T>>  left = nullptr;
    std::shared_ptr<Node<T>>  right = nullptr;  
};

template<typename T>
class KdTree
{
public:
    std::shared_ptr<Node<T>> root = nullptr;

    void insertHelper(std::shared_ptr<Node<T>>& node, uint32_t depth ,Point<T> point) {
        if(node == nullptr) {
            node = std::make_shared<Node<T>>(point);
        } else {
            uint32_t cd = depth % 2;

            if(point.get(cd) < node->point.get(cd)) {
                insertHelper(node->left, depth+1, point);
            } else {	
                insertHelper(node->right, depth+1, point);
            }
        }
    }
    void insert(Point<T> point) {
        insertHelper(root, 0 ,point);	
    }

    void searchHelper(Point<T> target, std::shared_ptr<Node<T>> node, int depth, std::map<double, Point<T>>& dis_point, double min_distance) {
        if(node != NULL) {   
            double distance = Point<T>::eculdianDistance(node->point, target);

            if(distance < min_distance) {
                dis_point.emplace(std::make_pair(distance, node->point));
            }

            if((target.get(depth%2)) <= node->point.get(depth%2)) {
                searchHelper(target, node->left, depth+1, dis_point, min_distance);
                searchHelper(target, node->right, depth+1, dis_point, min_distance);
            }

            if((target.get(depth%2)) >= node->point.get(depth%2)) {
                searchHelper(target, node->right, depth+1, dis_point, min_distance);
                searchHelper(target, node->left, depth+1, dis_point, min_distance);
            }
        }
    }
    decltype(auto) search(Point<T> target) {
        std::map<double, Point<T>> dis_point;
        double min_distance = std::numeric_limits<double>::max();
        searchHelper(target, root, 1, dis_point, min_distance);
        return dis_point;
    }
	

};

#endif
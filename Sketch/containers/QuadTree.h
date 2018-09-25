#ifndef QUADTREE_H
#define QUADTREE_H
#include <functional>
//https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/quadtrees.pdf

//Implements a Region Quadtree. Point is default point is center of square bound at (xmin, ymin), (xmax, ymax)
// Create a query method to recur to a given depth (have it call functor)

template <typename Point>
struct AABB
{
	const Point & min, &max;	//nopt points, store rect info
};



#define QUAD_TREE_TEMPLATE template <typename Point>
#define QUAD_TREE_DEF		QuadTree<Point>

//Create a for each interface (incremental and parallel)
 //type of points for min/max

QUAD_TREE_TEMPLATE
class QuadTree
{
private:
	struct Node
	{
		Node() :a(0), b(0), c(0), d(0){ }
		~Node() { delete a, b, c, d; }
		/*   _______
			|_a_|_b_|
			|_c_|_d_|
		*/
		QuadNode * a, b, c, d;
		//no dynamic updating, const 
		const Point & point;
		AABB<Point> rect;	//min and max boundary
	};

	Node * _root;
	unsigned int _size;
protected:
	void insertAt(Node* node,const Point & point);
	void removeAt(Node* node,const Point & point);


public:
	QuadTree();
	~QuadTree();


	//given an arry of points
	void construct(Point * points, unsigned int size);
	

	void insert(const Point & point);
	void remove(const Point & point);

	//takes in a function, return false to break. True to continue
	// function returns bool to break or continue
	
	void query(std::function<bool(	const AABB & rect, 
									const Point & point, 
									int depth)  );
};

QUAD_TREE_TEMPLATE 
QUAD_TREE_DEF::QuadTree() 
:_root(0), _size(0){}

QUAD_TREE_TEMPLATE 
QUAD_TREE_DEF::~QuadTree() 
{
	delete _root;
}


QUAD_TREE_TEMPLATE
void QUAD_TREE_DEF::insertAt(Node* node, const Point & point)
{
	DebugAssert(node);
}

QUAD_TREE_TEMPLATE
void QUAD_TREE_DEF::removeAt(Node* node, const Point & point)
{

	DebugAssert(node);

}

QUAD_TREE_TEMPLATE 
void QUAD_TREE_DEF::construct(Point * points, unsigned int size) 
{
	DebugAssert(points, size > 0);
	for (int i = 0; i < size; i++)
	{
		insert(points[i]);
	}
}

QUAD_TREE_TEMPLATE
void QUAD_TREE_DEF::insert(const Point & point) {}


QUAD_TREE_TEMPLATE 
void QUAD_TREE_DEF::remove(const Point & point) {}


//takes in a function, return false to break. True to continue
// function returns bool to break or continue

QUAD_TREE_TEMPLATE 
void QUAD_TREE_DEF::query(std::function<bool(const AABB & rect,
	const Point & point,
	int depth))
{}



#endif //QUADTREE_H

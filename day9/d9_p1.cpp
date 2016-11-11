#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;


class UIElement{
public:
	string name;
};
class FrameworkElement:public UIElement{
public:
	double Width;
	double Height;
	double OffsetLeft;
	double OffsetTop;
	int Gridcol = 1;
	int GridRow = 1;
	virtual void UpdateLayout(){}
} ;
class Panel : public FrameworkElement{
public:
	void Add(FrameworkElement *child);
	FrameworkElement Find(string name);
protected:
	vector<FrameworkElement*> Children;
};
class Grid : public Panel{
public:
	vector<int> Cols{1};
	vector<int> Rows{1};
	void UpdateLayout();
};
class Shapes:public FrameworkElement{

};
class Rectangle:public Shapes{
public:
	string Fill;
};

int main(){


	return 0;
}		
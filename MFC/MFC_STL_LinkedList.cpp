#include <iostream>
#include <ctime>
#include <list>
#include <algorithm>
using namespace std;
			
class DataPoint
{
public:

	void Set_x(double sx)
	{
		x = sx;
	}
	
	void Set_y(double sy)
	{
		y = sy;
	}
	
	void Set_z(double sz)
	{
		z = sz;
	}
	
	double Get_x(void)
	{
		return x;
	}
	
	double Get_y(void)
	{
		return y;
	}

	double Get_z(void)
	{
		return z;
	}
	
	void Set_catch(void)
	{
		catched = true;
	}
	
	void Set_uncatch(void)
	{
		catched = false;
	}

	bool Get_catched(void)
	{
		return catched;
	}

private:

	double x, y, z;
	bool catched;
};

class BSPLine
{
public:
	
	list<DataPoint> cline; //Link List for bspline

	void Init_DataPoints()
	{
		//  push_back()增加一元素到链表尾
		DataPoint *DP;
		DP = new DataPoint;
		
		srand( (unsigned)time(NULL));

		for(int i=0;i<11;i++)	//insert datapoints here
		{
			DP = new DataPoint;
			DP->Set_x(double(rand()%1000+1000)/100);
			DP->Set_y(double(rand()%1000+1000)/100);
			DP->Set_z(double(rand()%1000+1000)/100);
			if(i==5)
			{
				DP->Set_catch();
			}
			else
			{
				DP->Set_uncatch();
			}
			cline.push_back(*DP);
			delete DP;
		}
	}

private:

};

class List_Opert
{
public:
	
	void Show_DataPoints(list<DataPoint> &tempList)
	{
		//  size()返回链表中元素个数
		cout << "Number of Node is: " << tempList.size() << endl << endl;
		list<DataPoint>::iterator DPindex;

		for(DPindex = tempList.begin(); DPindex != tempList.end(); ++DPindex)
		{
			cout << DPindex->Get_x() << ' ' << DPindex->Get_y() << ' ' << DPindex->Get_z() << ' ' << DPindex->Get_catched() << ' ' <<endl;
		}
		cout << endl;
	}
	
	void Clear_List(list<DataPoint> &tempList)// clear() delete all elements of List
	{
		tempList.clear();
	}
	
	// insert()在指定位置插入一个或多个元素(三个重载函数)
	// iterator insert ( iterator position, const T& x );
	// void insert ( iterator position, size_type n, const T& x );
	// template <class InputIterator>
	// void insert ( iterator position, InputIterator first, InputIterator last );
	void List_insert(list<DataPoint> &tempList) //insert() insert a element
	{

		DataPoint *tempDP;
		tempDP = new DataPoint;

		tempDP->Set_x(5);
		tempDP->Set_y(5);
		tempDP->Set_z(5);
		tempDP->Set_uncatch();

		list<DataPoint>::iterator DPindex;
		for(DPindex = tempList.begin(); DPindex != tempList.end(); ++DPindex)
		{
			if(DPindex->Get_catched()==true)
			{
				tempList.insert(++DPindex, *tempDP);
				break;
			}
		} 
	}
	
	void List_mutil_element_erase(list<DataPoint> &tempList) // erase() delete all elements by condition of List
	{
		DataPoint *tempDP;
		tempDP = new DataPoint;

		list<DataPoint>::iterator DPindex;
		DPindex = tempList.begin();
		for(DPindex = tempList.begin(); DPindex != tempList.end(); ++DPindex)
		{
			if(DPindex->Get_catched()==true)
			{
				tempList.erase(DPindex);
				DPindex = tempList.begin();
			}
		}
		DPindex = tempList.begin();
	}
	
	void List_element_erase(list<DataPoint> &tempList) // erase() delete an element by condition of List
	{
		DataPoint *tempDP;
		tempDP = new DataPoint;

		list<DataPoint>::iterator DPindex;
		for(DPindex = tempList.begin(); DPindex != tempList.end(); ++DPindex)
		{
			if(DPindex->Get_catched()==true)
			{
				tempList.erase(DPindex);
				break;
			}
		}
	}


private:
};

int main(void)
{
	BSPLine *bpl;
	List_Opert *lopt;

	bpl = new BSPLine;
	lopt = new List_Opert;

	bpl->Init_DataPoints();
	lopt->Show_DataPoints(bpl->cline);
	lopt->List_insert(bpl->cline);
	lopt->Show_DataPoints(bpl->cline);
	lopt->List_mutil_element_erase(bpl->cline);
	lopt->Show_DataPoints(bpl->cline);

	return 0;
}

#include "stdafx.h"
#include "ListViewItemComparer.h"

ListViewItemComparer::ListViewItemComparer()
{
	col = 0;
}

ListViewItemComparer::ListViewItemComparer( int column , SortOrder type)
{
	col = column;
	order = type;
}

int ListViewItemComparer::CurrentComparer()
{
	return col;
}

SortOrder ListViewItemComparer::CurrentSortOrder()
{
	return order;
}

int ListViewItemComparer::Compare( Object^ x, Object^ y )
{
	int ret;
	String ^sx = gcnew String((dynamic_cast<ListViewItem^>(x))->SubItems[ col ]->Text);
	String ^sy = gcnew String((dynamic_cast<ListViewItem^>(y))->SubItems[ col ]->Text);
	ret = String::Compare( sx,sy);
	if(order == SortOrder::Ascending) return ret;
	else if(order == SortOrder::None){
		double numx,numy;
		numx = Double::Parse(sx,Globalization::NumberStyles::Currency);
		numy = Double::Parse(sy,Globalization::NumberStyles::Currency);
		if(numx < numy) return 1;
		else return -1;
	}
	else return ret *= -1;
}
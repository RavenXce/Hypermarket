#pragma once
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections;

// Implements the manual sorting of items by columns.
ref class ListViewItemComparer: public IComparer
{
private:
   int col;
   SortOrder order;

public:
   ListViewItemComparer();
   ListViewItemComparer( int column , SortOrder type);
   int CurrentComparer();
   SortOrder CurrentSortOrder();
   virtual int Compare( Object^ x, Object^ y );
};
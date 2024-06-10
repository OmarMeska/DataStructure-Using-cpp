#include <iostream>
#include <cassert>
#include <queue>
using namespace std;

int avl_nodes_rec(int height){
	if (height<0) return 0 ;
     
	return 1 + avl_nodes_rec(height-1) + avl_nodes_rec(height-2) ;
}

int avl_nodes_iter(int height){
	 int arr[500]{} ;
	 arr[0] = 1 ;
	  arr[1] = 2 ;
	 for (int i=2 ;i<=height ; i++ ) {
       arr[i] = 1 + arr[i-1] + arr[i-2] ;
	 } 

	 return arr[height] ;
}

int main(){
	cout << avl_nodes_iter(0)<< endl ;
	cout << avl_nodes_iter(1)<< endl ;
	cout << avl_nodes_iter(2)<< endl ;
	cout << avl_nodes_iter(3)<< endl ;
	cout << avl_nodes_iter(4)<< endl ;
	cout << avl_nodes_iter(5)<< endl ;
}



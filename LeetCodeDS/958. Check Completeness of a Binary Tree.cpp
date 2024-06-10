
#include<bits/stdc++.h>
using namespace std ;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        queue<TreeNode*> node_queue ;
        node_queue.push(root) ;
        int level =0 ;
        bool flag =false ;
        while (!node_queue.empty()) {
            int sz= node_queue.size(); 
            while (sz --) {
                TreeNode*cur = node_queue.front() ;
                node_queue.pop();
                if (cur->right and !cur->left) return false ;
                if (cur->right){
                        if (flag) return false ;
                        node_queue.push(cur->left) ;
                        node_queue.push(cur->right) ;
                }
                else if (cur->left ) {
                    if (flag) return false ;
                    node_queue.push(cur->left) ;
                flag =true ;
                }else flag =true ;
                

            }
        }
        return true ;
    }
};

int main(){

}
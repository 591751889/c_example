#include<stdio.h>
#include <stdlib.h>

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

void preorder(struct TreeNode *tree)
{
	if(!tree)
	{
		printf("NULL   ");
	}
	else
	{
		printf("%5d",tree->val);
		preorder(tree->left);
		preorder(tree->right);
	}
 } 
 
 struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
 		struct TreeNode *tree;
 		tree=(struct TreeNode*)malloc(sizeof(struct TreeNode)) ;
 		if(nums==NULL||numsSize==0)return NULL;
 	
		int middle=numsSize/2;
		tree->val=nums[middle];
		tree->left=sortedArrayToBST(nums,middle);
		tree->right=sortedArrayToBST(&nums[middle+1],numsSize-1-middle);
		return tree;
}

struct TreeNode* createTree() {
	int value;
	struct TreeNode *tree;
	scanf("%d",&value);
	if(value==999) {
		tree=NULL;
	} else {
		tree=(struct TreeNode*)malloc(sizeof(struct TreeNode)) ;
		tree->val=value;
		tree->left=createTree();
		tree->right=createTree();
	}

	return tree;
}
int main() {
	int a[]= {-10,-3,0,5,9} ;
	struct TreeNode *root=sortedArrayToBST(a,5);
	preorder(root);
	return 0;
}

#include<iostream>

using namespace std;

class node{
   public:
   int data;
   node* left;
   node* right;
   int height;

   node(int ele){
    this->data=ele;
    this->left=this->right=NULL;
    this->height=1;

   }
};

int getheight(node* root){
   if(root==NULL) return 0;

   return root->height;
}
int balance(node* root){
   if(root==NULL) return 0;

   return (getheight(root->left)-getheight(root->right));   
}

node* leftrotation(node* root){
   node* temp=root->right;
   root->right=temp->left;
   temp->left=root;
   
   root->height=1+max(getheight(root->left),getheight(root->right));
   temp->height=1+max(getheight(temp->left),getheight(temp->right));

   return temp;
}
node* rightrotation(node* root){
   node* temp=root->left;
   root->left=temp->right;
   temp->right=root;
   root->height=1+max(getheight(root->left),getheight(root->right));
   temp->height=1+max(getheight(temp->left),getheight(temp->right));
   return temp;
}

node* insert_ele(node* root,int ele){
   if(root==NULL){
      node* newnode=new node(ele);

      return newnode;
   }
   if(root->data<ele) root->right=insert_ele(root->right,ele);

   else if(root->data>ele) root->left=insert_ele(root->left,ele);

   else return NULL;
   

   root->height=1+max( getheight(root->left),getheight(root->right));
   
   int balanced=balance(root);

   if( balanced>1){
      //left left
       if(root->data>ele){
          
         return rightrotation(root);
       }
       //left right
       else{
         root->left=leftrotation(root->left);
         return rightrotation(root);
       }
   }
   else if(balanced<-1){
      //right right
     if(root->data<ele){
      return leftrotation(root);
     }
     //right left
     else{
       root->right=rightrotation(root->right);
       return leftrotation(root);
     }
   }

   return root;

}

void inorder(node* root){
   if(root==NULL) return;

   inorder(root->left);
   cout<<root->data<<" ";
   inorder(root->right);

}

node* deletion(node* root,int ele){
  if(root==NULL) return NULL;

   if(root->data<ele) root->right=deletion(root->right,ele);
   else if(root->data>ele) root->left=deletion(root->left,ele);

   else{
          if(!root->left){
            node* temp=root->right;
            delete(root);
            return temp;
          }
          else if(!root->right){
            node* temp=root->left;
            delete(root);
            return temp;
          }
          else{
            node* child=root->right;

            while(child->left!=NULL){
               child=child->left;
            }
            root->data=child->data;

            root->right=deletion(root->right,child->data);

          }

          
   }

   return root;
}

int main(){
  int n;
  cin>>n;
   node* root=NULL;

  for(int i=0;i<n;i++){
   int ele;
   cin>>ele;
   root=insert_ele(root,ele);
  }

  inorder(root);
  cout<<endl;
  int ele;
  cin>>ele;
  root=deletion(root,ele);

  inorder(root);
}
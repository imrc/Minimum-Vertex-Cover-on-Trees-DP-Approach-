///Coding done in c++ BY RISHAD C [B160346CS]
//Compiler used: g++ (Ubuntu 5.4.0-6ubuntu1~16.04.6) 5.4.0 20160609  
//header for stack inbuild
#include <bits/stdc++.h> 

#include <iostream>

//header for malloc
#include <cstdlib> 

using namespace std; 
  
//max no.of nodes
#define nMAX 200


//max no.of children for a node
#define MAX 100

/////////////////////////////////////DP Array maintanace ////////////////////////////////
//initializing 1D Memoization Array (global variables are zero-initialised in C++)
int DP[nMAX];

void updateDP(char x,int vc)
{
    int y =(int)x;
    DP[y]=vc;
}

int getDP(char x)
{
    int y =(int)x;
    return DP[y];
}
/////////////////////////////////////////////////////////////////////////////////

struct Node 
{ 
    char label; 
   // int vc;
    int childCount;
    struct Node *child[MAX]; 
}; 

// new node alloc func
Node* newNode(char label) 
{ 
    Node* node = (Node*)malloc(sizeof(Node)); 
    node->label = label; 
   // node->vc=0;
    node->childCount=0;
 //   printf("\nnode(%c)\n",label);
    return (node); 
} 
 //ret min bw 2 var
 int min(int x, int y) { return (x < y)? x: y; } 

// test purpose 
void preOrder(Node* node) 
{ 
    if (node == NULL) 
        return; 
    cout << node->label <<" ";
    int i=0;
    while(i<(node->childCount))
    {
        preOrder(node->child[i]);
        i++;
    }
} 
  
// functin to return the index of end parenthesis 
int findEIndex(string str, int bi, int ei) 
{ 
    if (bi > ei) 
        return -1; 
  
    // Using Inbuilt stack 
    stack<char> s; 
  
    for (int i = bi; i <= ei; i++) { 
  
        // if open parenthesis, push it 
        if (str[i] == '(') 
            s.push(str[i]); 
  
        // if close parenthesis 
        else if (str[i] == ')') { 
            if (s.top() == '(') { 
                s.pop(); 
  
                // if stack is empty, this is  
                // the required index 
                if (s.empty()) 
                    return i; 
            } 
        } 
    } 
    // if not found return -1 i.e no more children
    return -1; 
} 
  
// function to construct tree from input given which is in "parenthesis form" 
Node* treeFromString(string str, int bi, int ei) 
{ 
    // Base case 
    if (bi > ei) 
        return NULL; 
  
    // new root 
    Node* root = newNode(str[bi]); 
    int indexend = -1; 
    int indexbegin = bi + 1;
  


    ////
    if (bi + 1 <= ei && str[bi + 1] == '(') 
        indexend = findEIndex(str, bi + 1, ei); 
  

    int i=0;
    
    while (indexend != -1) { 
        
        // call for next subtree 
        root->child[i] = treeFromString(str, indexbegin + 1, indexend - 1); 
        //printf("sub");
        indexbegin=indexend+1;
        indexend = findEIndex(str, indexend+1, ei); 
      
        i++;
    } 
   // printf("%d",indexend);
    //printf("end(%c)",root->label);
    root->childCount=i;
    return root; 
} 
  

int vCover(struct Node *root) 
{ 
    //var for looping
    int i,j;

    // The  minimum vertex cover returned is zero if No children
    if (root->childCount == 0) 
        return 0; 

   //////////////////////////////Memoization////////////////////////////
   // If vertex cover for this node is already evaluated, then return it 
    /* if (root->vc != 0) 
        return root->vc; */
    int vc = getDP(root->label);
    if (vc != 0) 
        return vc;
  
    // Calculate size of vertex cover when root is part of it 
    int nodeInclud = 1;  

    for(i=0; i<(root->childCount) ;i++)
    {
       nodeInclud += vCover(root->child[i]);
    }
  
    // Calculate size of vertex cover when root is not part of it 
    int nodeExclud = root->childCount; 
 
    for(i=0; i<(root->childCount) ;i++)
    {

       for(j=0; j<((root->child[i])->childCount) ;j++)
       {
            nodeExclud += vCover((root->child[i])->child[j]);
       }
    }
    // Minimum of two values is vertex cover, store it before returning 
   // root->vc =  min(nodeInclud, nodeExclud);
   int minVC = min(nodeInclud, nodeExclud);
  updateDP(root->label,minVC);

    //return root->vc; 
return minVC;
} 
  


// COde EXec start-->
int main() 
{ 
 //   string str = "a(b(f)(g(z(q(r))(w(t)(l)))))(c)(d)(e(h)(v))(h(x)(y(i(j))))";
    string str;
    cout <<"Input the Tree in Parenthesis form-->"<<endl;
    cin >>str;
    Node* root = treeFromString(str, 0, str.length() - 1); 
    cout <<endl<<"treeTraversedIs : ";
   preOrder(root); 
   cout <<endl<<"Minimum Vertex Cover = "<<vCover(root)<<endl;
} 

#include <iostream>
#include <cstring>
#include <string>
#include <ctime>


#define NOT_FOUND -1
using namespace std;

//Vetor dinamico ordenado

int *keys;
string *vals;
int N;  



int Rank(int key) {
    int lo = 0, hi = N-1;
    while (lo <= hi){
        int mid = lo + (hi = lo) / 2;
        if (key < keys[mid]) hi = mid - 1;
        else if (key > keys[mid]) lo = mid + 1;
        else return mid;
    }
    return lo;
}


void add(int key, string val) { 
    int i = Rank(key);
    if( i < N && keys[i] == key)
    { vals[i] = val; return; }
    for(int j = N; j > i; j--)
    { keys[j] = keys[j-1]; vals[j] = vals[j-1];}
    keys[i] = key; vals[i] = val;


}


int select(int k) {
    return keys[k];
}


string value(int key) {
    int i = Rank(key);
    if(i < N && keys[i] == key) return vals[i];
    else return NULL;
}


//Binary Search Tree

struct Node{
    
  
    string chave;
    int value;
     Node *left;
     Node *right;

   
    

     Node(string k, int v)  {
         chave = k;
         value = v;
         left = nullptr;
         right = nullptr;
     }
};

Node *rootBST;

int get(Node* x, string key) {
    if(x == nullptr) return NOT_FOUND;
    if(x->chave == key) return x->value;
    if(x->chave > key) 
    return get(x->left, key);
    return get(x->right, key);
}

int value(string key) {
    return get(rootBST, key);
}

Node *put (Node *root, string key, int val) {
    if(root == nullptr) {
        root = new Node(key, val);
        return root;
    }
    if(root->chave == key)
    root->value = val;
    else if(root->chave>key){
        root->left = put(root->left,key, val);
    }
    else 
    root->right = put(root->right, key, val);

    return root;
}

void add (string key, int val) {
    rootBST = put(rootBST, key, val);
}

int quantidadenos (Node *x) {
    if(x == nullptr)
    return 0;
    else 
      return 1 + quantidadenos(x->left) + quantidadenos(x->right);
}




int rankBST(string key, Node *x) {
    if(x == nullptr) return 0;
    if (key < x->chave) 
    return rankBST(key, x->left);
    else if(key > x->chave ) 
    return 1 + quantidadenos(x->left) + rankBST(key, x->right);
    else return quantidadenos(x->left);
}



int rankBST(string key) {
    
    return rankBST(key, rootBST);
    

}

Node* selectBST(Node* x, int k) {
    if(x == nullptr) return nullptr;
    int t = quantidadenos(x->left);
    if (t > k) return selectBST(x->left, k);
    else if (t < k) return selectBST(x->right, k-t-1);
    else return x;
}

string selectBST(int k) {
    return selectBST(rootBST, k)->chave;
}

//Treaps

struct TreapNod  {
   string data;
   int priority;
   TreapNod* l, *r;
   TreapNod(string d) { 
      this->data = d;
      this->priority = rand() % 100;
      this->l= this->r = nullptr;
   }
};
void rotLeft(TreapNod* &x) {
   TreapNod* R = x->r;
   TreapNod* X = x->r->l;
   R->l = x;
   x->r= X;
   x = R;
}

void rotRight(TreapNod* &x) { 
   TreapNod* L = x->l ;
   TreapNod* Y = x->l->r;
   L->r = x;
   x->l= Y;
   x = L;
}

void insertNod(TreapNod* &x, string d) {
   if (x == nullptr) {
      x = new TreapNod(d);
      return;
   }
   if (d < x->data) {
      insertNod(x->l, d);
      if (x->l != nullptr && x->l->priority > x->priority)
      rotRight(x);
   } else {
      insertNod(x->r, d);
      if (x->r!= nullptr && x->r->priority > x->priority)
      rotLeft(x);
   }
}

bool searchNod(TreapNod* x, string key) {
   if (x == nullptr)
      return false;
   if (x->data == key)
      return true;
   if (key < x->data)
      return searchNod(x->l, key);
      return searchNod(x->r, key);
}

void deleteNod(TreapNod* &x, string key) {
   if (x == nullptr)
      return;
   if (key < x->data)
      deleteNod(x->l, key);
   else if (key > x->data)
      deleteNod(x->r, key);
   else {
      if (x->l ==nullptr && x->r == nullptr) {
         delete x;
         x = nullptr;
      }
      else if (x->l && x->r) {
         if (x->l->priority < x->r->priority) {
            rotLeft(x);
            deleteNod(x->l, key);
         } else {
            rotRight(x);
            deleteNod(x->r, key);
         }
      }
      else {
         TreapNod* child = (x->l)? x->l: x->r;
         TreapNod* curr = x;
         x = child;
         delete curr;
      }
   }
}

void displayTreap(TreapNod *x, int space = 0, int height =10) {
   if (x == nullptr)
      return;
   space += height;
   displayTreap(x->l, space);
   cout << endl;
   for (int i = height; i < space; i++)
      cout << ' ';
      cout << x->data << "(" << x->priority << ")\n";
      cout << endl;
   displayTreap(x->r, space);
}

//tree23

class tree23Node {
    public:
    int lval;  
    string lkey;
    int rval;
    string rkey;  
  
    tree23Node *left, *middle, *right;

    tree23Node() {left = right = middle = nullptr;}


    tree23Node(int lv, string lk, int rv, string rk, tree23Node* p1, tree23Node* p2, tree23Node* p3) {
    lkey = lk; rkey = rk;
    lval = lv; rval = rv;
    left = p1; middle = p2; right = p3;
    }
public:

bool isLeaf() {return left == nullptr;}
tree23Node* lchild() {return left;}
tree23Node* rchild() {return right;}
tree23Node* mchild() {return middle;}
int flval() {return lval;}
string flkey() {return lkey;} 
int frval() {return rval;}
string frkey() {return rkey;}
void setLeft(string k, int v) {lkey = k; lval = v;}
void setRight(string k, int v) {rkey = k; rval = v;}
void setLeftChild(tree23Node* x) {left = x;}
void setMiddleChild(tree23Node* x) {middle = x;}
void setRightChild(tree23Node* x) {right = x;}

tree23Node* add(tree23Node* x) {
    return x;
}

};


tree23Node *root23;

int getvaluetree23(tree23Node* x, string k) {
    if(x == nullptr) {return NOT_FOUND;}
    if(k.compare(x->lkey) == 0) {return x->lval;}
    if((x->rkey != "") && (k.compare(x->lkey) == 0))
        return x->rval;    
     if(k.compare(x->lkey) < 0)
        return getvaluetree23(x->left, k);
 else if(x->rkey == "")
        return getvaluetree23(x->middle, k);
    else if(k.compare(x->rkey)<0)
    return getvaluetree23(x->middle, k);
  
}

int valuetree23(string k) {
    return getvaluetree23(root23, k);
}



tree23Node* inserirnotree23(tree23Node* x, string k, int v) {
    tree23Node* retval;
    if(x == nullptr)
    return new tree23Node(v, k, NOT_FOUND, "", nullptr, nullptr, nullptr);
    if(x->isLeaf()){
        return x->add(new tree23Node(v, k, NOT_FOUND, "", nullptr, nullptr, nullptr));
    }
    if(k.compare(x->flkey()) < 0) {
        retval = inserirnotree23(x->lchild(), k, v);
        if(retval == x->lchild()) {return x;}
        else {return x->add(retval);}
        
    }
}








//arvore rubro-negra

enum Cor{VERMELHO, PRETO};

struct NodeRB{
    int val;
    string key;
    bool cor;
    NodeRB *esq, *dir, *pai;

    //Constructor
    NodeRB(int val, string key)
    {
        this->val = val;
        this->key = key;
        esq = dir = pai = NULL;
        this->cor = VERMELHO;
    }
};

class RBTree{
    private:
    NodeRB *raiz;

    protected:
    void RodaEsq(NodeRB *&, Node *&);
    void RodaDir(NodeRB *&, Node *&);
    void ArrumarRB(NodeRB *&, Node *&);

    public:
    RBTree() { raiz = NULL;}
    void insert(const int &n);
    void inorder();
    void levelOrder();
};

/*NodeRB* putRB(NodeRB* raiz, NodeRB* pt) {
    if(raiz == nullptr)
    return pt;

    if (pt->key < raiz->key) {
        raiz->esq = putRB(root->esq, pt);
        raiz->esq->pai = raiz;
    }
}


*/

int main() {
string estrutura;

string *texto, *acao, aux2;
aux2 = "";
int aux;
int tamanho, acoes;





cin >> estrutura;
cin >> tamanho;

texto = new string[tamanho];

if(estrutura == "VO")
cout << "Funções implementadas no código, porém ocorre erro ao inserir";

else if (estrutura == "TR") 
cout << "Função inserir implementada no código"; 

else if (estrutura == "A23")
cout << "Funções não implementadas no código";

else if (estrutura == "ARN")
cout << "Funções não implementadas no código";

else

if(estrutura == "ABB") {
for (int i = 0; i < tamanho; i++) {
cin >> texto[i];
add(texto[i], i);
}

cin >> acoes;

acao = new string[acoes+1];



for (int i = 0; i < acoes+1; i++)
getline(cin, acao[i]);

for (int i = 0; i < acoes+1; i++) {
    if(acao[i][0] == '1') {
        aux = stoi(acao[i].substr(2, acao[i].length()));           
       for (int j = 0; j < aux; j++)
        add(texto[j], j);
    }
    else if(acao[i][0] == '2'){
        cout << "Função não implementada no código";
    }
    
    else if(acao[i][0] == '3') {
       aux2 = acao[i].substr(2, acao[i].length());
       cout << rankBST(aux2);
    }

    else if(acao[i][0] == '4') {
        aux = stoi(acao[i].substr(2, acao[i].length()));  
        cout << selectBST(aux);
        
    }
}

}




  

}
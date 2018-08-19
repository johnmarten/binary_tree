/*
Namn: BinSearchTree.h
Beskrivning: Deklarerar typer och funktioner för ett generellt binärt sökträd.
*/

typedef struct node_ *TreeNode;
typedef struct tree_ *Binsearchtree;

Binsearchtree inittree(int (*cmp)(const void *key1, const void *key2), void (*destroy)(const void *data));
int insert(Binsearchtree tree, const void *data);
void *find(Binsearchtree tree, const void *data);
int delete(Binsearchtree tree, const void *data);
void doforall(Binsearchtree tree, void (*func)(void *data));
void preorder(Binsearchtree tree, void (*func)(void *data));
void postorder(Binsearchtree tree, void (*func)(void *data));

typedef struct TypeNode
{
    char* type;
    struct TypeNode* parent;
} TypeNode;

char* hasParent()
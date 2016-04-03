#ifndef HUFFMANNODE
#define HUFFMANNODE

/**
 * @brief The HuffmanNode class
 * implements the Huffman tree
 */
class HuffmanNode{
public:
    int count;
    char symbol;
    HuffmanNode *leftPTR;       //a pointer to the left node
    HuffmanNode *rightPTR;      //a pointer to the right node

    /**
     * Default Constructor: HuffmanNode
     * Initializes new empty tree
     */
    HuffmanNode(){
        leftPTR = rightPTR = NULL;
    }

    /**
     * An explicit constructor: HuffmanNode
     * @param L - left node
     * @param R - right node
     */
    HuffmanNode (HuffmanNode *L, HuffmanNode *R){
        leftPTR = L;
        rightPTR = R;
        count = L->count + R->count;
    }



    /**
     *Destructor: HuffmanNode
     * Frees memory
     */
    ~HuffmanNode(){
        delete leftPTR;
        delete rightPTR;
    }
};


/**
 * The comparison struct
 * compares the left and right nodes of a tree
 */
struct comparison{
    bool operator()(HuffmanNode* l,HuffmanNode* r) {
        return l->count < r->count;
    }
};

#endif // HUFFMANNODE


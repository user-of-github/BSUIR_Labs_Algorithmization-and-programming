#include "Set.h"

void Set :: DeleteByPointer (Node *pointer)
{
    Node *left = pointer->leftChild,
          *right = pointer->rightChild;

    // There are three cases: has no children | has one child | has both children

    if (left != nullptr && right != nullptr) // has both
    {
        Node *localMax = this->GetMaximumValue(left);
        pointer->value = localMax->value;

        this->DeleteByPointer(localMax); // no recursion. Maximum 1 call
    }
    else if (left != nullptr || right != nullptr) // only left child
    {
        Node *leftOrRight = (left != nullptr ? left : right);

        if (pointer->parent->rightChild == pointer)
            pointer->parent->rightChild = leftOrRight;
        else
            pointer->parent->leftChild = leftOrRight;

        leftOrRight->parent = pointer->parent;

        delete pointer;
    }
    else // no children
    {
        if (pointer->parent != nullptr) // it is not root
        {
            if (pointer->parent->leftChild == pointer)
                pointer->parent->leftChild = nullptr;
            else
                pointer->parent->rightChild = nullptr;
        }

        delete pointer;
    }
    return;
}

void Set :: RecursiveClear (Node *element)
{
    if (element != nullptr)
    {
        RecursiveClear(element->leftChild);
        RecursiveClear(element->rightChild);
        delete element;
    }

    return;
}

void Set :: RecursivePrint (const Node *element) const
{
    if (element != nullptr)
    {
        RecursivePrint (element->leftChild);
        cout<<"{"<<element->value<<"} ";
        RecursivePrint (element->rightChild);
    }

    return;
}

Set :: Node * Set :: GetMinimumValue (Node *startNode) const
{
    Node *answer = startNode;

    while (answer->leftChild != nullptr)
        answer = answer->leftChild;

    return answer;
}

Set :: ~Set ()
{
    this->Clear();
}

Set :: Node * Set :: GetMaximumValue (Node *startNode) const
{
    Node *answer = startNode;

    while (answer->rightChild != nullptr)
        answer = answer->rightChild;

    return answer;
}

Set :: Node * Set :: FindElement (const long long &_number) const
{
    Node *searchElement = this->root;

    Node *left = searchElement->leftChild,
          *right = searchElement->rightChild;

    while (searchElement != nullptr)
    {
        left = searchElement->leftChild;
        right = searchElement->rightChild;

        if (searchElement->value == _number)
            break;

        searchElement = (_number > searchElement->value ? right : left);
    }

    return searchElement;
}

unsigned int Set :: Size () const
{
    return this->_size;
}

Set :: Set ()
{
    this->root = nullptr;
    this->_size = 0;
}

void Set :: Add (const long long &_new)
{
    Node *newNode = new Node(_new, nullptr);

    if (this->root == nullptr && this->_size == 0)
    {
        this->root = newNode;
        this->_size ++;
    }
    else
    {
        if (this->Has(_new) == false)
        {
            Node *element = this->root;
            Node *left = element->leftChild,
                  *right = element->rightChild,
                   *tempParent = this->root;

            while (element != nullptr)
            {
                tempParent = element;

                left = element->leftChild;
                right = element->rightChild;

                element = (_new > element->value ? right : left);
            }

            newNode->parent = tempParent;
            ((_new > tempParent->value) ? (tempParent->rightChild = newNode) : (tempParent->leftChild = newNode));

            this->_size ++;
        }
    }

    return;
}

bool Set :: Has (const long long &_check) const
{
    return (this->FindElement(_check) != nullptr);
}

void Set :: Delete (const long long &_number)
{
    if (this->Has(_number) == true && this->_size > 0)
    {
        Node *searchElement = this->FindElement(_number);
        this->DeleteByPointer(searchElement);

        this->_size --;
    }

    if (this->_size == 0)
    {
        this->root = nullptr;
    }

    return;
}


void Set :: Clear ()
{
    this->RecursiveClear(this->root);
    this->root = nullptr;
    this->_size = 0;

    return;
}
ostream & operator << (ostream & cout, const Set &object)
{
    cout<<"Set ("<<object._size<<"): { ";
    if (object._size > 0)
        object.RecursivePrint(object.root);
    cout<<"}\n";

    return cout;
}

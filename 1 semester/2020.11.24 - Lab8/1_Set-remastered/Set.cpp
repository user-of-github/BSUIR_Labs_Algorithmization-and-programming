#include "Set.h"


void Set :: PrintSetRecursive (Member *member) const
{
    if (member != nullptr)
    {
        PrintSetRecursive (member->leftChild);
        cout<<member->value<<"; ";
        PrintSetRecursive (member->rightChild);
    }
    return;
}


Set :: Set ()
{
    this->_size = 0;
}

unsigned long long Set :: Size () const
{
    return this->_size;
}

bool Set :: Has (const long long &_check) const
{
    Member *element = this->root;
    Member *left = element->leftChild,
            *right = element->rightChild;

    bool found = false;
    while (element != nullptr)
    {
        if (element->value == _check)
        {
            found = true;
            break;
        }
        left = element->leftChild;
        right = element->rightChild;

        if (left != nullptr)
        {
            if (left->value == _check)
            {
                found = true;
                break;
            }
        }
        if (right != nullptr)
        {
            if (right->value == _check)
            {
                found = true;
                break;
            }
        }

        if (_check > element->value)
            element = right;
        else
            element = left;
    }

    return found;

}
void Set :: Add (const long long &_new)
{
    if (this->_size == 0)
    {
        this->_size ++;
        this->root = new Member (_new, nullptr);
    }
    else
    {
        if (this->Has(_new) == false)
        {
            Member *searchElement = this->root;
            Member *tempParent = this->root;
            Member *left = searchElement->leftChild,
                    *right = searchElement->rightChild;

            while (searchElement != nullptr)
            {
                tempParent = searchElement;

                left = searchElement->leftChild;
                right = searchElement->rightChild;

                if (_new > searchElement->value)
                    searchElement = right;
                else
                    searchElement = left;
            }

            Member *newChild = new Member(_new, tempParent);
            if (_new > tempParent->value)
                tempParent->rightChild = newChild;
            else
                tempParent->leftChild = newChild;

            this->_size ++;
        }
    }

    return;
}

/*void Set :: Delete (const long long &_num)
{
    if (this->Has(_num) == true)
    {
        Member *element = this->root;
        Member *left = element->leftChild,
                *right = element->rightChild;

        // сначала найду этот элемент
        while (element != nullptr)
        {
            left = element->leftChild;
            right = element->rightChild;

            if (element->value == _num)
                break;
            else if (left != nullptr)
            {
                if (left->value == element->value)
                {
                    element = left;
                    left = element->leftChild;
                    right = element->rightChild;
                    break;
                }
            }
            else if (right != nullptr)
            {
                if (right->value == element->value)
                {
                    element = right;
                    left = element->leftChild;
                    right = element->rightChild;
                    break;
                }
            }

            if (_num > element->value)
                element = right;
            else
                element = left;
        }
        // cout<<"found: "<<element->value<<"\n";
        Member *parent = element->parentElement;
        //cout<<"parent : "<<parent->value<<"\n";
        if (this->_size == 1) // то есть осталось всего одно число - корневое
        {
            delete this->root;
            this->root = nullptr;
        }

        //спустился в левое поддерево
        if (left == nullptr) // то есть левого поддерева нет
        {
            if (right == nullptr) // и правого тоже нет
            {
                if (parent->rightChild == element)
                    parent->rightChild = nullptr;
                else if (parent->leftChild == element)
                    parent->leftChild = nullptr;
            }
            else
            {

                right->parentElement = parent;

                if (parent->rightChild == element)
                    parent->rightChild = right;
                else if (parent->leftChild == element)
                    parent->leftChild = right;
            }
        }
        else // левое поддерево есть
        {
            Member *replaced = left;
            Member *replacedParent;
            while (replaced->rightChild != nullptr)
                replaced = replaced->rightChild;
            element->value = replaced->value;
            replacedParent = replaced->parentElement;
            if (replaced->leftChild == nullptr)
            {
                replacedParent->rightChild = nullptr;
            }
            else
            {
                Member *replacedLeft = replaced->leftChild;
                replacedLeft->parentElement = replaced->parentElement;
                replacedParent->rightChild = replacedLeft;
            }
            //delete replaced;
        }
        this->_size --;
    }


    return;
}*/

ostream & operator << (ostream & cout, const Set &object)
{
    cout<<"Set ("<<object._size<<") : { ";
    if (object._size > 0)
        object.PrintSetRecursive(object.root);
    cout<<"}\n";

    return cout;
}

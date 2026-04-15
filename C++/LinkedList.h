#ifndef ORDEREDLINKEDLIST_H
#define ORDEREDLINKEDLIST_H
#include <iostream>

template <class Type>
struct Node
{
	Type data;
	Node *next;
};

template <class Type>
class OrderedLinkedList;

template <class Type>
std::ostream& operator<<(std::ostream&, const OrderedLinkedList<Type>& list);

//template <class Type>
//bool const operator < (const Type key, const Type key1);
//
//template <class Type>
//bool const operator == (const Type key);



template <class Type>
class OrderedLinkedList
{
public:
	OrderedLinkedList();
	OrderedLinkedList(const OrderedLinkedList& other);
	OrderedLinkedList<Type>& operator=(const OrderedLinkedList<Type>& other);

	~OrderedLinkedList();

    int size() const;
    bool empty() const;
	Type get(int) const;
	Type getFirst() const;
	Type getLast() const;
	void insert(const Type&);
	int find(const Type&) const;
	void remove(const Type&);
    void clear();
    OrderedLinkedList<Type> everyOtherOdd();
    OrderedLinkedList<Type> everyOtherEven();
    friend std::ostream& operator<< <>(std::ostream&, const OrderedLinkedList<Type>& list);
//    virtual bool const operator == (const Type key);
//    virtual bool const operator < (const Type key);

protected:
    Node<Type>* front;
    Node<Type>* back;
    int count = -1;
};

template <class Type>
OrderedLinkedList<Type>::OrderedLinkedList()
{
    front = nullptr;
    back = nullptr;
    count = 0;
}

template <class Type>
OrderedLinkedList<Type>::OrderedLinkedList(const OrderedLinkedList<Type>& other)
{
    if (other.count == 0){
        front = nullptr;
        back = nullptr;
        count = 0;
        return;
    }
    // first node
    int size = other.count;
    count = size;
    Node<Type>* first = new Node<Type>();
    auto currOtherNode = other.front;
    this->front = first;
    auto currentThisNode = this->front;
    front->data = other.front->data;

    for (int i = 1; i < size; i++){
        // Nodes for middle

        // creating new node
        Node<Type>* next = new Node<Type>();
        //setting previous node's pointer to current node
        currentThisNode->next = next;
        // incrementing
        currOtherNode = currOtherNode->next;
        currentThisNode = next;
        // setting data
        next->data = currOtherNode->data;
    }
    // last Node
    this->back = currentThisNode;
    back->next = nullptr;

//    Node<Type>* last = new Node<Type>();
//    this->back = nullptr;
////    currentThisNode->next = last;
//    currOtherNode = currOtherNode->next;
//    back = last;
//    back->data = currOtherNode->data;

}

template <class Type>
OrderedLinkedList<Type>& OrderedLinkedList<Type>::operator=(const OrderedLinkedList& other)
{
    if (other.count == 0){
        front = nullptr;
        back = nullptr;
        count = 0;
        return *this;
    }
    int this_size = this->count;
    // cleaning up the data
    Node<Type>* temp = this->front;
    for(int i = 0; i<this_size; i++){
        temp = this->front;
        this->front = temp->next;
        delete temp;
    }

    int size = other.count;
    this->count=size;
    Node<Type>* first = new Node<Type>();
    auto currOtherNode = other.front;
    this->front = first;
    this->front->data = other.front->data;
    auto currentThisNode = this->front;
    for (int i = 1; i < size; i++){
        // Nodes for middle

        // creating new node
        Node<Type>* next = new Node<Type>();
        //setting previous node's pointer to current node
        currentThisNode->next = next;
        // deleting data
        currOtherNode = currOtherNode->next;
        // incrementing

        currentThisNode = next;
        // setting data
        currentThisNode->data = currOtherNode->data;

    }
    // last Node
    back = currentThisNode;
    back->next = nullptr;
    // incrementing all nodes;
//    currentThisNode->next = last;
//    currOtherNode = currOtherNode->next;
//    back = last;




return *this;
}

template <class Type>
OrderedLinkedList<Type>::~OrderedLinkedList()
{
    Node<Type>* temp = front;

    while(front != nullptr){
        temp = front;
        front = front->next;
        delete temp;
    }
}

template <class Type>
int OrderedLinkedList<Type>::size() const
{
return count;
}

template <class Type>
bool OrderedLinkedList<Type>::empty() const
{
    if (count == 0){
        return true;
    }
    else {
        return false;
    }
}

template <class Type>
Type OrderedLinkedList<Type>::get(int pos) const
{
    if (pos > count || count == 0) {
        throw std::out_of_range("This position does not exist");
    }
    Node<Type>* temp = front;
    for (int i = 0; i<pos; i++) {
        temp = temp->next;
    }
   return temp->data;
}

template <class Type>
Type OrderedLinkedList<Type>::getFirst() const
{
    if (count < 1){
        throw std::out_of_range("The list is empty");
    }
   return front->data;
}

template <class Type>
Type OrderedLinkedList<Type>::getLast() const
{
    if (count < 1){
        throw std::out_of_range("The list is empty");
    }
   return back->data;
}

template <class Type>
void OrderedLinkedList<Type>::insert(const Type& item) {
    Node<Type> *newNode = new Node<Type>();
    newNode->data = item;
    // if no first node
    if (!front) {
        this->front = newNode;
        this->back = newNode;
        newNode->next = nullptr;
        count++;
    }
    //  if after last node
    else if (newNode->data > back->data){
        back->next = newNode;
        newNode->next = nullptr;
        back = newNode;
        count++;
    }
    // if before first node
    else if (newNode->data < front->data){
        newNode->next = front;
        front = newNode;
        count++;
    }
    // if between 1 and last node
    else if (front){
    auto temp = front;
    int temp_count = 0;
        while (temp != nullptr){
        if (temp->data < newNode->data){
            temp = temp->next;
            temp_count++;

        }
        else {
            temp = temp;
            break;
        }
    }
        temp = front;
        int i = 1;
        while (i != temp_count){
            temp = temp->next;
            i++;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        count++;
    }
}


template <class Type>
int OrderedLinkedList<Type>::find(const Type& item) const
{
    auto temp = front;
    int position = 0;
    while (temp != nullptr){
        if (temp->data == item){
            return position++;
        }
        else {
            temp = temp->next;
            position++;
        }
    }
    return -1;
}

template <class Type>
void OrderedLinkedList<Type>::remove(const Type& item)
{
    if (find(item) == -1){return;}
    else{
auto temp = front;
int temp_count = 0;
if (front->data== item){
    temp = temp->next;
    delete front;
    front = temp;
    count--;
}
else if (back->data == item){
    for (int i=0; i<count-2; i++){
        temp = temp->next;
    }
    delete back;
    temp->next = nullptr;
    back = temp;
    count--;
}
else {
    temp_count++;
    temp = temp->next;
while (temp != nullptr){
    if (temp->data == item){
        auto to_delete = temp;
        temp = front;
        for (int i = 0; i < temp_count-1; i++){
            temp = temp->next;
        }
        temp->next = to_delete->next;
        delete to_delete;
        count--;
        break;
    }
    else {
        temp = temp;
    }
}
}
}
}

template <class Type>
void OrderedLinkedList<Type>::clear()
{
    Node<Type>* temp = front;

    while(front != nullptr){
        temp = front;
        front = front->next;
        delete temp;
        count--;
    }
    front = nullptr;
    back = nullptr;
    count = 0;
//    front->next = nullptr;
//    back->next = nullptr;

}


template <class Type>
OrderedLinkedList<Type> OrderedLinkedList<Type>::everyOtherOdd() {
    if (this->front == NULL){return *this;}
    OrderedLinkedList<Type> retVal;
    auto temp = this->front;
    for (int i = 0; i < count; i++) {
        if ((i)%2 == 0){
            retVal.insert(temp->data);
            temp = temp->next;
        }
        else {
            temp = temp->next;
        }
    }

    return retVal;
}
//        retVal.insert(temp->data);
//        temp = temp->next;
//        if (temp != nullptr){
//            temp = temp->next;
//        }
//        else {return retVal;}
//        }







template <class Type>
OrderedLinkedList<Type> OrderedLinkedList<Type>::everyOtherEven(){
    if (this->front == NULL){return *this;}
    OrderedLinkedList<Type> retVal;
    auto temp = this->front;
    temp = temp->next;
//    retVal.insert(temp->data);
    for (int i = 1; i < count; i++) {
        if ((i)%2 != 0){
            retVal.insert(temp->data);
            temp = temp->next;
        }
        else{

            temp = temp->next;
        }
//        temp = temp->next;
//        if (temp != nullptr) {
//            temp = temp->next;
//            retVal.insert(temp->data);
//        }
//        else {return retVal;}
    }
return retVal;
}

template <class Type>
std::ostream& operator<<(std::ostream& out, const OrderedLinkedList<Type>& list) {
    if (!list.front){
        out << "";
    }
    else {
    auto temp = list.front;
    out<<temp->data;
    temp = temp->next;
    if (list.front != list.back){

    while (temp != nullptr) {
    out << "->" << temp->data;
    temp = temp->next;
    }
    }
    }
return out;
}
#endif

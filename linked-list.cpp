#include <cstdint>
#include <iostream>

template<class Value>
class SinglyLinkedList
{
  // POD-type

private:
  template<class NodeValue>
  struct SinglyLinkedNode
  {
    NodeValue value;
    SinglyLinkedNode<NodeValue> *next;

    SinglyLinkedNode(
      NodeValue value, SinglyLinkedNode<NodeValue> *next = nullptr)
    {
      this->value = value;
      this->next = next;
    }
  };

  typedef SinglyLinkedNode<Value> Node;

  // ! Head and Tail must always point to something, .
  // or both point to nothing (null)
  Node *_head = nullptr;
  Node *_tail = nullptr;
  uint64_t _size = 0;

public:
  SinglyLinkedList() {}
  ~SinglyLinkedList()
  {
    // free all the nodes
  }

  void push(Value v)
  {
    Node *newNode = new Node(v);

    // if both point to the same thing
    if (this->_head == this->_tail)
    {
      // both could be null, so point to the new node
      if (this->_head == nullptr) { this->_head = this->_tail = newNode; }
      else {
        this->_tail = newNode;
        this->_head->next = this->_tail;
      }
    }
    else {
      Node *currentTail = this->_tail;
      currentTail->next = newNode;
      this->_tail = newNode;
    }

    ++this->_size;
  }

  uint64_t size() { return this->_size; }

  Value front()
  {
    if (this->_head == nullptr) { throw "Error: front is null"; }

    return this->_head->value;
  }

  Value back()
  {
    if (this->_tail == nullptr) { throw "Error: backk= is null"; }

    return this->_tail->value;
  }

  void pop()
  {
    // if both point to the same thing
    if (this->_head == this->_tail)
    {
      if (this->_head != nullptr)
      {
        // both point to the same node,
        Node *currentNode = this->_head;

        this->_tail = this->_head = nullptr;

        delete currentNode;
        --this->_size;
      }
    }
    else {
      Node *previousNode;
      Node *currentNode = this->_head;

      // walk the list
      while (currentNode != this->_tail)
      {
        previousNode = currentNode;
        currentNode = currentNode->next;
      }

      previousNode->next = nullptr;

      this->_tail = previousNode;
      --this->_size;
    }
  }
};

int main()
{
  // your code here
  return 0;
}

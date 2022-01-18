#include <cstdint>
#include <iostream>
#include <string>

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

    SinglyLinkedNode(NodeValue value, SinglyLinkedNode<NodeValue> *next = NULL)
    {
      this->value = value;
      this->next = next;
    }
  };

  typedef SinglyLinkedNode<Value> Node;

  // ! Head and Tail must always point to something, .
  // or both point to nothing (null)
  Node *_head = NULL;
  Node *_tail = NULL;
  size_t _size = 0;

public:
  SinglyLinkedList() {}
  ~SinglyLinkedList()
  {
    // Unimplemented: free all the nodes
  }

  void push(Value v)
  {
    Node *newNode = new Node(v);

    // if both point to the same thing
    if (this->_head == this->_tail)
    {
      // both could be null, so point to the new node
      if (this->_head == NULL) { this->_head = this->_tail = newNode; }
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

  size_t size() const { return this->_size; }

  Value front() const
  {
    if (this->_head == NULL) { throw "Error: front is null"; }

    return this->_head->value;
  }

  Value back() const
  {
    if (this->_tail == NULL) { throw "Error: back= is null"; }

    return this->_tail->value;
  }

  const Value &operator[](size_t index) const
  {
    if (index >= this->_size - 1) { throw "Error: index out of bounds"; }

    Node *curentNode = this->_head;
    for (size_t i = 0; i < index; ++i) { curentNode = curentNode->next; }

    return curentNode->value;
  }

  void pop()
  {
    // if both point to the same thing
    if (this->_head == this->_tail)
    {
      if (this->_head != NULL)
      {
        // both point to the same node,
        Node *currentNode = this->_head;

        this->_tail = this->_head = NULL;

        delete currentNode;
        --this->_size;
      }
    }
    else {
      Node *previousNode = NULL;
      Node *currentNode = this->_head;

      // walk the list
      while (currentNode != this->_tail)
      {
        previousNode = currentNode;
        currentNode = currentNode->next;
      }

      previousNode->next = NULL;

      this->_tail = previousNode;
      --this->_size;
    }
  }
};

int main()
{
  std::string studentName;
  SinglyLinkedList<double> testScores;

  std::cout << "Input Name: ";
  std::getline(std::cin, studentName);

  for (uint64_t i = 1; i < 5; ++i)
  {
    double testScore = 0;
    std::cout << "Input Test Score #" << i << " (Up to 100 Points): ";
    std::cin >> testScore;
    testScores.push(testScore);
  }

  double accumulator = 0;
  for (uint64_t i = 1; i < 5; ++i)
  {
    accumulator += testScores.back();
    testScores.pop();
  }

  std::cout << "Your Average Is: " << accumulator / 4 << std::endl;

  return 0;
}

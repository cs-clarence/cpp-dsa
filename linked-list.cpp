#include <iostream>
#include <stdint.h>
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

struct Student
{
  std::string name;
  SinglyLinkedList<double> testScores;
  double average;
};

int main()
{
  SinglyLinkedList<Student> students;

  size_t studentNumber = 1;
  while (true)
  {
    std::cout << "===================================================="
              << std::endl;
    std::cout << "Student Number #" << studentNumber << std::endl;
    Student student;
    std::cout << "Input Name: ";
    std::getline(std::cin, student.name);

    double accumulator = 0;
    for (uint64_t i = 1; i < 5; ++i)
    {
      double testScore = 0;
      std::cout << "Input Test Score #" << i << " (Up to 100 Points): ";
      std::cin >> testScore;
      accumulator += testScore;
      student.testScores.push(testScore);
    }

    student.average = accumulator / 4;

    students.push(student);

    std::cout << "Average: " << student.average << std::endl;

    int answer = 0;
    std::cout << "Add more students? 1 = yes: ";
    std::cin >> answer;

    if (answer != 1) { break; }

    std::cin.ignore(1, '\n');
    ++studentNumber;
  }

  std::cout << "===================================================="
            << std::endl;
  while (students.size() != 0)
  {
    Student student = students.back();
    students.pop();

    double testScore1 = student.testScores.back();
    student.testScores.pop();
    double testScore2 = student.testScores.back();
    student.testScores.pop();
    double testScore3 = student.testScores.back();
    student.testScores.pop();
    double testScore4 = student.testScores.back();
    student.testScores.pop();

    std::cout << "STUDENT NAME: " << student.name
              << "\tTEST SCORE #1: " << testScore1
              << "\tTEST SCORE #2: " << testScore2
              << "\tTEST SCORE #3: " << testScore3
              << "\tTEST SCORE #4: " << testScore4
              << "\tAVERAGE: " << student.average << std::endl;
  }

  return 0;
}

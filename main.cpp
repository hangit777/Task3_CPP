#include <iostream>
#include <string>
#include <utility>

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        explicit Node(T  d, Node* p = nullptr, Node* n = nullptr)
                : data(std::move(d)), prev(p), next(n) {}
    };
    Node* head;
    Node* tail;
    size_t size;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }
    bool empty() const {
        return size == 0;
    }
    size_t length() const {
        return size;
    }
    void push_front(const T& value) {
        Node* newNode = new Node(value, nullptr, head);
        if (head != nullptr) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
        ++size;
    }
    void push_back(const T& value) {
        Node* newNode = new Node(value, tail, nullptr);
        if (tail != nullptr) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
        ++size;
    }
    void pop_front() {
        if (head != nullptr) {
            Node* temp = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
            delete temp;
            --size;
        }
    }
    void pop_back() {
        if (tail != nullptr) {
            Node* temp = tail;
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            } else {
                head = nullptr;
            }
            delete temp;
            --size;
        }
    }
    void insert(size_t index, const T& value) {
        if (index <= 0) {
            push_front(value);
        } else if (index >= size) {
            push_back(value);
        } else {
            Node* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            Node* newNode = new Node(value, current->prev, current);
            current->prev->next = newNode;
            current->prev = newNode;
            ++size;
        }
    }
    void remove(size_t index) {
        if (index < 0 || index >= size) {
            return;
        }
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        if (current == head) {
            pop_front();
        } else if (current == tail) {
            pop_back();
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            --size;
        }
    }
    void print() const {
        std::cout << "[";
        if (head != nullptr) {
            std::cout << head->data;
            Node* current = head->next;
            while (current != nullptr) {
                std::cout << ", " << current->data;
                current = current->next;
            }
        }
        std::cout << "]" << std::endl;
    }
};

int main() {
    DoublyLinkedList<int> intList;
    intList.push_back(1);
    intList.push_back(2);
    intList.push_back(3);
    intList.push_front(0);
    intList.insert(2, 100);
    intList.print();
    intList.remove(2);
    intList.print();
    DoublyLinkedList<std::string> stringList;
    stringList.push_back("red");
    stringList.push_back("yellow");
    stringList.push_back("orange");
    stringList.push_front("green");
    stringList.insert(2, "black");
    stringList.print();
    stringList.remove(2);
    stringList.print();
    int size = stringList.length();
    while (!stringList.empty()){
        stringList.pop_back();
        stringList.print();
    }
    if(stringList.empty()){
        std::cout<< "Empty list"<<std::endl;
    }else{
       std::cout<< stringList.length()<<std::endl;
    }
    return 0;
}

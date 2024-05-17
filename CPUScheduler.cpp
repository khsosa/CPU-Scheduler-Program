#include <iostr

using namespace std;

class Process {
public:
    int totalTime;
    string processName;

    Process (string processName, int totalTime){
        this->processName = processName;
        this->totalTime = totalTime;
    }

    void updateRunTime(int quantum) {
        this->totalTime-=quantum;
    }
    void print () {
        cout << "Process " << processName << " " << totalTime << " seconds" << endl;
    }
};

// Node Class: Node for the DoublyLinkedList
template <typename T> class Node {
public:
    T *data;
    Node<T> *next;
    Node<T> *prev;

    Node (T *data) {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }

    void print () {
        data->print ();
    }
};

template <typename T> class CircularDLL {
public:
    Node<T> *curr;
    int length;

    CircularDLL(T *data) {
        Node<T> *newNode = new Node<T>(data);
        newNode->next = newNode;
        newNode->prev = newNode;
        curr = newNode;
        length = 1;
    }


    ~CircularDLL() {
        if(curr == nullptr){
            return;
        }
        Node <T> *current = curr->next;
        while(current!=curr){
            Node<T> *temp = current;
            current = current->next;
            delete temp->data;
            delete temp;
        }
        delete curr->data;
        delete curr;
    }


    void printList() {
        if(curr == nullptr){
            cout<< "List Empty" << endl;
            return;
        }
        Node<T> *current = curr->next;
        int count = 1;
        while(current != curr) {
            cout << count << ". ";
            current->print();
            current = current->next;
            count++;
        }
    }

    void insertProcess(T *data) {
        Node<T> *newNode = new Node<T>(data);
        if(length == 0){
            curr->next = newNode;
            curr->prev = newNode;
            newNode->next = curr;
            newNode->prev = curr;
        }else{
            newNode->next = curr;
            newNode->prev = curr->prev;
            curr->prev->next = newNode;
            curr->prev = newNode;
        }
        length++;
    }


    void deleteProcess(Node <T> *beingDeleted){
        //write code to delete process here
        if(length == 0|| beingDeleted == nullptr){
            cout << "Empty" << endl;
            return;
        }else{
            beingDeleted->prev->next = beingDeleted->next;
            beingDeleted->next->prev = beingDeleted->prev;
            if(curr == beingDeleted){
                curr=beingDeleted->next;
            }
            delete beingDeleted->data;
            delete beingDeleted;
            length--;
        }
    }
};


int main() {
    int quantum;
    int cycle = 1;
    char newProcessCheck = 'Y';
    string processName;
    int totalTime;
    Process *newProcess;
    int counter = 5;

    cout << "Enter quantum time: ";
    cin >> quantum;
    cout << " " << endl;
    cout << "Prepopulating with processes: " << endl;
    cout << " " << endl;

    CircularDLL<Process> *ll1 = new CircularDLL<Process>(newProcess);
    newProcess = new Process("A ", 10);
    ll1->insertProcess(newProcess);
    newProcess = new Process("B ", 12);
    ll1->insertProcess(newProcess);
    newProcess = new Process("C ", 8);
    ll1->insertProcess(newProcess);
    newProcess = new Process("D ", 5);
    ll1->insertProcess(newProcess);
    newProcess = new Process("E ", 10);
    ll1->insertProcess(newProcess);
    ll1->printList();
    cout << " " << endl;
    bool finished = false;
    while (!finished) {
        cout << "Add new process? (Enter Y/N)";
        cin >> newProcessCheck;
        cout << " " << endl;
        if (newProcessCheck == 'Y' || newProcessCheck == 'y') {
            while (newProcessCheck == 'Y' || newProcessCheck == 'y') {
                cout << "Enter new process name: ";
                cin >> processName;
                cin.ignore();
                cout << " " << endl;
                cout << "Enter total process time: ";
                cin >> totalTime;
                cout << " " << endl;
                newProcess = new Process(processName, totalTime);
                ll1->insertProcess(newProcess);
                cout << "Process Added." << endl;
                cout << " " << endl;
                cout << "Add new process? (Enter Y/N)";
                cin >> newProcessCheck;
                cout << " " << endl;
            }
        }

        cout << "Running cycle " << cycle << endl;
        cout << " " << endl;
        cout << "After cycle " << cycle << " - " << counter << " second elapses - state of process is as follows: ";
        cout << " " << endl;
        Node<Process> *current = ll1->curr->next;
        while (current != ll1->curr) {
            current->data->updateRunTime(quantum);
            current = current->next;
        }
        current = ll1->curr->next;
        while (current != ll1->curr) {
            if (current->data->totalTime <= 0) {
                Node<Process> *temp = current->next;
                ll1->deleteProcess(current);
                current = temp;
            } else {
                current = current->next;
            }
        }
        ll1->printList();
        cout << endl;
        cycle++;
        counter += 5;
        if (ll1->curr->next == ll1->curr && ll1->curr->prev == ll1->curr) {
            finished = true;
        }
    }

    cout << "All processes are completed" << endl;
    return 0;
}

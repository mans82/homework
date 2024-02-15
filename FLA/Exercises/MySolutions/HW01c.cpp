#include <map>
#include <vector>
#include <string>
#include <iostream>

using Node = int;
using Alphabet = char;

class DFA {
    public:
        DFA(Node startingNode) : startingNode{startingNode}, currentNode{startingNode} {}

        void addTransition(Alphabet alphabet, Node from, Node to) {
            this->transitions[from][alphabet] = to;
        }

        void setAccept(Node node, bool isAccept) {
            this->acceptingNodesTable[node] = isAccept;
        }

        bool isAcceptable() {
            return this->acceptingNodesTable[currentNode];
        }

        bool failed() const {
            return this->_failed;
        }

        void testString(std::string strToTest) {
            reset();
            for (char c : strToTest) {
                read(c);
                if (failed()) return;
                _passedNodes.push_back(currentNode);
            }
        }

        std::vector<Node> passedNodes() {
            return _passedNodes;
        }
        
    
    private:
        std::map<Node, std::map<Alphabet, Node>> transitions {};
        std::map<Node, bool> acceptingNodesTable {};
        Node startingNode {0};
        Node currentNode {0};
        std::vector<Node> _passedNodes {};
        bool _failed = false;

        void reset() {
            _failed = false;
            currentNode = startingNode;
            _passedNodes.clear();
        }

        void read(Alphabet alphabet) {
            if (_failed) return;
            if (isTransitionValid(currentNode, alphabet)) {
                doTransition(alphabet);
            } else {
                _failed = true;
            }
        }

        bool isTransitionValid(Node node, Alphabet alphabet) {
            return transitions[node][alphabet] != 0;
        }

        void doTransition(Alphabet alphabet) {
            currentNode = transitions[currentNode][alphabet];
        }

};

int main() {

    using std::cin;
    using std::cout;
    using std::endl;

    int n, m, s, q;

    cin >> n >> m >> s >> q;
    DFA mainDfa(s);

    for (int i = 0; i < n; i++) {
        bool isAccept;
        cin >> isAccept;
        mainDfa.setAccept(i + 1, isAccept);
    }

    for (int i = 0; i < m; i++) {
        Alphabet transitionAlphabet;
        Node from;
        Node to;

        cin >> transitionAlphabet >> from >> to;

        mainDfa.addTransition(transitionAlphabet, from, to);
    }

    for (int i = 0; i < q; i++) {
        std::string input;
        cin >> input;

        mainDfa.testString(input);

        if (!mainDfa.failed() && mainDfa.isAcceptable()) {
            cout << "Yes ";
        } else {
            cout << "No ";
        }

        for (Node passedNode : mainDfa.passedNodes()) {
            cout << passedNode << " ";
        }
        cout << endl;
    }

    return 0;
}
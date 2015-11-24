#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;
using std::flush;

class oset;
void print(oset& OS);       // for debugging

// Non-generic starter code.
//
// *** THIS SKELETON ENVISIONS INTEGER ELEMENTS.
// *** YOUR VERSION SHOULD BE POLYMORPHIC.
//
class oset {
    class node {
     public:
        const int val;
        node *next;
        node(int v) : val(v), next(NULL) { }
    };
    node head;
        // NB: _not_ node*.  There's a dummy node here, with garbage val;
        // Existence of this node avoids several special cases in the
        // methods below.
    node beyond;
        // to simplify iterator.

    //--------------------------------------
    // Iterator support

 public:
    class iter {
        node *pos;          // node _before_ the one with this->operator*
        // constructor is private:
        iter(node* n) : pos(n) { }
    friend class oset;      // so oset can call the (private) constructor
    public:   
        const int& operator*() {
            return pos->next->val;
        }
        // support forward iteration.  This is prefix version (++p).
        iter& operator++() {
            if (pos != NULL) pos = pos->next;
            return *this;
        }
        // and this is the postfix version (p++).
        // Note that it returns a copy, _not_ a reference.
        iter operator++(int) {
            iter rtn = *this;
            if (pos != NULL) pos = pos->next;
            return rtn;
        }
        bool operator==(iter other) {return pos->next == other.pos->next;}
        bool operator!=(iter other) {return pos->next != other.pos->next;}
    };

 private:
    iter start;         // initialized in the constructors below
    iter finish;        // initialized in the constructors below

 public:
    iter begin() {
        return start;
    }
    iter end() {
        return finish;
    }

    //--------------------------------------
    // Constructors and destructor

    // new empty set:
    oset() : head(0), beyond(0), start(&head), finish(&beyond) {
        head.next = NULL;
    }

    // new singleton set:
    oset(int v) : head(0), beyond(0), start(&head), finish(&beyond) {
        head.next = new node(v);
    }

    // copy constructor:
    oset(oset& other) : head(0), beyond(0), start(&head), finish(&beyond) {
        node *o = other.head.next;
        node *n = &head;
        while (o) {
            n->next = new node(o->val);
            o = o->next;
            n = n->next;
        }
        n->next = NULL;
    }

 private:
    void clear() {
        node *n = head.next;
        while (n) {
            node* t = n->next;
            delete n;
            n = t;
        }
        head.next = NULL;
    }

 public:
    // destructor -- clean up nodes:
    ~oset() {
        clear();
    }
    // assignment
    oset& operator=(oset& other) {
        clear();
        operator+=(other);      // union (see below)
    }

    //--------------------------------------
    // Find, insert, and remove

private:
    // Return pointer to last node with val < v
    //
    // *** THIS CODE IMPLICITLY REQUIRES A >= OPERATOR FOR THE SET
    // *** ELEMENT TYPE.  YOU NEED TO MAKE THAT EXPLICIT
    // *** (IN DIFFERENT WAYS IN DIFFERENT VERSIONS OF THE CODE).
    //
    node* find_prev(const int v) {
        node* p = &head;
        while (true) {
            if (p->next == NULL) return p;
            if (p->next->val >= v) return p;
            p = p->next;
        }
    }
        
public:
    // find -- return true iff present:
    bool operator[](const int v) {
        node* p = find_prev(v);
        return (p->next != NULL && p->next->val == v);
    }

    // insert v if not already present; return ref to self
    oset& operator+=(const int v) {
        node* p = find_prev(v);
        if (p->next == NULL || p->next->val != v) {
            node* n = new node(v);
            n->next = p->next;
            p->next = n;
        }
        return *this;
    }

    // remove v if present; return ref to self
    oset& operator-=(const int v) {
        node* p = find_prev(v);
        node* t;
        if ((t = p->next) != NULL && p->next->val == v) {
            // already present
            p->next = t->next;
            delete t;
        }
        return *this;
    }

    //--------------------------------------
    // Union, intersection and difference.
    // These are operator assignments, to simplify management of space:
    // programmer is forced to manage temporaries explicitly
    // (as illustrated in the code for intersection below).

    // Union.
    //
    // *** THIS CODE HAS COST O(N^2).  IT SHOULD BE O(N).
    //
    oset& operator+=(oset& other) {
//        for (iter i = other.begin(); i != other.end(); ++i) {
//            operator+=(*i);
//        }
        iter i = begin();
        iter j = other.begin();
        while(i != end() && j != other.end()){
          if(*i == *j){
                ++i;
                ++j;
            } else if (*i < *j) {
//                operator+=(*j);
                node* n = new node(*j);
                n->next = i.pos->next;
                i.pos->next = n;
                ++i;
            } else {
                //operator+=(*j);
                node* n = new node(*j);
                n->next = i.pos->next;
                i.pos->next = n;
                ++j;
            }
        }
        if(i == end()){
            while (j != other.end()) {
//                operator+=(*j);
                node* n = new node(*j);
                n->next = i.pos->next;
                i.pos->next = n;
                ++j;
            }
        }

        return *this;
    }

    // Set difference.
    //
    // *** THIS CODE HAS COST O(N^2).  IT SHOULD BE O(N).
    //
    oset& operator-=(oset& other) {
        for (iter i = other.begin(); i != other.end(); ++i) {
            operator-=(*i);
        }
        return *this;
/*
        iter i = begin();
        iter j = other.begin();
        while(i != other.end() && j != end()){
          if(*i == *j){
                ++j;
                ++i;
            } else if (*i < *j) {
//                operator+=(*j);
                node* t = i.pos->next;
                i.pos->next = t->next;
                delete t;
//                node* n = new node(*j);
//                n->next = i.pos->next;
//                i.pos->next = n;
                ++i;
            } else {
                //operator+=(*j);
                node* t = i.pos->next;
                i.pos->next = t->next;
                delete t;
//                node* n = new node(*j);
//                n->next = i.pos->next;
//                i.pos->next = n;
                ++j;
            }
        }
        if(i == end()){
            while (j != other.end()) {
                //operator+=(*j);
                node* t = i.pos->next;
                i.pos->next = t->next;
                delete t;
//                node* n = new node(*j);
//                n->next = i.pos->next;
//                i.pos->next = n;
                ++j;
            }
        }
*/
        return *this;
    }

    // Intersection.
    //
    // *** THIS CODE HAS COST O(N^2).  IT SHOULD BE O(N).
    //
    oset& operator*=(oset& other) {
        oset temp;      // empty
        for (iter i = begin(); i != end(); ++i) {
            if (other[*i]) temp+=(*i);
        }
        clear();
        operator+=(temp);   // union
        // NB: temp is destructed as we leave this scope
        return *this;
    }
};

void print(oset& OS) {
    for (oset::iter i = OS.begin(); i != OS.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
}
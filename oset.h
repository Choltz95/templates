#include <iostream>
#include <typeinfo>
#include <string.h>

using std::cout;
using std::endl;
using std::flush;

template <class T> class oset;
template <class T> void print(oset<T>& OS);       // for debugging

template <class T>
class oset {
    class node {
     public:
        const T val;
        node *next;
        node(T v) : val(v), next(NULL) { }
        node(): val(), next(NULL) { }
    };
    int(*comparator)(const T x, const T y);
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
        const T& operator*() {
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
    oset(int(*f)(const T x, const T y)) : head(), beyond(), start(&head), finish(&beyond) {
        head.next = NULL;
        comparator = f;
    }

    // new singleton set:
    oset(T v, int(*f)(const T x, const T y)) : head(), beyond(), start(&head), finish(&beyond) {
        head.next = new node(v);
        comparator = f;
    }

    // copy constructor:
    oset(oset& other, int(*f)(const T x, const T y)) : head(), beyond(), start(&head), finish(&beyond) {
        node *o = other.head.next;
        node *n = &head;
        comparator = f;
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
    // *** ELEMENT TYPE. YOU NEED TO MAKE THAT EXPLICIT
    // *** (IN DIFFERENT WAYS IN DIFFERENT VERSIONS OF THE CODE).
    //
    node* find_prev(T v) {
        node* p = &head;
        while (true) {
            if (p->next == NULL) return p;
            if (comparator(p->next->val, v) == 0 || comparator(p->next->val, v) > 0) return p; // comparator
            p = p->next;
        }
    }
        
public:
    // find -- return true iff present:
    bool operator[](T v) {
        node* p = find_prev(v);
        return (p->next != NULL && p->next->val == v);
    }

    // insert v if not already present; return ref to self
    oset& operator+=(T v) {
        node* p = find_prev(v);
        if (p->next == NULL || p->next->val != v) {
            node* n = new node(v);
            n->next = p->next;
            p->next = n;
        }
        return *this;
    }

    // remove v if present; return ref to self
    oset& operator-=(T v) {
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
    oset& operator+=(oset& other) {
        // comparators not equivalent, use n^2 algorithm
        if(comparator != other.comparator) {
            for (iter i = other.begin(); i != other.end(); ++i) {
                operator+=(*i);
            }
        }

        iter i = begin();
        iter j = other.begin();
        while(i != end() && j != other.end()){
          //if(*i == *j){
            if(comparator(*i, *j) == 0){
                ++i;
                ++j;
            } else if (comparator(*i, *j) < 0) {
            //else if (*i < *j) {
                ++i;
            } else {
                node* n = new node(*j);
                n->next = i.pos->next;
                i.pos->next = n;
                ++j;
            }
        }
        if(i == end()){
            while (j != other.end()) {
                node* n = new node(*j);
                i.pos->next = n;
                ++j;
                ++i;
            }
        }
        return *this;
    }
    /*
    oset& operator n2+=(oset& other) {
        for (iter i = other.begin(); i != other.end(); ++i) {
            operator+=(*i);
        }
    }
    */
    // Set difference.
    oset& operator -=(oset& other) {
        if(comparator != other.comparator) {
            for (iter i = other.begin(); i != other.end(); ++i) {
                operator-=(*i);
            }
        }

        iter i = begin();
        iter j = other.begin();
        while(i != end() && j != other.end()){
          if(comparator(*i, *j) == 0){
                node* t;
                if ((t = i.pos->next) != NULL && i.pos->next->val == *j) {
                    // already present
                    i.pos->next = t->next;
                    delete t;
                }
                ++j;
            } else if (comparator(*i, *j) < 0) {
                ++i;
            } else {
                ++j;
            }
        }
        return *this;
    }
    /*
    oset& operator n2-=(oset& other) {
        for (iter i = other.begin(); i != other.end(); ++i) {
            operator-=(*i);
        }
    }
    */
    // Intersection
    oset& operator*=(oset& other) {
        oset temp(comparator); // take comparator of this in 'this.intersect(...)'
        
        if(comparator != other.comparator) {
            for (iter i = begin(); i != end(); ++i) {
                if (other[*i]) temp+=(*i);
            }
            clear();
            operator+=(temp);   // union
            // NB: temp is destructed as we leave this scope
            return *this;
        }

        iter i = begin();
        iter j = other.begin();
        iter k = temp.begin();
        while(i != end() && j != other.end()){
          if(comparator(*i, *j) == 0){
                node* n = new node(*i);
                k.pos->next = n;
                ++j;
                ++k;
            } else if (comparator(*i, *j) < 0) {
                ++i;
            } else {
                ++j;
            }
        }

        clear();
        operator+=(temp);   // union
        // NB: temp is destructed as we leave this scope
        return *this;
    }
    /*
    oset& operator n2*=(oset& other) {
        oset temp;      // empty
        for (iter i = begin(); i != end(); ++i) {
            if (other[*i]) temp+=(*i);
        }
        clear();
        operator+=(temp);   // union
        // NB: temp is destructed as we leave this scope
        return *this;
    }
    */
};

// set printer
template <class T> 
void print(oset<T>& OS) {
    for (typename oset<T>::iter i = OS.begin(); i != OS.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
}
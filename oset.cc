/*
    Starter code for assignment 5, CSC 254, Fall 2015

    Provides skeleton of code for generic ordered sets.

    Everything but /main/ should be moved to a .h file, which should
    then be #included from here.

    Be sure to read the assignment web page carefully.
    Then search for all-caps comments preceded by '***' for hints as to
    where you should make changes.

    A couple warnings:

    (1) Don't try to modify an oset while you're iterating over it.
        The following may not work:
            for (oset::iter i = begin(); i != end(); ++i) {
                if (!other[*i]) operator-=(*i);
            }

    (2) Don't try to modify an oset in the middle of a string of output:
        The following may not work:
            cout << (S += 9) << " " << S[9] << endl;
        (Because this is all one expression, the compiler is free to
        evaluate S[9] before it evaluates (S += 9)).
*/
#include "oset.h"


int comparator_cs(const std::string x, const std::string y) {
    //return strcmp(x,y);
    if (x == y){
        return 0;
    } else if (x > y){
        return 1;
    } else {
        return -1;
    }
}

int comparator_ci(const std::string x, const std::string y) {

    if (x == y){
        return 0;
    } else if (x > y){
        return 1;
    } else {
        return -1;
    }
}

int comparator_int(const int x, const int y) {
    if (x == y){
        return 0;
    } else if (x > y){
        return 1;
    } else {
        return -1;
    }
}

int comparator_d( double x, const double y) {
    if (x == y){
        return 0;
    } else if (x > y){
        return 1;
    } else {
        return -1;
    }
}

int main() { 
    cout << "*****INTS*****" << endl;

    oset <int> S(comparator_int);     // empty set
    S += 3;     // now should contain 3

    cout << S[3] << " ";            // should print 1 (true) : 3 is in S
    S += 3;                         // should be a no-op
    cout << S[5] << endl;           // should print 0 (false) : 5 not in S

    (S += 5) += 7;
    print(S);                       // should print 3 5 7

    oset <int> T(3,comparator_int);                      // singleton

    print(T);                       // should print 3

    oset <int> U(S, comparator_int);                      // copy of S
    oset <int> V(S, comparator_int);                      // copy of S

    oset <int> W(comparator_int);  W = S;  print(W);      // 3 5 7

    S -= 4;                         // should be a no-op
    S -= 3;
    U -= 5;
    V -= 7;
    print(S);                       // 5 7
    print(U);                       // 3 7
    print(V);                       // 3 5

    oset <int> A(comparator_int);  ((A += 5) += 3) += 4;  print(A);       // 3 4 5
    oset <int> B(comparator_int);  ((B += 6) += 5) += 7;  print(B);       // 5 6 7

    oset <int> AuB(A,comparator_int);  AuB += B;  print(AuB);            // 3 4 5 6 7
    oset <int> AmB(A,comparator_int);  AmB -= B;  print(AmB);            // 3 4
    oset <int> AiB(A,comparator_int);  AiB *= B;  print(AiB);            // 5


    cout << "*****DOUBLES*****" << endl;

    oset <double> Sd(comparator_d);     // empty set
    Sd += 3.1;     // now should contain 3

    cout << Sd[3.1] << " ";            // should print 1 (true) : 3 is in S
    Sd += 3.1;                         // should be a no-op
    cout << Sd[5.1] << endl;           // should print 0 (false) : 5 not in S

    (Sd += 5.1) += 7.1;
    print(Sd);                       // should print 3 5 7

    oset <double> Td(3.1,comparator_d);                      // singleton

    print(Td);                       // should print 3

    oset <double> Ud(Sd,comparator_d);                      // copy of S
    oset <double> Vd(Sd,comparator_d);                      // copy of S

    oset <double> Wd(comparator_d);  Wd = Sd;  print(Wd);      // 3 5 7

    Sd -= 4.1;                         // should be a no-op
    Sd -= 3.1;
    Ud -= 5.1;
    Vd -= 7.1;
    print(Sd);                       // 5 7
    print(Ud);                       // 3 7
    print(Vd);                       // 3 5

    oset <double> Ad(comparator_d);  ((Ad += 5.1) += 3.1) += 4.1;  print(Ad);       // 3 4 5
    oset <double> Bd(comparator_d);  ((Bd += 6.1) += 5.1) += 7.1;  print(Bd);       // 5 6 7

    oset <double> AuBd(Ad,comparator_d);  AuBd += Bd;  print(AuBd);            // 3 4 5 6 7
    oset <double> AmBd(Ad,comparator_d);  AmBd -= Bd;  print(AmBd);            // 3 4
    oset <double> AiBd(Ad,comparator_d);  AiBd *= Bd;  print(AiBd);            // 5
    
    cout << "*****STRINGS*****" << endl;

    oset <std::string> Ss(comparator_cs);     // empty set
    Ss += "a";     // now should contain 3

    cout << Ss["a"] << " ";            // should print 1 (true) : 3 is in S
    Ss += "a";                         // should be a no-op
    cout << Ss["c"] << endl;           // should print 0 (false) : 5 not in S

    (Ss += "c") += "d";
    print(Ss);                       // should print 3 5 7

    oset <std::string> Ts("a", comparator_cs);                      // singleton

    print(Ts);                       // should print 3

    oset <std::string> Us(Ss, comparator_cs);                      // copy of S
    oset <std::string> Vs(Ss, comparator_cs);                      // copy of S

    oset <std::string> Ws(comparator_cs);  Ws = Ss;  print(Ws);      // 3 5 7

    Ss -= "b";                         // should be a no-op
    Ss -= "a";
    Us -= "c";
    Vs -= "d";
    print(Ss);                       // 5 7
    print(Us);                       // 3 7
    print(Vs);                       // 3 5

    oset <std::string> As(comparator_cs);  ((As += "c") += "a") += "b";  print(As);       // 3 4 5
    oset <std::string> Bs(comparator_cs);  ((Bs += "e") += "c") += "d";  print(Bs);       // 5 6 7

    oset <std::string> AuBs(As, comparator_cs); AuBs += Bs; print(AuBs);            // 3 4 5 6 7
    oset <std::string> AmBs(As, comparator_cs); AmBs -= Bs; print(AmBs);            // 3 4
    oset <std::string> AiBs(As, comparator_cs); AiBs *= Bs; print(AiBs);            // 5 

// TESTS WITHOUT COMPARATOR ARGUMENT
/*    
    cout << "*****INTS*****" << endl;

    oset <int> S;     // empty set
    S += 3;     // now should contain 3

    cout << S[3] << " ";            // should print 1 (true) : 3 is in S
    S += 3;                         // should be a no-op
    cout << S[5] << endl;           // should print 0 (false) : 5 not in S

    (S += 5) += 7;
    print(S);                       // should print 3 5 7

    oset <int> T(3);                      // singleton

    print(T);                       // should print 3

    oset <int> U(S);                      // copy of S
    oset <int> V(S);                      // copy of S

    oset <int> W;  W = S;  print(W);      // 3 5 7

    S -= 4;                         // should be a no-op
    S -= 3;
    U -= 5;
    V -= 7;
    print(S);                       // 5 7
    print(U);                       // 3 7
    print(V);                       // 3 5

    oset <int> A;  ((A += 5) += 3) += 4;  print(A);       // 3 4 5
    oset <int> B;  ((B += 6) += 5) += 7;  print(B);       // 5 6 7

    oset <int>  AuB(A);  AuB += B;  print(AuB);            // 3 4 5 6 7
    oset <int> AmB(A);  AmB -= B;  print(AmB);            // 3 4
    oset <int> AiB(A);  AiB *= B;  print(AiB);            // 5

    cout << "*****DOUBLES*****" << endl;

    oset <double> Sd;     // empty set
    Sd += 3.1;     // now should contain 3

    cout << Sd[3.1] << " ";            // should print 1 (true) : 3 is in S
    Sd += 3.1;                         // should be a no-op
    cout << Sd[5.1] << endl;           // should print 0 (false) : 5 not in S

    (Sd += 5.1) += 7.1;
    print(Sd);                       // should print 3 5 7

    oset <double> Td(3.1);                      // singleton

    print(Td);                       // should print 3

    oset <double> Ud(Sd);                      // copy of S
    oset <double> Vd(Sd);                      // copy of S

    oset <double> Wd;  Wd = Sd;  print(Wd);      // 3 5 7

    Sd -= 4.1;                         // should be a no-op
    Sd -= 3.1;
    Ud -= 5.1;
    Vd -= 7.1;
    print(Sd);                       // 5 7
    print(Ud);                       // 3 7
    print(Vd);                       // 3 5

    oset <double> Ad;  ((Ad += 5.1) += 3.1) += 4.1;  print(Ad);       // 3 4 5
    oset <double> Bd;  ((Bd += 6.1) += 5.1) += 7.1;  print(Bd);       // 5 6 7

    oset <double> AuBd(Ad);  AuBd += Bd;  print(AuBd);            // 3 4 5 6 7
    oset <double> AmBd(Ad);  AmBd -= Bd;  print(AmBd);            // 3 4
    oset <double> AiBd(Ad);  AiBd *= Bd;  print(AiBd);            // 5

    cout << "*****STRINGS*****" << endl;

    oset <std::string> Ss;     // empty set
    Ss += "a";     // now should contain 3

    cout << Ss["a"] << " ";            // should print 1 (true) : 3 is in S
    Ss += "a";                         // should be a no-op
    cout << Ss["c"] << endl;           // should print 0 (false) : 5 not in S

    (Ss += "c") += "d";
    print(Ss);                       // should print 3 5 7

    oset <std::string> Ts("a");                      // singleton

    print(Ts);                       // should print 3

    oset <std::string> Us(Ss);                      // copy of S
    oset <std::string> Vs(Ss);                      // copy of S

    oset <std::string> Ws;  Ws = Ss;  print(Ws);      // 3 5 7

    Ss -= "b";                         // should be a no-op
    Ss -= "a";
    Us -= "c";
    Vs -= "d";
    print(Ss);                       // 5 7
    print(Us);                       // 3 7
    print(Vs);                       // 3 5

    oset <std::string> As;  ((As += "c") += "a") += "b";  print(As);       // 3 4 5
    oset <std::string> Bs;  ((Bs += "e") += "c") += "d";  print(Bs);       // 5 6 7

    oset <std::string> AuBs(As); AuBs += Bs; print(AuBs);            // 3 4 5 6 7
    oset <std::string> AmBs(As); AmBs -= Bs; print(AmBs);            // 3 4
    oset <std::string> AiBs(As); AiBs *= Bs; print(AiBs);            // 5
*/

}
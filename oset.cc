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
int main() {
    // Some simple testing code.  You'll need a lot more.

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



/*
    oset <int> Sd;     // empty set
    Sd += 3.1;     // now should contain 3

    cout << Sd[3.1] << " ";            // should print 1 (true) : 3 is in S
    Sd += 3.1;                         // should be a no-op
    cout << Sd[5.1] << endl;           // should print 0 (false) : 5 not in S

    (Sd += 5.1) += 7.1;
    print(Sd);                       // should print 3 5 7

    oset <int> Td(3.1);                      // singleton

    print(Td);                       // should print 3

    oset <int> Ud(Sd);                      // copy of S
    oset <int> Vd(Sd);                      // copy of S

    oset <int> Wd;  Wd = Sd;  print(W);      // 3 5 7

    Sd -= 4.1;                         // should be a no-op
    Sd -= 3.1;
    Ud -= 5.1;
    Vd -= 7.1;
    print(Sd);                       // 5 7
    print(Ud);                       // 3 7
    print(Vd);                       // 3 5

    oset <int> Ad;  ((Ad += 5.1) += 3.1) += 4.1;  print(Ad);       // 3 4 5
    oset <int> Bd;  ((Bd += 6.1) += 5.1) += 7.1;  print(Bd);       // 5 6 7

    oset <int>  AuBd(Ad);  AuBd += Bd;  print(AuBd);            // 3 4 5 6 7
    oset <int> AmBd(Ad);  AmBd -= Bd;  print(AmBd);            // 3 4
    oset <int> AiBd(Ad);  AiBd *= Bd;  print(AiBd);            // 5
*/
}

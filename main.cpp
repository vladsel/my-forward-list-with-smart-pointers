#include "list.hpp"

using namespace std;

int main() {
    try {
        forward_list <int> b{ 10, 11 };
        int aa = 15, bb = 16, cc = 17, dd = 18;
        b.push_front(aa);
        b.push_front(bb);
        b.push_front(move(cc));
        b.push_front(move(dd));

        cout << "\n\nlist b: " << endl;
        b.print_list();

        forward_list <int> a{ 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150 };
        cout << "\n\nlist a: " << endl;
        a.print_list();

        cout << "\n\nlist a, after a = b: " << endl;
        a = move(b);
        a.print_list();

        cout << "\n\na(size): " << a.size() << endl;

        cout << "\n\na(index(4)): " << a[4] << endl;

        cout << "\n\nafter erase by index(2): ";
        a.erase(2);
        a.print_list();

        cout << "\n\na(size): " << a.size() << endl;

        cout << "\n\n\n";
    }
    catch (exception &ex) {
        cerr << ex.what() << endl;
        return -1;
    }
    catch(...) {
        cerr << "\nunknown error\n" << endl;
        return -1;
    }

    return 0;
}
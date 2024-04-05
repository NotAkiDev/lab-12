#include <iostream>
#include <vector>

using namespace std;

template <typename Iterator, typename Functor>
class TransformIterator {
private:
    Iterator iter;
    Functor func_obj;
public:
    TransformIterator(Iterator it, Functor func) : iter(it), func_obj(func) {}

    auto operator*() const {
        return func_obj(*iter); // При разыменовании итератора запускать функтор
    }

    // Так как итератор кастомный, перегрузим операторы для вывода:

    TransformIterator& operator++() { // Перегрузка инкремента
        ++iter;
        return *this;
    }

    bool operator!=(const TransformIterator& other) const { // Перегрузка неравенства
        return iter != other.iter;
    }
};

int TransformFunction(int x) {
    return x * x;
}

int main() {
    vector<int> vec = {3, 3, 2, 5, 4};
    
    TransformIterator<vector<int>::iterator, decltype(TransformFunction)*> begin(vec.begin(), TransformFunction);
    TransformIterator<vector<int>::iterator, decltype(TransformFunction)*> end(vec.end(), TransformFunction);
    
    for (auto it = begin; it != end; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}

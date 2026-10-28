/*
 * SafeArray：带越界检查的安全数组
 * （二）通过 operator[] 支持下标访问
 * （三）用模板实现类型无关的安全数组
 */
#include <iostream>
#include <stdexcept>

template <typename T>
class SafeArray {
public:
    explicit SafeArray(int size) : data(NULL), size_(0) {
        if (size <= 0) {
            throw std::invalid_argument("数组大小必须为正数");
        }
        data = new T[size]();
        size_ = size;
    }

    ~SafeArray() {
        delete[] data;
    }

    SafeArray(const SafeArray &) = delete;
    SafeArray &operator=(const SafeArray &) = delete;

    T &operator[](int index) {
        checkIndex(index);
        return data[index];
    }

    const T &operator[](int index) const {
        checkIndex(index);
        return data[index];
    }

    int size() const {
        return size_;
    }

private:
    void checkIndex(int index) const {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("数组下标越界");
        }
    }

    T *data;
    int size_;
};

int main() {
    SafeArray<int> numbers(5);
    for (int i = 0; i < numbers.size(); i++) {
        numbers[i] = (i + 1) * 10;
    }

    std::cout << "int 数组：";
    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;

    SafeArray<double> scores(3);
    scores[0] = 90.5;
    scores[1] = 82.0;
    scores[2] = 77.5;

    std::cout << "double 数组：";
    for (int i = 0; i < scores.size(); i++) {
        std::cout << scores[i] << " ";
    }
    std::cout << std::endl;

    try {
        std::cout << numbers[5] << std::endl;
    } catch (const std::out_of_range &error) {
        std::cout << "numbers[5]：" << error.what() << std::endl;
    }

    try {
        scores[-1] = 0;
    } catch (const std::out_of_range &error) {
        std::cout << "scores[-1]：" << error.what() << std::endl;
    }

    return 0;
}

#include <iostream>
#include <stdexcept>
#include <string.h>

template <class T>
class TVectorBase{
    T* arr;
    int len;
    public:
    int& getLength(){
        return this->len;
    }
    const int getLength() const {//some method take arguments as const's, and can't apply non-const method to them
        return this->len;
    }
    T& operator[](int index){
        if(index>=((*this).getLength())){
            throw std::out_of_range("");
        }
        return this->arr[index];
    }
    const T& operator[](int index) const {//some method take arguments as const's, and can't apply non-const method to them
        if(index>=((*this).getLength())){
            throw std::out_of_range("");
        }
        return this->arr[index];
    }
    TVectorBase(int l=1){
        (*this).getLength() = l;
        this->arr = new T[this->len];
    }
    TVectorBase(const TVectorBase<T>& vectorToCopy){
        (*this).getLength() = vectorToCopy.len;
        this->arr = new T[(*this).getLength()];
        for(int i=0;i<(*this).getLength();i++){
            (*this)[i] = vectorToCopy[i];
        }
    }
    ~TVectorBase(){
        delete[] this->arr;
    }
    void setLength(int newLen){
        T* newArr = new T[newLen];
        for(int i=0;(i<newLen)&&(i<(*this).getLength());i++){
            newArr[i] = (*this)[i];
        }
        (*this).getLength() = newLen;
        T* tempPtr=this->arr;
        this->arr = newArr;
        delete[] tempPtr;
    }
    TVectorBase<T> operator=(const TVectorBase<T>& vectorB){
        if(&vectorB!=this){
            if((*this).getLength()!=vectorB.getLength()){
                (*this).getLength()=vectorB.getLength();
                delete[] this->arr;
                this->arr = new T[(*this).getLength()];
            }
            for(int i=0;i<(*this).getLength();i++){
                (*this)[i] = vectorB[i];
            }
        }
        return *this;
    }
    TVectorBase<T> operator+=(const TVectorBase<T>& vectorB){
        if((*this).getLength()!=(vectorB.getLength())){
            throw std::out_of_range("");
        }
        for(int i=0;i<(*this).getLength();i++){
            (*this)[i] += vectorB[i];
        }
        return *this;
    }
};

template <class T>
class TVector:public TVectorBase<T>{
    public:
    TVector(int l=1):TVectorBase<T>(l){};
    TVector(const TVectorBase<T>& vectorToCopy):TVectorBase<T>(vectorToCopy){};
    ~TVector(){};
    friend std::ostream& operator<<(std::ostream& os, TVectorBase<T> vector) {
        throw std::bad_cast();
    }
    friend std::istream& operator>>(std::istream& is, TVectorBase<T>& vector) {
        throw std::bad_cast();
    }
};

template<>
class TVector<int>:public TVectorBase<int>{
    public:
    TVector(int l=1):TVectorBase<int>(l){};
    TVector(const TVectorBase<int>& vectorToCopy):TVectorBase<int>(vectorToCopy){};
    ~TVector(){};
    friend std::ostream& operator<<(std::ostream& os, TVectorBase<int> vector) {
        for(int i=0;i<vector.getLength();i++){
            os << vector[i] << " ";
        }
        return os;
    }
    friend std::istream& operator>>(std::istream& is, TVectorBase<int>& vector) {
        int length;
        is >> length;
        vector.setLength(length);
        for (int i = 0; i < length; ++i) {
            is >> vector[i];
        }
        return is;
    }
};
template<>
class TVector<char>:public TVectorBase<char>{
    public:
    TVector(int l=1):TVectorBase<char>(l){};
    TVector(const TVectorBase<char>& vectorToCopy):TVectorBase<char>(vectorToCopy){};
    ~TVector(){};
    friend std::ostream& operator<<(std::ostream& os, TVectorBase<char> vector) {
        for(int i=0;i<vector.getLength();i++){
            os << vector[i] << " ";
        }
        return os;
    }
    friend std::istream& operator>>(std::istream& is, TVectorBase<char>& vector) {
        int length;
        is >> length;
        vector.setLength(length);
        for (int i = 0; i < length; ++i) {
            is >> vector[i];
        }
        return is;
    }
};


int main(){
    int a = 10, b = 15;
    TVector<char> charVector(a);
    TVector<int> intVectorA(a),intVectorB(b);
    for(int i=0;i<a;i++){
        charVector[i] = 'A'+i;
        intVectorA[i] = 2*i;
    }
    for(int i=0;i<b;i++){
        intVectorB[i] = 2*i+1;
    }
    std::cout << "charVector = " << charVector << "\tlen = " << charVector.getLength();
    std::cout << "\nintVectorA = " << intVectorA << "\tlen = " << intVectorA.getLength();
    std::cout << "\nintVectorB = " << intVectorB << "\tlen = " << intVectorB.getLength() << "\n\n\n";
    intVectorA[0] = 314;
    intVectorB[0] = 271;
    std::cout << "\nintVectorA = " << intVectorA << "\tlen = " << intVectorA.getLength();
    std::cout << "\nintVectorB = " << intVectorB << "\tlen = " << intVectorB.getLength() << "\n\n\n";
    intVectorA.setLength(20);
    intVectorB.setLength(5);
    std::cout << "\nintVectorA = " << intVectorA << "\tlen = " << intVectorA.getLength();
    std::cout << "\nintVectorB = " << intVectorB << "\tlen = " << intVectorB.getLength() << "\n\n\n";
    //std::cout << intVectorB[10]=5; out_of_range
    intVectorA = intVectorB;
    std::cout << "\nintVectorA = " << intVectorA << "\tlen = " << intVectorA.getLength();
    std::cout << "\nintVectorB = " << intVectorB << "\tlen = " << intVectorA.getLength() << "\n\n\n";
    intVectorA[0] = 161;
    std::cout << "\nintVectorA = " << intVectorA << "\tlen = " << intVectorA.getLength();
    std::cout << "\nintVectorB = " << intVectorB << "\tlen = " << intVectorA.getLength() << "\n\n\n";
    intVectorA+=intVectorB;
    std::cout << "\n intVectorA = " << intVectorA << "\tlen = " << intVectorA.getLength();
    std::cout << "\n intVectorB = " << intVectorB << "\tlen = " << intVectorA.getLength() << "\n\n\n";

    TVector<std::string> vectorToRead;
    //std::cin >> vectorToRead;
    //std::cout << "\n vectorToRead = " << vectorToRead;
    return 0;
}
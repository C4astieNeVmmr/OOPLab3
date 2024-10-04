#include <iostream>
#include <string.h>

template <class T>
class TVector{
    T* arr;
    int len;
    public:
    T& operator[](int index){
        if(index>=(this->len)){
            throw std::out_of_range("");
        }
        return this->arr[index];
    }
    const T& operator[](int index) const {
        if(index>=(this->len)){
            throw std::out_of_range("");
        }
        return this->arr[index];
    }
    int getLength(){
        return this->len;
    }
    TVector(int l=1){
        this->len = l;
        this->arr = new T[this->len];
    }
    TVector(const TVector<T>& vectorToCopy){
        this->len = vectorToCopy.len;
        this->arr = new T[this->len];
        for(int i=0;i<this->len;i++){
            (*this)[i] = vectorToCopy[i];
        }
    }
    ~TVector(){
        delete[] this->arr;
    }
    void setLength(int newLen){
        T* newArr = new T[newLen];
        for(int i=0;(i<newLen)&&(i<this->len);i++){
            newArr[i] = (*this)[i];
        }
        this->len = newLen;
        T* tempPtr=this->arr;
        this->arr = newArr;
        delete[] tempPtr;
    }
    TVector<T> operator=(const TVector<T>& vectorB){
        if(&vectorB!=this){
            if(this->len!=vectorB.len){
                this->len=vectorB.len;
                delete[] this->arr;
                this->arr = new T[this->len];
            }
            for(int i=0;i<this->len;i++){
                (*this)[i] = vectorB[i];
            }
        }
        return *this;
    }
    TVector<T> operator+=(const TVector<T>& vectorB){
        if((this->len)!=(vectorB.len)){
            throw std::out_of_range("");
        }
        for(int i=0;i<this->len;i++){
            (*this)[i] += vectorB[i];
        }
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, TVector<T> vector) {
        for(int i=0;i<vector.len;i++){
            os << vector[i] << " ";
        }
        return os;
    }
    friend std::istream& operator>>(std::istream& is, TVector<T>& vector) {
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
    std::cin >> vectorToRead;
    std::cout << "\n vectorToRead = " << vectorToRead;
    return 0;
}
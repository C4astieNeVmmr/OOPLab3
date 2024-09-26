#include <iostream>

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
    TVector(int l=1){
        this->len = l;
        this->arr = new T[this->len];
    }
    TVector(const TVector<T>& vectorToCopy){
        this->len = vectorToCopy.len;
        this->arr = new T[this->len];
        for(int i=0;i<this->len;i++){
            this->arr[i] = vectorToCopy.arr[i];//TODO how to change this
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
    TVector<T> operator=(TVector<T> vectorB){
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
    }/*
    TVector<T> operator+(TVector<T> vectorB){
        
    }
    TVector<T> operator+=(TVector<T> vectorB){
        if(this->len!=vectorB.len){
            throw out_of_range("");
        }
        for(int i=0;i<this->len;i++){
            this->arr[i] += vectorB.arr[i];
        }
    }*/
    friend std::ostream& operator<<(std::ostream& os,TVector<T> vec){
        for(int i=0;i<vec.len;i++){
            os << vec[i] << " ";
        }
        return os;
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
    std::cout << "charVector = " << charVector;
    std::cout << "\n\n intVectorA = " << intVectorA;
    std::cout << "\n\n intVectorB = " << intVectorB << "\n\n\n";
    intVectorA[0] = 314;
    intVectorB[0] = 271;
    std::cout << "\n\n intVectorA = " << intVectorA;
    std::cout << "\n\n intVectorB = " << intVectorB << "\n\n\n";
    intVectorA.setLength(20);
    intVectorB.setLength(5);
    std::cout << "\n\n intVectorA = " << intVectorA;
    std::cout << "\n\n intVectorB = " << intVectorB << "\n\n\n";
    //std::cout << intVectorB[10]=5; out_of_range
    intVectorA = intVectorB;
    std::cout << "\n\n intVectorA = " << intVectorA;
    std::cout << "\n\n intVectorB = " << intVectorB << "\n\n\n";
    intVectorA[0] = 161;
    std::cout << "\n\n intVectorA = " << intVectorA;
    std::cout << "\n\n intVectorB = " << intVectorB << "\n\n\n";
    
    return 0;
}
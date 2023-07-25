#include <iostream>
#include <string>
#include <memory>
/*
class Dado{
private:
    std::string name;
    int valor;
public:
    Dado(std::string T="DadoDefault", int n=1):name(T), valor(n){}

    Dado& operator +(const Dado& D2)
    {
        valor=valor+D2.valor;
        return *this;
    }
    friend std::ostream& operator << (std::ostream& output, const Dado &D1)
    {
        output<<D1.name<<"-"<<D1.valor;
        return output;
    }

};
int main(){
    Dado D1("Dado1",3);
    Dado D2("Dado2",2);
    Dado D3;
    D3=D1+D2;

    std::cout<<D3;
    
    return 0;
}

class Persona
{
private:
    std::string name;
    int edad;
public:
    Persona(std::string n="Nombre", int e=0):name(n),edad(e){}

    Persona operator+(Persona& P1){
        edad=edad+P1.edad;
        return *this;
    }
    friend std::ostream& operator <<(std::ostream &output,const Persona& P1)
    {
        output<<P1.name<<" tiene "<<P1.edad;
        return output;
    }

};
int main (){
    Persona P1("el",9);
    Persona P2("Ana",8);
    std::cout<<P1+P2;
    return 0;
}

class Num
{
private:
    int valor;
public:
    Num(int n=0):valor(n){}
    Num operator+(const Num& N){
        valor=valor+N.valor;
        return *this;
    }
    Num operator=(const Num& N){
        valor=N.valor;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& output, const Num& N)
    {
        output<<N.valor;
        return output;
    }
};
int main(){
    Num A(14);
    Num B(12);
    std::cout<<A+B;
    A=B;
    std::cout<<A;
    return 0;
}
*/
/*
int main(){
    std::unique_ptr<int> ptr= std::make_unique<int>(42);
    std::cout<<*ptr;
    std::unique_ptr<int> ptr2= std::move(ptr);
    std::cout<<*ptr2;
    std::cout<<*ptr; 
}
*/
/*
std::string get_string()
{
 return std::string("I am a string.");
}
struct my_type
{
    my_type() = default;
    my_type(const my_type &) {std::cout <<"Copying\n";}
    my_type(my_type &&) {std::cout <<"Moving\n";}
};
my_type func()
{
    return my_type();
}
*/
/*
int main(){
    int x[3][3][3]={{{1,2,3},{4,5,6},{7,8,9}},
                    {{10,11,12},{14,15,16},{17,18,19}},
                    {{21,22,23},{24,25,26},{27,28,29}}};
    std::cout<< *(*(*(x+0)+2)+1);
    std::cout<< *(*(*(x+1)+1)+0);
    std::cout<< *(*(*(x+2)+0)+1);
    return 0;
}
*/

class CE{
public:
    CE ()
    { 
        std::cout <<"constructor";
    }
    CE (const CE&)
    {
        std::cout<<"COPIA";
    }
    ~CE ()
    { 
        std::cout <<"Destructor";
    }
};
CE funcion()
{
    return CE();
}
int  main(){
    CE ce;
    return 0;
}
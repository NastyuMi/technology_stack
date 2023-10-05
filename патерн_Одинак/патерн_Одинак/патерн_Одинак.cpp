#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class Singleton
{
private:
    /*тут создается достаточное к-тво переменных 
    а так же создаем не один , а указиваем максимальное к-ство одинакив 
    если буднт создаваться больше чем указано в статической переменной int Singleton::users */
    static int count; 
    static int users; 
    static vector<Singleton*> _instance; 
    vector<string> storage;
    int d = 0;


protected:

    /*тут мы добавляем сервера, т.к. может быть расширение этого списка*/
    Singleton() 
    {
        storage.clear();
        storage.push_back("local disk");
        storage.push_back("Amazon S3");
    }

public:
   
    static Singleton* Instance()
    {
        if (count < users)
        {
            _instance.push_back(new Singleton());
            count++;
            return _instance[count - 1];
        }
        else
        {
            return nullptr;
        }
    }

    void Set()
    {   
        /*делаем так, чтобы подключение к какому именно серверу происхлодило случайным образом*/
        d = (0 + std::rand() % (100 - 0 + 1)) % storage.size();

    }

    int Get()
    {
        return d ;
    }

    void Print()
    {
        cout << storage[d] << endl;
    }

    ~Singleton()
    {
       
    }
};

int Singleton::count = 0;
int Singleton::users = 4; //тут 1е место где задаем к-тво пользователей
int n = 4; // 2-е место где задаем к-тво пользователей
vector<Singleton*> Singleton::_instance;

int main()
{
    Singleton* objArray[4];  // и тут 3-е место где задаем к-тво пользователей


    /*создаем поочередно массив из одинакив*/
    for (int i = 0; i < n; i++)
    {
        objArray[i] = Singleton::Instance();

        if (objArray[i] != nullptr)
        {
            objArray[i]->Set();
            cout << "user #" << i + 1 << " = ";
            objArray[i]->Print();
        }
    }


    /*для проверки зоздаем еще один екземляр*/
    Singleton* obj5 = Singleton::Instance();

    if (obj5 != nullptr)
    {
        obj5->Set();
        obj5->Print();
    }
    else
        cout << "Error creating obj5." << endl;

    return 0;
}

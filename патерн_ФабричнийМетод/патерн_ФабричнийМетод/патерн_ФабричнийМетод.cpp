#include <iostream>
#include <string>

 using namespace std;

 /*данный класс у меня вышел обсолютно абстрактным, в нем мы могли бы гипотетически прописать
 доступ непосредственно для взаимодействия с соц сетями*/

class LogIN {
public:
    virtual ~LogIN() {}
    virtual string Operation() const = 0 ;
};

/* происходные классы от LogIN  имеют оператор для авторизации в определенной сети*/
class LogIN_Facebook : public LogIN {
public:
    string Operation() const override {
        string log = "";
        string pass = "";
    metka1:
        cout << "login:";
        cin >> log;
        if (log.empty() == true)
            goto metka1;
    metka2:
        cout << "password:";
        cin >> pass;
        if (pass.empty() == true)
            goto metka2;

        return "Welcome to Facebook";
    }
};

class LogIN_LinkedIN : public LogIN {
public:
    string Operation() const override {
        string log = "";
        string pass = "";
    metka1:
        cout << "login:";
        cin >> log;
        if (log.empty() == true)
            goto metka1;
    metka2:
        cout << "password:";
        cin >> pass;
        if (pass.empty() == true)
            goto metka2;

        return "Welcome to LinkedIN";
    }
};

/*а отличии от предыдущих методов тут мы создаем сам пост в виде текста*/
class CreatePOST {
    
public:
    virtual ~CreatePOST() {};
    virtual LogIN* FactoryMethod() const = 0;

    string SomeOperation() const {
        // Вызываем фабричный метод, чтобы получить объект.
        LogIN* LogIN = this->FactoryMethod();
        // Далее, работаем с этим обьектом.
        string result = LogIN->Operation();
        string post;
        cout << result << endl;
    st:
        cout << "Write a post:";
        getline(cin, post);
        if (post.empty() == true)
            goto st;
        result = "Your post on " + result.substr(result.find_last_of(' ') + 1) + ": " + post;
        delete LogIN;
        return result;
    }
};


class PostForFacebook : public CreatePOST {
    
public:
    LogIN* FactoryMethod() const override {
        return new LogIN_Facebook();
    }
};

class PostForLinkedIN : public CreatePOST {

public:
    LogIN* FactoryMethod() const override {
        return new LogIN_LinkedIN();
    }
};

/*
  Клиентский код работает с экземпляром конкретного создателя.
 */
void ClientCode(const CreatePOST& CreatePOST) {

    cout << CreatePOST.SomeOperation() << endl;
}

/* в главном классе проверяем работу с разными средами */

int main() {
    cout << "User1.\n";
    CreatePOST* creator = new PostForFacebook();
    ClientCode(*creator);
    cout << endl;
    cout << "User2.\n";
    CreatePOST* creator1 = new PostForLinkedIN();
    ClientCode(*creator1);

    delete creator;
    delete creator1;
    return 0;
}

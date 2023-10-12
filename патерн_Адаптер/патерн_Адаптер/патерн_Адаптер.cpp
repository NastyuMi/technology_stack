#include <iostream>
#include <string>

using namespace std;

// інтерфейс, який ми не можемо змінювати за завданням, перевела на с++
class Notification
{
public:
    virtual void send(string title, string message) = 0;
};

// клас, який ми не можемо змінювати за завданням , перевела к код с++
class EmailNotification : public Notification
{
private:
    string adminEmail;

public:
    EmailNotification(string adminEmail)  {
        adminEmail = adminEmail;
    }

    void send(string title, string message) override {
        cout << "Sent email with title '" << title << "' to '" << adminEmail << "' that says '" << message << "'.\n";
    }
};

// Адаптер для Slack
class Adapter_for_SlackNotification : public Notification
{
private:
    string login;
    string api_key;
    string ID_chat;

public:
    Adapter_for_SlackNotification(string login, string api_key, string ID_chat) {
        login = login;
        api_key = api_key;
        ID_chat = ID_chat;
    }

    /**
    * тут ще можли перейти перевірку на правильній тип даних, чи не пусті поля
    * але допустимо, що все введено вірно
    * а для зручності все будемо приймать в текстовому форматі
    */

    void send(string title, string message) override
    {
        cout << "Sent Slack message with title '" << title << "' to chat '" << ID_chat << "' that says '" << message << "'.\n";
    }
};

// Адаптер для  SMS
class Adapter_for_SMSNotification : public Notification
{
private:
    string phone;
    string sender;

public:
    Adapter_for_SMSNotification(string phone, string sender) {
        phone = phone;
        sender = sender;
    }

    /**
    * тут ще можли перейти перевірку на правильній тип даних, чи не пусті поля
    * але допустимо, що все введено вірно
    * а для зручності все будемо приймать в текстовому форматі
    */

    void send(string title, string message) override
    {
        cout << "Sent SMS with title '" << title << "' from '" << sender << "' to phone '" << phone << "' that says '" << message << "'.\n";
    }
};


//створюємо екземпляри для перевірки роботи адаптерів
int main()
{
    Notification* emailNotification = new EmailNotification("ikm223a@gmail.com");
    Notification* slackNotification = new Adapter_for_SlackNotification("login", "api_key", "id_chat");
    Notification* smsNotification = new Adapter_for_SMSNotification("0958832666", "Natalii");

    emailNotification->send("Email Test", "This is an email message");
    slackNotification->send("Slack Test", "This is a Slack message");
    smsNotification->send("SMS Test", "This is an SMS message");

    delete emailNotification;
    delete slackNotification;
    delete smsNotification;

    return 0;
}

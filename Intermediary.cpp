#include <iostream>
#include <string>

using namespace std;

class Mediator;

class Colleague {
public:
    virtual void setMediator(Mediator* mediator) {
        this->mediator = mediator;
    }

    virtual void send(string message) const = 0;
    virtual void receive(string message) const = 0;

protected:
    Mediator* mediator;
};

class Mediator {
public:
    virtual void send(string message, const Colleague* colleague) const = 0;
};

class ProfileDialogMediator : public Mediator {
public:
    void send(string message, const Colleague* colleague) const override {
        colleague->receive(message);
    }
};

class TextBox : public Colleague {
public:
    void setText(const string& text) {
        this->text = text;
        send("Text set: " + text);
    }

    void send(string message) const override {
        mediator->send(message, this);
    }

    void receive(string message) const override {
        cout << "TextBox received: " << message << endl;
    }

private:
    string text;
};

class Checkbox : public Colleague {
public:
    void check() {
        isChecked = true;
        send("Checkbox checked");
    }

    void uncheck() {
        isChecked = false;
        send("Checkbox unchecked");
    }

    void send(string message) const override {
        mediator->send(message, this);
    }

    void receive(string message) const override {
        cout << "Checkbox received: " << message << endl;
    }

private:
    bool isChecked = false;
};

class Button : public Colleague {
public:
    void click() {
        send("Button clicked");
    }

    void send(string message) const override {
        mediator->send(message, this);
    }

    void receive(string message) const override {
        cout << "Button received: " << message << endl;
    }
};

int main() {
    ProfileDialogMediator mediator;

    TextBox textBox;
    Checkbox checkbox;
    Button button;

    textBox.setMediator(&mediator);
    checkbox.setMediator(&mediator);
    button.setMediator(&mediator);

    textBox.setText("John Doe");
    checkbox.check();
    button.click();

    return 0;
}
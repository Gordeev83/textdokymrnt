#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Document {
public:
    virtual void create() = 0;
    virtual void open(const string& filename) = 0;
    virtual void save() = 0;
    virtual void saveAs(const string& filename) = 0;
    virtual void print() = 0;
    virtual void close() = 0;
};

class TextDocument : public Document {
private:
    string content;
    string filename;
    bool isOpen;

public:
    void create() override {
        if (isOpen) {
            cout << "Документ уже открыт" << endl;
            return;
        }
        isOpen = true;
        content = "";
        filename = "";
        cout << "Создан новый текстовый документ" << endl;
    }

    void open(const string& filename) override {
        if (isOpen) {
            cout << "Документ уже открыт" << endl;
            return;
        }
        isOpen = true;
        this->filename = filename;
        cout << "Открыт текстовый документ: " << filename << endl;
    }

    void save() override {
        if (!isOpen) {
            cout << "Документ не открыт, пожалуйста, откройте или создайте новый документ" << endl;
            return;
        }
        if (filename.empty()) {
            cout << "Пожалуйста, укажите имя файла для сохранения документа" << endl;
            return;
        }
        ofstream file(filename);
        file << content;
        file.close();
        cout << "Сохраненный текстовый документ" << endl;
    }

    void saveAs(const string& filename) override {
        if (!isOpen) {
            cout << "Документ не открыт, пожалуйста, откройте или создайте новый документ" << endl;
            return;
        }
        this->filename = filename;
        save();
    }

    void print() override {
        cout << "Содержание: " << content << endl;
    }

    void close() override {
        isOpen = false;
        content = "";
        filename = "";
        cout << "Текстовый документ закрыт" << endl;
    }
};


int main()
{
    setlocale(LC_ALL, "");
    Document* textDoc = new TextDocument();
    textDoc->create();
    textDoc->open("text_document.txt");
    textDoc->saveAs("new_text_document.txt");
    textDoc->print();
    textDoc->close();

    cout << endl;


    delete textDoc;

    return 0;
}
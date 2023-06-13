#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> // Untuk transformasi huruf
#include <sstream> // Untuk stringstream
#include <cstdlib> //untuk system cls atau pause.
using namespace std;

class TextEditor {
protected:
    string filename;

public:
  TextEditor(const string& filename) : filename(filename) {}
    virtual void execute() = 0;
};

class createFile : public TextEditor { //Class Turunan Pertama
public :
    createFile(const string& filename) : TextEditor(filename) {}

    void execute() override {
        ofstream file(filename);
        if (file) {
            cout << "File telah dibuat: " << filename << endl;
            file.close();
        } else {
            cerr << "Gagal membuat file." << endl;
        }
    }
};

class openFile: public TextEditor { //Class Turunan Kedua
public:
    openFile(const string& filename) : TextEditor(filename) {}
 
    void execute() override {
        ifstream file(filename);
        if (file) {
            string line;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        } else {
            cerr << "Gagal membuka file." << endl;
        }
    }
};

class editFile : public TextEditor { //Class Turunan Ketiga
public:
    editFile(const string& filename) : TextEditor(filename) {}

    void execute() override {
    string content = readFile(filename);
    cout << "Isi file semula:\n" << content << endl;

    int choice;
    cout << "\n\033[38;5;214m Menu Edit \033[0m" << endl;
    cout << "1. Menambahkan isi file" << endl;
    cout << "2. Mengedit isi file" << endl;
    cout << "Pilihan anda: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            cout << "Tambahkan isi file (ketik 'finish' setelah siap menambah):\n";
            string line;
            cin.ignore();
            while (getline(cin, line)) {
                if (line == "finish") {
                    break;
                }
                
                content += "" + line + "\n";
            }
            break;
        }
        case 2:{
            int lineNumber;
            cout << "Input nomor baris yang ingin diedit: ";
            cin >> lineNumber;
            cin.ignore(); // Menghapus karakter \n yang tersisa setelah memasukkan nomor baris

            if (lineNumber <= 0 || lineNumber > countLines(content)) {
                cerr << "Nomor baris tidak tersedia." << endl;
                return;
            }

            cout << "Masukkan kalimat baru: ";
            string newText;
            getline(cin, newText);
            content = editLine(content, lineNumber, newText);
            break;
        }
        default:
            cerr << "Pilihan anda tidak valid. Gagal melakukan edit." << endl;
            return;
    }

    saveFile(filename, content); // Simpan perubahan ke dalam file
}

protected:
 string readFile(const string& filename) {
        ifstream file(filename);
        if (file) {
            stringstream buffer;
            buffer << file.rdbuf();
            file.close();
            return buffer.str();
        } else {
            cerr << "Gagal membuka file." << endl;
            return "";
        }
    }

     string editLine(const string& text, int lineNumber, const string& newText) {
    stringstream ss(text);
    string modifiedText;
    string line;
    int currentLine = 0;
    while (getline(ss, line)) {
        currentLine++;
        if (currentLine == lineNumber) {
            modifiedText += newText + "\n";
        } else {
            modifiedText += line + "\n";
        }
    }
    return modifiedText;
}

    int countLines(const string& text) {
    stringstream ss(text);
    int count = 0;
    string line;
    while (getline(ss, line)) {
        count++;
    }
    return count;
}

    void saveFile(const string& filename, const string& content) {
        ofstream file(filename);
        if (file) {
            file << content;
            cout << "File tersimpan: " << filename << endl;
            file.close();
        } else {
            cerr << "Gagal menyimpan file." << endl;
        }
    }
};

class formatText : public TextEditor { //Class Turunan Keempat
public:
    formatText(const string& filename) : TextEditor(filename) {}
    void execute() override {

                ifstream file(filename);
                if (file) {
                    string text;
                    string line;
                    while (getline(file, line)) {
                        text += line + "\n";
                    }
                    file.close();

  string formattedText = text; 
    int choice;

    cout << "\n\033[38;5;214m Menu Format \033[0m" << endl;
    
    cout << "1. Uppercase" << endl;
    cout << "2. Lowercase" << endl;
    cout << "3. Capitalize" << endl;
    cout << "4. Enter" << endl;
    cout << "Pilihan anda: ";
    cin >> choice;
 
    switch (choice) {
        case 1:
            transform(formattedText.begin(), formattedText.end(), formattedText.begin(), ::toupper);
            break;
        case 2:
            transform(formattedText.begin(), formattedText.end(), formattedText.begin(), ::tolower);
            break;
        case 3:
            transform(formattedText.begin(), formattedText.end(), formattedText.begin(), ::tolower);
            formattedText[0] = toupper(formattedText[0]);
            for (size_t i = 1; i < formattedText.length(); i++) {
                if (formattedText[i - 1] == ' ')
                    formattedText[i] = toupper(formattedText[i]);
            }
            break;
        case 4:
            formattedText = addParagraphs(formattedText);
            break;
       
        default:
            cerr << "Pilihan anda tidak valid. Gagal melakukan format." << endl;
    }

 saveFile(formattedText);
        } else {
            cerr << "Gagal membuka file." << endl;
}
    }
 private:

        void saveFile(const string& formattedText) {
        ofstream file(filename);
        if (file) {
            file << formattedText;
            cout << "File tersimpan: " << filename << endl;
            cout << "Hasil Format Text :\n" << formattedText << endl;
            file.close();
        } else {
            cerr << "Gagal menyimpan file." << endl;
        }
    }

 string addParagraphs(const string& text) {
        string formattedText;
        string line;
        stringstream ss(text);
        while (getline(ss, line)) {
            if (!line.empty()) {
                formattedText += line + "\n\n"; // Tambahkan dua baris kosong antara setiap paragraf
            }
        }
        return formattedText;
    }
};

class analyzeFile: public TextEditor { //Class Turunan Kelima
public:
    analyzeFile(const string& filename) : TextEditor(filename) {}
    void execute() override {
        ifstream file(filename);
        if (file) {
            string text;
            string line;
            while (getline(file, line)) {
                text += line + "\n";
            }
            file.close();

            int choice;
            cout << "\n\033[38;5;214m Menu Analisis \033[0m" << endl;
            cout << "1. Cari sebuah kata" << endl;
            cout << "2. Menghitung jumlah kata dalam file" << endl;
            cout << "3. Menghitung jumlah kalimat dalam file" << endl;
            cout << "Pilihan anda: ";
            cin >> choice;

            switch (choice) {
                case 1:{
                    string searchWord;
                    cout << "Berikan kata yang ingin dicari: ";
                    cin >> searchWord;
                    if (searchWord.length() > 0) {
                        int count = searchWordOccurrences(text, searchWord);
                        cout << "Kata \"" << searchWord << "\" muncul " << count << " kali." << endl;
                    } else {
                        cerr << "Kata yang dicari tidak valid." << endl;
                    }
                    break;
                }
                case 2:{
                    int wordCount = countWords(text);
                    cout << "Jumlah kata dalam file: " << wordCount << endl;
                    break;
                }
                case 3:{
                    int sentenceCount = countSentences(text);
                    cout << "Jumlah kalimat dalam file: " << sentenceCount << endl;
                    break;
                }
                default:
                    cerr << "Pilihan anda tidak valid. Tolong coba lagi" << endl;
            }
        } else {
            cerr << "Gagal membuka file." << endl;
        }
    }

    private:
    int searchWordOccurrences(const string& text, const string& searchWord) {
        int count = 0;
        string word;
        stringstream ss(text);
        while (ss >> word) {
            if (word == searchWord) {
                count++;
            }
        }
        return count;
    }

    int countWords(const string& text) {
        int count = 0;
        string word;
        stringstream ss(text);
        while (ss >> word) {
            count++;
        }
        return count;
    }

    int countSentences(const string& text) {
    int count = 0;
    stringstream ss(text);
    string sentence;
    while (getline(ss, sentence)) {
        size_t pos = 0;
        while ((pos = sentence.find('.', pos)) != string::npos) {
            count++;
            pos++;
        }
    }
    return count;
}
};

class compileFile : public TextEditor { //Class Turunan Keenam
public:
    compileFile(const string& filename) : TextEditor(filename) {}

    void execute() override {
        string extension = getFileExtension(filename);
        transform(extension.begin(), extension.end(), extension.begin(), ::tolower); 

        if (extension == "c") {
            string command = "gcc " + filename + " -o " + getOutputFilename(filename);
            cout << "Run file: " << filename << endl;
            int result = system(command.c_str());
            if (result == 0) {
                cout << "Run sukses." << endl;
                cout << "Melakukan eksekusi file..." << endl;
                string output = executeFile(getOutputFilename(filename));
                cout << "--- Output ---" << endl;
                cout << output << endl;
            } else {
                cerr << "Run gagal." << endl;
            }
        } else if (extension == "cpp") {
            string command = "g++ " + filename + " -o " + getOutputFilename(filename);
            cout << "Run file: " << filename << endl;
            int result = system(command.c_str());
            if (result == 0) {
                cout << "Run sukses." << endl;
                cout << "Melakukan eksekusi file..." << endl;
                string output = executeFile(getOutputFilename(filename));
                cout << "--- Output ---" << endl;
                cout << output << endl;
            } else {
                cerr << "Run gagal." << endl;
            }
        } else {
            cerr << "Tipe file tidak tersedia. Hanya file c and .cpp yang dapat dirun." << endl;
        }
    }

private:
    string getFileExtension(const string& filename) {
        size_t dotPos = filename.find_last_of(".");
        if (dotPos != string::npos && dotPos < filename.length() - 1) {
            return filename.substr(dotPos + 1);
        }
        return "";
    }

    string getOutputFilename(const string& filename) {
        size_t dotPos = filename.find_last_of(".");
        if (dotPos != string::npos) {
            return filename.substr(0, dotPos);
        }
        return filename;
    }

    string executeFile(const string& filename) {
        string command = filename;
        string output;
        FILE* pipe = popen(command.c_str(), "r");
        if (pipe) {
            char buffer[128];
            while (!feof(pipe)) {
                if (fgets(buffer, 128, pipe) != nullptr) {
                    output += buffer;
                }
            }
            pclose(pipe);
        }
        return output;
    }
};

class copyFile : public TextEditor {
public:
    copyFile(const string& sourceFilename) : TextEditor(sourceFilename) {}

    void execute() override {
        string destinationFilename;
        cout << "Masukkan nama file tujuan: ";
        cin >> destinationFilename;

        ifstream sourceFile(filename);
        if (sourceFile) {
            ofstream destinationFile(destinationFilename);
            if (destinationFile) {
                destinationFile << sourceFile.rdbuf();
                cout << "File berhasil dicopy ke: " << destinationFilename << endl;
                destinationFile.close();
            } else {
                cerr << "Gagal membuat file tujuan." << endl;
            }
            sourceFile.close();
        } else {
            cerr << "Gagal membuka file sumber." << endl;
        }
    }
};

class clearFile : public TextEditor {
public:
    clearFile(const string& filename) : TextEditor(filename) {}

    void execute() override {
        ofstream file(filename);
        if (file) {
            cout << "Isi file telah dikosongkan: " << filename << endl;
            file.close();
        } else {
            cerr << "Gagal mengosongkan file." << endl;
        }
    }
};

class deleteFile : public TextEditor { //Class Turunan Ketuju
public:
    deleteFile (const string& filename) : TextEditor(filename) {}

    void execute() override {
    if (remove(filename.c_str()) == 0) {
        cout << "File dihapus: " << filename << endl;
    } else {
        cerr << "Gagal menghapus file." << endl;
    }
}
};

int main() {
      
    string filename;
    cout << "\033[1;95m === Text Editor Sederhana === \033[0m" << endl;

    int choice;
    do {
        system("cls");
        cout << "\033[1;95m === Text Editor Sederhana === \033[0m" << endl;
        cout << "\033[1;38;2;209;117;129m ----MENU UTAMA----\033[0m" << endl;
        cout << "1.  Membuat file baru" << endl;
        cout << "2.  Membuka file" << endl;
        cout << "3.  Mengedit file" << endl;
        cout << "4.  Format teks" << endl;
        cout << "5.  Analisis file" << endl;
        cout << "6.  Run file (C/C++) " << endl;
        cout << "7.  Mengcopy file " << endl;
        cout << "8.  Mengosongkan isi file " << endl;
        cout << "9.  Menghapus file " << endl;
        cout << "10. Exit" << endl;
        cout << "\033[1;38;2;209;117;129m Pilihan Anda: \033[0m" << endl;
        cin >> choice;

        cout << "Berikan nama file: ";
        cin >> filename;

    createFile createFileMenu(filename);
    openFile openFileMenu(filename);
    editFile editFileMenu(filename);
    formatText formatFileMenu(filename);
    analyzeFile analyzeFileMenu(filename);
    compileFile runFileMenu(filename);
    copyFile copyFileMenu(filename);
    clearFile clearFileMenu(filename);
    deleteFile deleteFileMenu(filename);

       
switch (choice) {
        case 1:
            createFileMenu.execute();
            system("pause");
            break;
        case 2:
            openFileMenu.execute();
            system("pause");
            break;
        case 3:
            editFileMenu.execute();
            system("pause");
            break;
        case 4:
            formatFileMenu.execute();
            system("pause");
            break;
        case 5:
            analyzeFileMenu.execute();
            system("pause");
            break;
        case 6:
            runFileMenu.execute();
            system("pause");
            break;
        case 7:
            copyFileMenu.execute();
            system("pause");
            break;
        case 8:
            clearFileMenu.execute();
            system("pause");
            break;
        case 9:
            deleteFileMenu.execute();
            system("pause");
            break;
         case 10:
                cout << "Keluar..." << endl;
                break;
        default:
            cerr << "Pilihan anda tidak valid. Program berakhir." << endl;
            system("pause");
            break;
    }
    }   while (choice != 10);
    return 0;
}

#ifndef DOCUMENT_H_INCLUDED
#define DOCUMENT_H_INCLUDED

#include <fstream>


class Document{
public:
    std::string openDocument(const std::string name){
        if(!canOpenDocument(name))
            throw std::string("file is not existed. ");
        openFile(name);
        return readFile();
    }
protected:
    virtual void openFile(const std::string name) = 0;
    virtual bool canOpenDocument(const std::string name) = 0;
    virtual std::string readFile() = 0;
};


class MyDocument : public Document{
public:
    void openFile(const std::string name){
        fs.open(name, std::ios::in);
    }
    bool canOpenDocument(const std::string name){
        fs.open(name,std::ios::in); //success : not 0, fail : 0
        if(!fs){
            //fs.close();
            return false;
        }
        else{
            fs.close();
            return true;
        }
    }
    std::string readFile(){
        std::string line;
        while(getline(fs, line)){
            content += line;
        }
        fs.close();
        return content;
    }
private:
    std::fstream fs;
    std::string content;
};
#endif // DOCUMENT_H_IMCLUDE

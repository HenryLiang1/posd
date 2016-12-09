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
        if(content.size() == 0){
            throw std::string("file data is empty");
        }

        fs.close();
        return content;
    }
private:
    std::fstream fs;
    std::string content;
};

class InstructionDocument{
public:
    std::vector<std::string> openDocument(const std::string name){
        if(!canOpenDocument(name))
            throw std::string("file is not existed. ");
        openFile(name);
        return readFile();
    }
    void writeDocument(const std::string name, std::vector<std::string> data){
        if(!canWriteDocument(name))
            throw std::string("file is not existed. ");
        openFileForWrite(name);
        writeFile(data);
    }
protected:
    virtual void openFile(const std::string name) = 0;
    virtual void openFileForWrite(const std::string name) = 0;
    virtual bool canOpenDocument(const std::string name) = 0;
    virtual bool canWriteDocument(const std::string name) = 0;
    virtual std::vector<std::string> readFile() = 0;
    virtual void writeFile(std::vector<std::string> dataset) = 0;
};

class MyInstructionDocument : public InstructionDocument{
public:
    void openFile(const std::string name){
        fs.open(name, std::ios::in);
    }
    void openFileForWrite(const std::string name){
        fs.open(name, std::ios::out);
    }
    bool canOpenDocument(const std::string name){
        fs.open(name,std::ios::in); //success : not 0, fail : 0
        if(!fs){
            return false;
        }
        else{
            fs.close();
            return true;
        }
    }
    bool canWriteDocument(const std::string name){
        fs.open(name,std::ios::out); //success : not 0, fail : 0
        if(!fs){
            return false;
        }
        else{
            fs.close();
            return true;
        }
    }
    std::vector<std::string> readFile(){
        std::string line;
        while(getline(fs, line)){
            instr.push_back(line);
        }
        if(instr.size() == 0){
            throw std::string("file data is empty");
        }

        fs.close();
        return instr;
    }
    void writeFile(std::vector<std::string> dataset){
        for(std::string data : dataset){
            fs << data << "\n";
        }
        fs.close();
    }
private:
    std::fstream fs;
    std::vector<std::string> instr;
};


#endif // DOCUMENT_H_IMCLUDE

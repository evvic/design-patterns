#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Document;

// Example of breaking Interface Segregation Principle:
// One interface with many functions/responsibilites
// Anyone who wants to inherit and override this would need to 
// do so for all methods

//struct IMachine
//{
//  virtual void print(Document& doc) = 0;
//  virtual void fax(Document& doc) = 0;
//  virtual void scan(Document& doc) = 0;
//};
//
//struct MFP : IMachine
//{
//  void print(Document& doc) override;
//  void fax(Document& doc) override;
//  void scan(Document& doc) override;
//};

// 1. Recompile
// 2. Client does not need this
// 3. Forcing implementors to implement too much

// Correct way to follow the Interface Segregation Principle:
// Separate the virtual methods into different interfaces

struct IPrinter
{
    virtual void print(Document& doc) = 0;
};

struct IFax
{
    virtual void fax(Document& doc) = 0;
};

struct IScanner
{
    virtual void scan(Document& doc) = 0;
};

struct Printer : IPrinter
{
    void print(Document& doc) override;
};

struct Scanner : IScanner
{
    void scan(Document& doc) override;
};

struct IMachine: IPrinter, IScanner {};

struct Machine : IMachine
{
    IPrinter& printer;
    IScanner& scanner;

    Machine(IPrinter& printer, IScanner& scanner)
        : 
        printer{printer}, scanner{scanner}
        {}

    void print(Document& doc) override {
        printer.print(doc);
    }
    void scan(Document& doc) override;
};

int main() {
    return 0;
}
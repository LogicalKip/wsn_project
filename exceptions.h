#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

using namespace std;

class DebugException : public exception {

private:
    string err;

public:
    DebugException(string cl, string meth, string info = "") {
        this->err = "\nDEBUG ERROR at " + cl + "::" + meth + ". " + info;
    }

    virtual const char* what() const throw() {
        return err.c_str();
    }

    virtual ~DebugException() throw()
        {}
};

class NegativeResultException : public DebugException {
public:
    NegativeResultException(string cl, string meth, string info = "")
        : DebugException(cl, meth, info)
        {}
    virtual ~NegativeResultException() throw()
        {}
};

class UnhandledCaseException : public DebugException {
public :
    UnhandledCaseException(string cl, string meth, string info = "")
        : DebugException(cl, meth, info)
        {}
    virtual ~UnhandledCaseException() throw()
        {}
};

#endif // EXCEPTIONS_H

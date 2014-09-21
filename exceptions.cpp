#include <exception>
using namespace std;

class NegativeResultException : public exception {
public:
    NegativeResultException(string err) {
        this->err = err;
    }

    virtual const char* what() const throw() {
        return err.c_str();
    }

private:
    string err;

};

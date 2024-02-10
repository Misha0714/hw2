#include "product.h"


class Book : public Product {
public:
    Book(std::string category,  std::string name, double price, int qty,  std::string author,  std::string isbn); 
    ~Book(); 
    std::set<std::string> keywords() const; 

    std::string displayString() const; 

    void dump(std::ostream& os) const; 

    std::string getAuthor() const;
    
    std::string getISBN() const;

private: 
    std::string author_; 
    std::string isbn_; 
}; 
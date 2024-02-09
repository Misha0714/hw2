#include "book.h"
#include "util.h"
#include "product.h"

//constructor 
Book::Book(const std::string category, const std::string name, double price, 
int qty, const std::string author, const std::string isbn) : 
Product(category, name, price, qty)
{
    author_ = author; 
    isbn_ = isbn; 

}

//destructor 
Book::~Book()
{

}

std::set<std::string> Book::keywords() const  {
    
        
    std::set<std::string> authorSet = parseStringToWords(convToLower(author_));
    std::set<std::string> prodNameSet = parseStringToWords(convToLower(name_));  
    std::set<std::string> set; 
    typename std::set<std::string>::iterator it; 

    for(it=authorSet.begin(); it!= authorSet.end(); ++it) {
        set.insert(*it); 
    }


    for(it=prodNameSet.begin(); it!= prodNameSet.end(); ++it) {
        set.insert(*it) ; 
    }

    set.insert(isbn_); 

    return set;
} 
     


std::string Book::displayString() const {
    
    std::string productDisplay =  name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_  + "\n"
    + std::to_string(price_) + std::to_string(qty_) + " left."; 

    return productDisplay; 


     
}

void Book::dump(std::ostream& os) const {

    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ <<"\n" << author_ << std::endl;

}


//get author function 
std::string Book::getAuthor() const {
    return author_; 
}

//get isbn function 
std::string Book::getISBN() const {
    return isbn_; 
}




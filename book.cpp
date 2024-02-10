#include "book.h"
#include "util.h"
#include "product.h"
#include <sstream>
#include <iomanip>

//constructor 
Book::Book(std::string category, std::string name, double price, 
int qty, std::string author, std::string isbn) : 
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
    //iterate through autjor set and insert the author string into there 
    for(it=authorSet.begin(); it!= authorSet.end(); ++it) {
        set.insert(*it); 
    }

    //iterate through prodName set and insert the prdoName string into there 
    for(it=prodNameSet.begin(); it!= prodNameSet.end(); ++it) {
        set.insert(*it) ; 
    }

    set.insert(isbn_); 

    return set;
} 
     


std::string Book::displayString() const {
    
    std::stringstream ss; 
    std::string setPrice; 
    ss << std::setprecision(2) << std::fixed << price_;
    ss >> setPrice;  

    std::string productDisplay =  name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_  + "\n" +
    setPrice + " " + std::to_string(qty_) + " left."; 

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




#include "movie.h"
#include "util.h"
#include "product.h"
#include <sstream>
#include <iomanip>

//constructor 
Movie::Movie(const std::string category, const std::string name, double price, 
int qty, const std::string genre, const std::string rating) : 
Product(category, name, price, qty)
{
    genre_ = genre; 
    rating_ = rating; 

}

//destructor 
Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const  {
    // if it's one char remove it    
    std::set<std::string> set = parseStringToWords(name_);  
    set.insert(convToLower(genre_));
   
  
    return set;
    
} 
     


std::string Movie::displayString() const {

    std::stringstream ss; 
    std::string setPrice; 
    ss << std::setprecision(2) << std::fixed << price_;
    ss >> setPrice;
    
    std::string productDisplay =  name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_  + "\n"
    + setPrice + " " + std::to_string(qty_) + " left."; 

    return productDisplay; 


     
}

void Movie::dump(std::ostream& os) const {

    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;

}


//get author function 
std::string Movie::getGenre() const {
    return genre_; 
}

//get isbn function 
std::string Movie::getRating() const {
    return rating_; 
}
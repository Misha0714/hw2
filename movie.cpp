#include "movie.h"
#include "util.h"
#include "product.h"

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
    
        
    std::set<std::string> genreSet = parseStringToWords(genre_);
    std::set<std::string> prodNameSet = parseStringToWords(name_);  
    std::set<std::string> set; 
    typename std::set<std::string>::iterator it; 

    for(it=genreSet.begin(); it!= genreSet.end(); ++it) {
        set.insert(*it); 
    }


    for(it=prodNameSet.begin(); it!= prodNameSet.end(); ++it) {
        set.insert(*it) ; 
    }

    set.insert(rating_); 

    return set;
} 
     


std::string Movie::displayString() const {
    
    std::string productDisplay =  name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_  + "\n"
    + std::to_string(price_) + std::to_string(qty_) + " left."; 

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
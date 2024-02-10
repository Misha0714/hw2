#include "clothing.h"
#include "util.h"
#include "product.h"
#include <sstream>
#include <iomanip>

//constructor 
Clothing::Clothing(const std::string category, const std::string name, double price, 
int qty, const std::string size, const std::string brand) : 
Product(category, name, price, qty)
{
    size_ = size; 
    brand_ = brand; 

}

//destructor 
Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const  {
    
        
    std::set<std::string> brandSet = parseStringToWords(brand_);
    std::set<std::string> prodNameSet = parseStringToWords(name_);  
    std::set<std::string> set = setUnion(brandSet,prodNameSet); 
    // typename std::set<std::string>::iterator it; 

    // // for(it=sizeSet.begin(); it!= sizeSet.end(); ++it) {
    // //     set.insert(*it); 
    // // }


    // // for(it=prodNameSet.begin(); it!= prodNameSet.end(); ++it) {
    // //     set.insert(*it) ; 
    // // }

    set.insert(size_); 

    return set;
} 
     


std::string Clothing::displayString() const {

    std::stringstream ss; 
    std::string setPrice; 
    ss << std::setprecision(2) << std::fixed << price_;
    ss >> setPrice;  
    
    std::string productDisplay =  name_ + "\n" + "Size: " + size_ + " Brand: " + brand_  + "\n"
    + setPrice + " " + std::to_string(qty_) + " left."; 

    return productDisplay; 


     
}

void Clothing::dump(std::ostream& os) const {

    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n"<< brand_ << std::endl;

}


//get brand function 
std::string Clothing::getBrand() const {
    return brand_; 
}

//get size function 
std::string Clothing::getSize() const {
    return size_; 
}
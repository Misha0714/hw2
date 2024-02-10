#include "user.h"
#include "product.h"
#include "util.h"
#include "user.h"
#include "mydatastore.h"
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <string>
using namespace std; 

//destructor 
MyDataStore::~MyDataStore() {
    // Delete objects in usersVector

    //deleting elements in proudct map 
    std::map<std::string, Product*>::iterator it; 
    for(it=productMap.begin();it!=productMap.end();++it) {
        delete it -> second; 
    }
    //deleting elements in user map 
    std::map<std::string, User*>::iterator it1; 
    for(it1=userMap.begin();it1!=userMap.end();++it1) {
        delete it1 -> second; 
    }



}


void MyDataStore::addProduct(Product* p) {

    //make a keywords set to store all the keywords for a product 
    std::set<std::string> keywords = p->keywords(); 
    //populate key with keywords for each product 
    for(std::set<std::string>::iterator it= keywords.begin(); it!=keywords.end(); ++it) {

        key[*it].insert(p); 

    }
    //insert name of product and product to map 
    productMap[p->getName()] = p;

}

void MyDataStore::addUser(User* u) {


    //userMap.insert(std::make_pair(u->getName(), u)); 
    //insert user into userMap and correspond the name to the user object itself 
    userMap[u->getName()] = u;

}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    
    
    //make a set to put all the products that match the key words in here  
    std::set<Product*> update; 

    //go through the terms vector first 
    for(size_t i=0; i<terms.size(); i++) {
      if(type==0) { //AND
          //if key map find the terms in it 
          if(key.find(terms[i])!=key.end()) {
              //chekc if update is empty 
              if(update.empty()) {
                  //put those terms that match in the key in empty 
                  update = key[terms[i]]; 
                }
                else {
                  //otherwise do setIntersection to find out what terms to put in for AND
                  update = setIntersection(update, key[terms[i]]); 
                }
              }
            }
      if(type==1) { //OR
        for(size_t i=0; i<terms.size(); i++) {
          if(key.find(terms[i])!=key.end()) {
              if(update.empty()) {
                  update = key[terms[i]]; 
                }
                else {
                    update = setUnion(update, key[terms[i]]); 
                }
            }
        }  
    }
  } 
    //convert update set to Product vector and return 
    std::vector<Product*> result(update.begin(), update.end());
    return result; 
  
}

//view cart. Based on the username you should be able to see all the products they have in their set 
void MyDataStore::viewCart(const std::string& username) {

    //use find to find the username in the map 
    if (cart.find(username) != cart.end()) {
        // Username found, print the elements in the queue
        std::vector<Product*> tempVector = cart[username];  
        // std::cout << tempVector.size() << std::endl;
        
        for(size_t i=0;i<tempVector.size();i++) {
          std::cout <<"Item " << i+1 << std::endl;
          std::string s = tempVector[i]->displayString();
          std::cout << s << std::endl;
          
        }
    } else {
      std::cout<< "Invalid username" << std::endl;
    }
}



void MyDataStore::addProductToCart(const std::string& username, Product* product) 
{

    //add the product  
    //checks to see if username is in users 
    std::map<std::string, User*>::iterator it = userMap.find(username);

    if(it!=userMap.end()) {
        //and if it is not nullptr will add product to cart of user 
        if(product != nullptr)
        {
          cart[username].push_back(product);
          return;
        }    
    } else {
        std::cout << "Invalid request" << std::endl; 
        return;

    }
}


void MyDataStore::buyCart(std::string& username) {

    //std::map<std::string, std::queue<Product*>>::iterator it = cart.find(username);
    //std::queue<Product*> tempQueue = it->second; 
    //find the username
    //finding if username is valid 

   std::string lowerUsername = convToLower(username); 
   //cart of the user 
   std::vector<Product*> curr = cart[username]; 

   //make empty variable` to put items that will not be bought 
   std::vector<Product*> unbought_products; 

   if (userMap.find(username)!=userMap.end()) {
    std::cout << "made it" << std::endl;
    //find the size of the cart 
        if(curr.size()>0) {
          std::cout << ">1 thing" << std::endl;
            for(size_t i=0; i<curr.size(); i++) {
                Product* product = curr[i]; 
                if (product->getQty()>0 && userMap[username]->getBalance() >= product->getPrice())   {
                    userMap[username]->deductAmount(product->getPrice()); 
                    product->subtractQty(1); 
                }
                else {
                    unbought_products.push_back(product); 
                }
            }
        }
   }
   else {
        std::cout<< "Invalid username" << std::endl;
   }
   curr = unbought_products;
   cart[username] = curr;
  
}





void MyDataStore::dump(std::ostream& ofile) {

     ofile << "<products>" << std::endl; 
     std::map<std::string, Product*>::iterator it; 
     for(it = productMap.begin();it !=productMap.end();++it) {
            it -> second -> dump(ofile); 
     }
     
     ofile << "</products>" << std::endl; 
     
     
     ofile << "<users>"<< std::endl; 
     std::map<std::string, User*>::iterator it2;
     for(it2=userMap.begin();it2!=userMap.end();++it2) {
            it2 -> second -> dump(ofile); 
     }
     ofile << "</users>" << std::endl; 


}


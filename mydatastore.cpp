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

    std::map<std::string, Product*>::iterator it; 
    for(it=productMap.begin();it!=productMap.end();++it) {
        delete it -> second; 
    }

    std::map<std::string, User*>::iterator it1; 
    for(it1=userMap.begin();it1!=userMap.end();++it1) {
        delete it1 -> second; 
    }



    // for (User* user : usersVector) {
    //     delete user;
    // }
    // // Clear the vector after deleting the objects
    // usersVector.clear();

    // // Delete objects in productVector
    // for (Product* product : productVector) {
    //     delete product;
    // }
    // // Clear the vector after deleting the objects
    // productVector.clear();

}

void MyDataStore::addProduct(Product* p) {

    //keywords to product - already know keywords 
    //make a loop 
    //map data structure that corresponds keyword string to set of products (declare in datamembers)
     //productVector.push_back(p);
    // p.keywords(); 

    //we make a new set of string called keywords to 
    std::set<std::string> keywords = p->keywords(); 

    for(std::set<std::string>::iterator it= keywords.begin(); it!=keywords.end(); ++it) {

        key[*it].insert(p); 

    }

    productMap.insert(std::make_pair(p->getName(), p)); 

    //string s will go through each keyword in p's set 
    // for(std::string s : keywords) {
    //     //keyword does exist in the list 
    //     if(key.find(s)!=key.end()) {
    //         //in the key map it is trying to find s in the set in the map 
    //         key.find(s)->second.insert(p); 
    //     }
    //     else {
    //         std::set<Product*> newset;
    //         newset.insert(p);
    //         //Insert into the map using std::map::insert
    //         key.insert(std::make_pair(s, newset));
    //     }

    // }

}

void MyDataStore::addUser(User* u) {
    //if they press addUser button call this function 

    // std::set<std::string> keywords = u->keywords(); 

    // for(std::set<string>::iterator it=keys.begin(); it!=keys.end(); ++it) {

    //     keyProducts[*it].insert(u); 

    // }

    userMap.insert(std::make_pair(u->getName(), u)); 

    //usersVector.push_back(u); 



}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    
    
    //terms contain keywords you want to retrieve products for 
    //std::set<Product*> set(terms.begin(), terms.end());
    //use a map for keyword to product, string to set of products 
    //Set A will have all the products 
    std::set<Product*> update; 

    //key.find(terms) -> second;


    if(type==1) { //OR 
    //
        for(size_t i=0; i<terms.size(); i++) {
            if(key.find(terms[i])!=key.end()) {
                if(update.empty()) {
                    update = key[terms[i]]; 
                }
                else {
                    update = setIntersection(update, key[terms[i]]); 
                }
            }
        } 
    }

    if(type==0) { //AND
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

    std::vector<Product*> result(update.begin(), update.end());
    return result; 


}

//view cart. Based on the username you should be able to see all the products they have in their set 
void MyDataStore::viewCart(const std::string& username) {

    //use find to find the username in the map 
    std::map<std::string, std::vector<Product*>>::iterator it = cart.find(username);

    if (it != cart.end()) {
        // Username found, print the elements in the queue
        std::vector<Product*> tempVector = it->second;  // Create a temporary queue for display
        while (!tempVector.empty()) {
            Product* product = tempVector.front();
            // Assuming Product has a member function or variable that can be printed
            std::cout << product->getName() << " ";  // Replace with the appropriate function or variable
            tempVector.pop_back();
        }
    }



}


void MyDataStore::addProductToCart(const std::string& username, Product* product) 
{

    //add the product  
    //checks to see if username is in users 
    std::map<std::string, User*>::iterator it = userMap.find(username);

    if(it!=userMap.end()) {
        //and if it is will add product to cart of user 
        cart[username].push_back(product);
        
    }
    else {
      
        std::cout << "Invalid request" << std::endl; 
        return;

    }
 

}

//Buying the cart - You should support the BUYCART username command which should cause the program to iterate through the items in username's cart (case insensitive). 
//If the item is in stock AND the user has enough money it should be removed from the cart, the in stock quantity reduced by 1, and the product price should be debited from the user’s available credit.
// If an item is not in stock or the user does not have enough credit, simply leave it in the cart and go on to the next product. 
//Note: Your cart implementation must iterate through the products in the order they were added.
//If the username provided is invalid, print Invalid username to the screen and do not process the command.
void MyDataStore::buyCart(std::string& username) {

    
   std::string lowerUsername = convToLower(username); 
   //cart of the user 
   std::vector<Product*> curr = cart[username]; 

   //make empty variable` to put items that will not be bought 
   std::vector<Product*> unbought_products; 

   //std::map<std::string, std::queue<Product*>>::iterator it = cart.find(username);
   //std::queue<Product*> tempQueue = it->second; 
    //find the username

    //finding if username is valid 
   if (userMap.find(username)!=userMap.end()) {
    //find the size of the cart 
        if(curr.size()>0) {
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



}
//    //find the user 
//    for(vector<User*>::iterator it=usersVector.begin(); it!=usersVector.end(); ++it) {
//         convToLower(user->getName());  
//     }

//     //if user exists 
//     if (it=usersVector.end()) {
//         cout << "Invalid username" << endl; 
//         return; 
//     }
//     //users balance 
//     double balance = (*it) -> getBalance(); 
//     std::queue<Product*>& cart = [lowercaseUsername]; 

//     //price 
//     double price = 0; 
//     while(!cart.empty()) {
//         Product* product = cart.front(); 
//         cart.pop(); 
//         if(product->getQty()>0) {
//             price += product -> getPrice(); 
//         }

//     }

//     //available or not 
//     if(product->getQty() > 0) {
//        product -> subtractQty(1);  

//     }




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


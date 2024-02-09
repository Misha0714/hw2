#include "datastore.h"
#include "util.h"
#include <map>
#include <set>
#include <queue>
#include <vector>

class MyDataStore : public DataStore {

public: 

    ~MyDataStore(); 

    virtual void addProduct(Product* p); 

    virtual void addUser(User* u); 

    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type); 

    virtual void dump(std::ostream& ofile);

    void viewCart(const std::string& username); 

    void addProductToCart(const std::string& username, Product* product); 

    void buyCart(std::string& username); 

    

private: 

    //map string to set of product 
    std::map<std::string, std::set<Product*>> key;
    
    //users vector (add users easily)
    std::map<std::string, User*> userMap;
    //std::vector<User*> usersVector;   

    //product vector (add products easily)
    std::map<std::string, Product*> productMap;
    //std::vector<Product*> productVector; 

    //make a queue mapping usernames to their carts 
    //std::map<std::string,std::queue<Product*>> cart; 
     std::map<std::string,std::vector<Product*>> cart; 




}; 


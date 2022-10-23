#include <iostream>
#include <vector>
#include "datamodel.h"

std::vector<Product> allProd {
    Product{1,"Apple",3},
    Product{3,"Mango",6},
    Product{2,"Guava",7},
    Product{5,"Banana",4},
    Product{4,"Strawberry",9},
    Product{6,"Pineapple",11}
};

void printProd() {
    std::cout << "Available Products \n";
    for (Product p: allProd) {
        std::cout << p.getDisplayName();
    }
}

Product *chooseProduct() {
    // Display the list of products
    std::string prodList{};
    std::cout << "Available Products \n";
    
    for (Product p: allProd) {
       prodList.append(p.getDisplayName());
    }
    std::cout << prodList << "\n";
    std::cout << "--------------------------\n";
    char choice{};
    std::cin >> choice;
    
    for (size_t i = 0; i < allProd.size(); i++) {
        if (allProd.at(i).getShortName() == std::toupper(choice)) {
            return &allProd.at(i);
        }
    }
    
    std::cout << "Product not found!\n";
    return nullptr;
}

bool checkout(Cart &c) {
    if (c.isEmpty()) {
        std::cerr << "Error, cart is empty\n";
        return false;
    }
    
    int total = c.getTotal();
    std::cout << "Pay in cash ";
    
    int paid{};
    std::cin >> paid;
    
    if (paid >= total) {
        std::cout << "Change " << paid - total << "\n";
        std::cout << "Successfull checkout!\n";
        return true;
    }
    else {
        std::cout << "Payment failed. Not enough cash.\n";
        return false;
    }
}

int main() {
    char act{};
    Cart cart;
    
    while (true) {
        std::cout << "Select an action - a.Add item v.View cart c.Checkout q.Quit\n";
        std::cin >> act;
        act = std::toupper(act);
        if (act == 'A') {
            // Add to cart
            // View products + Choose product + Add to the cart
            std::cout << "  Add to cart\n";
            Product *p = chooseProduct();
            if (p != nullptr) {
                std::cout << "Added to the Cart " << p->getDisplayName() << "\n";
                cart.addProduct(*p);
            }
        }
        else if (act == 'V') {
            // View cart
            std::cout << "  View cart\n";
            std::cout << "--------------------------\n";
            std::cout << cart.viewCart();
            std::cout << "--------------------------\n";
        }
        else if (act == 'C') {
            // View cart
            std::cout << "  Checkout\n";
            std::cout << "--------------------------\n";
            std::cout << cart.viewCart();
            std::cout << "--------------------------\n";
            // Checkout
            if (checkout(cart)) cart.emptyCart();
        }
        else if (act == 'Q') {
            std::cout << "Good Bye.\n";
            break;
        }
        else {
            std::cerr << "Error, no such option\n";
        }
    }
    
    return 0;
}
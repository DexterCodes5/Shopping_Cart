#include <unordered_map>

// Product, Item, Cart
class Product {
    friend class Item;
    friend class Cart;
    int p_id;
    std::string p_name;
    int p_price;
    
public:
    Product() {}
    
    Product(int id, std::string name, int price) :p_id{id}, p_name{name}, p_price{price} {}
    
    std::string getDisplayName() { return p_name + " : Eu " + std::to_string(p_price) + "\n"; };
    
    char getShortName() { return p_name.at(0); }
};

class Item {
    friend class Cart;
    Product prod;
    int quantity;
    
public:
    Item() {}
    Item(Product p, int q) :prod{p}, quantity{q} {}
    
    int getItemPrice() {
        return quantity * prod.p_price;
    }
    
    std::string getItemInfo() {
        return std::to_string(quantity) + " x " + prod.p_name + " Eu " + std::to_string(quantity*prod.p_price) + "\n";
    }
    
};

class Cart {
    // Collection
    std::unordered_map<int,Item> items;
public:
    void addProduct(Product p) {
        if (items.count(p.p_id) == 0) {
            Item new_Item(p,1);
            items[p.p_id] = new_Item;
        }
        else {
            items[p.p_id].quantity += 1;
        }
    }
    
    int getTotal() {
        int total{};
        
        for (std::pair<int,Item> pair: items) {
            total += pair.second.getItemPrice();
        }
        return total;
    }
    
    std::string viewCart() {
        if (items.empty()) {
            return "Cart is empty\n";
        }
        
        std::string itemList{};
        int cart_total = getTotal();
        
        for (std::pair<int,Item> pair: items) {
            Item item = pair.second;
            itemList.append(item.getItemInfo());
        }
        
        return itemList + "\n Total Amount : Eu " + std::to_string(cart_total) + "\n";
    }
    
    bool isEmpty() {
        return items.empty();
    }
    
    void emptyCart() {
        items.clear();
    }
};
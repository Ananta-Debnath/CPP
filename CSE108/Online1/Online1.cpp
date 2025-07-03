#include <iostream>
#include <string>
using namespace std;


class Product
{
    string productName;
    string productID;
    double price;
    int stockChanges[100];
    int numStockChanges;

public:
    void addStock(int amount)
    {
        if (numStockChanges < 100)
        {
            stockChanges[numStockChanges] = amount;
            numStockChanges++;
        }
    }
    
    void reduceStock(int amount)
    {
        if (numStockChanges < 100)
        {
            stockChanges[numStockChanges] = (-1) * amount;
            numStockChanges++;
        }
    }
    
    int getCurrentStock()
    {
        int stock = 0;
        for (int i = 0; i < numStockChanges; i++) stock += stockChanges[i];
        
        return stock;
    }
    
    void display()
    {
        cout << "Product: " << productName << " (ID: " << productID << "), Price: Tk." << price << ", Stock: " << getCurrentStock() << endl;
    }

    Product()
    {
        productName = "No Name";
        productID = "No Id";
        price = 0;
        numStockChanges = 0;
    }

    Product(string productName, string productID, double price)
    {
        this->productName = productName;
        this->productID = productID;
        this->price = price;
        numStockChanges = 0;
    }

    // More Functions
    string getID()
    {
        return productID;
    }

    int getNumStockChanges()
    {
        return numStockChanges;
    }
};


class Inventory
{
    Product* products;
    int numProducts;
    int maxProducts;

public:
    void addProduct(Product p)
    {
        if (numProducts < maxProducts)
        {
            products[numProducts] = p;
            numProducts++;
            cout << "Product added with ID: " << p.getID() << endl;
        }

        else cout << "Inventory full. Cannot add any more product." << endl;
    }

    void updateProductStock(string productID, int amount)
    {
        for (int i = 0; i < numProducts; i++)
        {
            if (productID == products[i].getID())
            {
                if (amount < 0) products[i].reduceStock(abs(amount));

                else products[i].addStock(abs(amount));
            }
        }
    }
    
    void listAllProducts()
    {
        for (int i = 0; i < numProducts; i++)
        {
            products[i].display();
        }
    }
    
    Product getMostStockedProduct()
    {
        int idx = 0, stock = products[0].getCurrentStock(), newStock;
        for (int i = 1; i < numProducts; i++)
        {
            newStock = products[i].getCurrentStock();
            if (newStock > stock || (newStock == stock && products[i].getNumStockChanges() < products[idx].getNumStockChanges()))
            {
                idx = i;
                stock = newStock;
            }
        }

        return products[idx];
    }

    Inventory()
    {
        products = NULL;
        numProducts = 0;
        maxProducts = 0;
    }

    Inventory(int maxProducts)
    {
        products = new Product[maxProducts];
        numProducts = 0;
        this->maxProducts = maxProducts;
    }

    Inventory(Product* products, int numProducts, int maxProducts)
    {
        this->products = new Product[maxProducts];
        this->numProducts = 0;
        this->maxProducts = maxProducts;

        for (int i = 0; i < numProducts; i++) addProduct(products[i]);
    }

    Inventory(const Inventory& inv)
    {
        maxProducts = inv.maxProducts;
        products = new Product[maxProducts];
        numProducts = 0;

        for (int i = 0; i < inv.numProducts; i++)
        {
            products[i] = inv.products[i];
            numProducts++;
        }
    }

    ~Inventory()
    {
        delete[] products;
    }
};


int main() {
    Inventory inv1(5);

    Product p1("Laptop", "P001", 50000);
    Product p2("Smartphone", "P002", 30000);
    Product p3("Tablet", "P003", 25000);
    Product p4("Smartwatch", "P004", 4000);
    Product p5("Headphones", "P005", 2000);
    Product p6("Charger", "P006", 1000);

    inv1.addProduct(p1);
    inv1.addProduct(p2);
    inv1.addProduct(p3);
    inv1.addProduct(p4);
    inv1.addProduct(p5);
    inv1.addProduct(p6);

    inv1.updateProductStock("P001", 50);
    inv1.updateProductStock("P001", -10);
    inv1.updateProductStock("P003", 70);
    inv1.updateProductStock("P002", 70);
    inv1.updateProductStock("P002", -5);
    inv1.updateProductStock("P003", -10);

    cout << "\nProducts in Inventory 1:\n";
    inv1.listAllProducts();

    cout << "\nMost Stocked Product in Inventory 1:\n";
    inv1.getMostStockedProduct().display();

    Inventory inv2 = inv1;

    inv2.updateProductStock("P003", 10);
    inv2.updateProductStock("P002", 10);
    inv2.updateProductStock("P002", -5);

    cout << "\nProducts in Inventory 2:\n";
    inv2.listAllProducts()
    ;
    cout << "\nMost Stocked Product in Inventory 1:\n";
    inv1.getMostStockedProduct().display();

    cout << "\nMost Stocked Product in Inventory 2:\n";
    inv2.getMostStockedProduct().display();

    return 0;
    }
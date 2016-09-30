#include <iostream>

class Market {
public:
	Market()=default;
    Market(unsigned a) : apple(a) { }
    Market(unsigned a, unsigned b) :apple(a), applePrice(b) {}

    Market &appleSold() {
    	apple--;
    	return *this;
    }
    Market &sales() {
      std::cout<< apple <<std::endl;
      return *this;
    }

    unsigned getPrice() {
    	return applePrice*1;
    }
    unsigned getPrice(unsigned a){
    	return applePrice*a;
    }

private:
    unsigned apple = 0;
    unsigned applePrice = 39;
    unsigned getPrice() const;

};


int main(){
    Market eMart(99);
    Market gs25;
    Market homePlus(107, 35);

    std::cout << eMart.getPrice() << std::endl;
    std::cout << eMart.getPrice(12) <<std::endl;

    homePlus.sales().appleSold();
    homePlus.sales();

}

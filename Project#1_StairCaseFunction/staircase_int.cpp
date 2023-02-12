#include <iostream>

int main();

int main() {
	double x{};
	
	std::cout << "Enter value of x: ";
	std::cin >> x;
	
	int stair{};
    int integerNumber{};
    double floatPart{};
    
	if(x>=0) {
        integerNumber=(int)x;
        floatPart=x-integerNumber;
        stair=x-floatPart;
    }

    else {
       integerNumber=(int)x;
       if(integerNumber==x) {
        stair=x;
       }
       else {
        floatPart=1-((-1)*(x-integerNumber));
        stair=x-floatPart;
       }
    }

	std::cout << "The value of stair(x) is: ";
	std::cout << stair;
	std::cout << std::endl;
	
	return 0;
}
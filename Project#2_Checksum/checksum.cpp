#include <iostream>
#include <climits>

int array[9]{};
unsigned int add_checksum(unsigned int n);
bool verify_checksum(unsigned int n);
void add_checksum(unsigned arrays[], std::size_t capacity);
unsigned int remove_checksum(unsigned int n);
void remove_checksum(unsigned arrays[], std::size_t capacity);

#ifndef MARMOSET_TESTING
int main();
#endif

#ifndef MARMOSET_TESTING
int main() {
	unsigned int value_to_protect{2113234};
	unsigned int protected_value = add_checksum(value_to_protect);
	std::cout << "The value " << value_to_protect
		<< " with the checksum added is " << protected_value
		<< "." << std::endl;
	
    if (verify_checksum(protected_value))
	{
		std::cout << "The checksum is valid." << std::endl;
	}
	else   {
		std::cout << "The checksum is invalid." << std::endl;
	} 
	const std::size_t QTY_VALUES {3};
	unsigned int value_series[QTY_VALUES] {20201122, 20209913, 20224012};
	
	add_checksum(value_series, QTY_VALUES);
	
	std::cout << "Series with checksums added: ";
	for (std::size_t series_index {0};
		series_index < QTY_VALUES; series_index++)
	{
		std::cout << value_series[series_index] << " ";
	}

    std::cout << std::endl;
    return 0;
}

#endif

unsigned int add_checksum (unsigned int n) {
    if(n>99999999) {
        return UINT_MAX;
    }
    unsigned int original=n;
    for(int i=7;i>=0;--i) {
        int d=n%10;
        n/=10;
        array[i]=d;
    }

    int sum{0};
    for(int i=0;i<8;i++) {
        if(i%2!=0) {
            if(array[i]*2>=10) {
                int b=array[i]*2;
                int a{0};
                a+=b%10;
                b/=10;
                a+=b%10;
                array[i]=a;
                sum+=array[i];
            }
            else {
                sum+=(array[i]*2);
            }
        }
        else {
            sum+=array[i];
        }
    }
    array[8]=sum*9%10;
    return original*10+array[8];
}

void add_checksum (unsigned int arrays[], std::size_t capacity) {
    for(int i=0;i<capacity;++i) {
        arrays[i] = add_checksum(arrays[i]);
    }
    return;
}

bool verify_checksum(unsigned int n) {
    if(n>999999999) {
        return false;
    }
    else {
        if(n==add_checksum(n/10)) {
            return true;
        }
        else {
            return false;
        }
    }
}

unsigned int remove_checksum(unsigned int n) {
    if(n>999999999) {
        return UINT_MAX;
    }
    if(n==add_checksum(n/10)) {
        return n/10;
    }
    else {
        return UINT_MAX;
    }

}

void remove_checksum(unsigned arrays[], std::size_t capacity) {
    for(int i=0;i<capacity;++i) {
        arrays[i] = remove_checksum(arrays[i]);
    }
    return;
}
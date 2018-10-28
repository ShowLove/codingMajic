// Purpose: demonstrate code reuse

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/*
g++ NumberSystems.cpp -o NumberSystems.out
./NumberSystems.out 2 hex
*/

//// hex /////////////////////////////////////////////////
// In hexadecimal four binary bits represent one hex digit
/*
0000	=	0	1000	=	8
0001	=	1	1001	=	9
0010	=	2	1010	=	A
0011	=	3	1011	=	B
0100	=	4	1100	=	C
0101	=	5	1101	=	D
0110	=	6	1110	=	E
0111	=	7	1111	=	F
*/

/*								////binary////
0hex	=	0dec	=	0oct	0	0	0	0	
1hex	=	1dec	=	1oct	0	0	0	1
2hex	=	2dec	=	2oct	0	0	1	0
3hex	=	3dec	=	3oct	0	0	1	1
4hex	=	4dec	=	4oct	0	1	0	0
5hex	=	5dec	=	5oct	0	1	0	1
6hex	=	6dec	=	6oct	0	1	1	0
7hex	=	7dec	=	7oct	0	1	1	1
8hex	=	8dec	=	10oct	1	0	0	0
9hex	=	9dec	=	11oct	1	0	0	1
Ahex	=	10dec	=	12oct	1	0	1	0
Bhex	=	11dec	=	13oct	1	0	1	1
Chex	=	12dec	=	14oct	1	1	0	0
Dhex	=	13dec	=	15oct	1	1	0	1
Ehex	=	14dec	=	16oct	1	1	1	0
Fhex	=	15dec	=	17oct	1	1	1	1
*/


class NumberSystems {
public:

	NumberSystems(){}
	~NumberSystems(){}

	bool intToChar(int value, char& charDigit) {
		int c = value - 10;
		if (value >= 0 && value <= 9){
			charDigit = '0' + value;
			return true;
		}
		else if (value >= 10 && value <= 15){
			charDigit = 'A' + (value - 10); 
			return true; 
		}
		else{
			// myTODO add cout
			return false;
		}
	}

	/* upper and lower case is treated the same: 0 1 2 3 4 5 6 7 8 9 a = 10 ...
	 * grabs an individual char from a string representation of a hex or a bin
	 * @param char digit of a string
	 * @return returns the decimal value of the char
	 */
	int charToInt(char c) {
		if (c >= '0' && c <= '9') return c - '0';
		else if (c >= 'A' && c <= 'Z') return 10 + c - 'A';
		else if (c >= 'a' && c <= 'z') return 10 + c - 'a';
		return -1;
	}

	bool binaryToHex(string binary, string& hexString, int bytes){

		int bitsInAByte 									  = 8;
		int binaryValue, decimalValue, hexDigitTotalInDecimal = 0;
		int binaryBits  								      = bytes * bitsInAByte;
		char hexCharTemp; 
		string stringDigit;

		int exponent = 3;
		for(int i = 0; i < binaryBits; i++, exponent--){

			// calculate decimal value of current bin digit
			binaryValue = charToInt(binary[i]);
			decimalValue = binaryValue * pow(2, exponent);
			// 4 binary digits equal one hex digit
			hexDigitTotalInDecimal += decimalValue;
			if(i%4 == 3){
				// convert the integer to a hex char and update the hex string
				intToChar(hexDigitTotalInDecimal, hexCharTemp);
				exponent = 4; decimalValue = 0; hexDigitTotalInDecimal = 0;
				hexString += hexCharTemp;
			}
		}

		return true;
	}

	const char* hexCharToBinString(char c)
	{
	    // TODO handle default / error
	    switch(toupper(c))
	    {
	        case '0': return "0000";
	        case '1': return "0001";
	        case '2': return "0010";
	        case '3': return "0011";
	        case '4': return "0100";
	        case '5': return "0101";
	        case '6': return "0110";
	        case '7': return "0111";
	        case '8': return "1000";
	        case '9': return "1001";
	        case 'A': return "1010";
	        case 'B': return "1011";
	        case 'C': return "1100";
	        case 'D': return "1101";
	        case 'E': return "1110";
	        case 'F': return "1111";
	    }

	    cout << "switch failed in hexCharToBinString" << endl;
	    return NULL;
	}

	string hexStringToBinString(const string& hex, string& bin)
	{
	    // TODO use a loop from <algorithm> or smth
	    for(unsigned i = 0; i != hex.length(); ++i)
	       bin += hexCharToBinString(hex[i]);
	    return bin;
	}

	/*
	 * Loops through every character in the string, extract the digit from right to left
	 * operating on it and adding it to the total value
	 * totalDecValue Updates the total value every loop
	 * decValueOfCharDigit individual digit of the value. i.e binary 1 or 0
	 * exponent decreases from right to left 
	 * @param number string representation of binary or hex number
	 * @param base of the number system i.e binary base 2, hex base 16
	 * @return returns the total decimal number
	 */
	int convertToDecimal(string number, int base) {

		int totalDecValue = 0;

		// Only convert base 2 or base 16
		if (base < 2 || (base > 10 && base != 16)) return -1;

		// Travers from right to left
		for (int i = number.length()-1; i >= 0; i--) {
			int decValueOfCharDigit = charToInt(number[i]);
			if (decValueOfCharDigit < 0 || decValueOfCharDigit >= base)
				return -1;
			//Big indean least significant digit on the right
			int exponent = number.length() - 1 - i;
			totalDecValue += decValueOfCharDigit * pow(base, exponent);
		}
		return totalDecValue;
	}
};

class HelperFunctions {
public:

	HelperFunctions(){}
	~HelperFunctions(){}

	/*
	 * Compares string representations of a binary and hex number
	 * @param binary string representation of binary number
	 * @param hex string representation of hex number
	 * @return returns true if they both have the same decimal value
	 */
	bool compare_binary_hex(string binary, string hex) {
		NumberSystems numSys;
		int n1 = numSys.convertToDecimal(binary, 2);
		int n2 = numSys.convertToDecimal(hex, 16);

		// debug use
		cout << "binary string Dec value:"<< n1 << " hex string Dec value:" << n2 << endl;

		if (n1 < 0 || n2 < 0) {
			return false;
		} else {
			return n1 == n2;
		}
	}

	bool debug_charToInt(int bytes, string binOrHex){
		NumberSystems numSys;
		if (binOrHex == "bin"){
			string binaryString = createBinaryString(bytes);
			cout << "created binary string: ";
			cout << binaryString << endl;	

			for (int i = 0; i < binaryString.length(); i++)
				cout << numSys.charToInt(binaryString[i]) << ", ";
			cout << "\n -- " << endl;
		}
		else if (binOrHex == "hex"){
			string hexString = createHexString(bytes);
			cout << "created hex string: ";
			cout << hexString << endl;

			for (int i = 0; i < hexString.length(); i++)
				cout << numSys.charToInt(hexString[i]) << ", ";
			cout << "\n -- " << endl;		
		}else
		{
			cout << "Invalid Input - use either bin or hex. yourInput:" << binOrHex << endl;
			return false;
		}

		return true;
	}

	bool debug_binaryToHex(string binary, string& hexString, int bytes){
		NumberSystems numSys;

		int binaryValue				= 0;
		int decimalValue   			= 0;
		int hexDigitTotalInDecimal 	= 0;
		int bitsInAByte 			= 8;		
		int binaryBits  			= bytes * bitsInAByte;
		char hexCharTemp;
		string stringDigit;

		int exponent = 3;
		for(int i = 0; i < binaryBits; i++, exponent--){
			binaryValue = numSys.charToInt(binary[i]);
			cout << "binary_value:" << binaryValue << endl;
			decimalValue = binaryValue * pow(2, exponent);
			hexDigitTotalInDecimal += decimalValue;
			cout << "Decimal:" << decimalValue  << "= bin:" <<binaryValue<<" * 2^exponent:" << exponent <<endl;
			if(i%4 == 3){
				cout << "(i%4 == 3) index:" << i << endl;
				cout << "hexTotal:" << hexDigitTotalInDecimal << endl;

				numSys.intToChar(hexDigitTotalInDecimal, hexCharTemp);
				exponent = 4;
				decimalValue = 0;
				hexDigitTotalInDecimal = 0;
				cout << "hexChar:" << hexCharTemp << endl;
				hexString += hexCharTemp;
				cout << "hexString" << hexString << "\n\n" << endl;
			}
		}

		return true;
	}

	string createBinaryString(int bytes){

		srand(time(NULL));
		int bits = bytes * 8;
		string binaryString;

		for (int i = 0; i < bits; i++){
			int binaryDigit = rand() % 2;
			binaryString += ('0' + binaryDigit);
		}

		return binaryString;
	}

	string createHexString(int bytes){

		srand(time(NULL));
		int hexValues = bytes * 2;
		string binaryString;

		for(int i = 0; i < hexValues; i++){
			int hexDigit = rand() % 15;
			binaryString += (hexDigit < 10) ? ('0' + hexDigit) : 'A' + (hexDigit - 10);
		}

		return binaryString;
	}

};

int main(int argc, char** argv)
{
	NumberSystems numSys;
	HelperFunctions helper;
	cout << "argc = " << argc << endl;
	cout << "Param 1 the number of bytes you want to create" << endl;
	cout << "Param 2: hex or bin -- the number system you want to manipulate" << endl;

	// Default values
	int bytes = 1;
	string nuberSystem = "bin";


	// If user entered both prameters use them instead of the default values and run debug
	if ( argc == 3){
		bytes  = atoi(argv[1]);
		nuberSystem = argv[2];
		cout << "debug: digit to value" << endl;
		helper.debug_charToInt(bytes, nuberSystem);
	}

	string hexString    = helper.createHexString(bytes);
	string binaryString = helper.createBinaryString(bytes);

	cout << "hString:" << hexString << "\nbString:" << binaryString << endl;

	cout << "Randomly Generated strings" << endl;
	if (helper.compare_binary_hex(binaryString, hexString))
		cout << "numbers were equal" << endl;
	else
		cout << "numbers were not equal" << endl;

	string outValue;
	numSys.binaryToHex(binaryString, outValue, bytes); //myTODO if
	cout << "binary to hex conversion" << endl;
	if (helper.compare_binary_hex(binaryString, outValue))
		cout << "numbers were equal" << endl;
	else
		cout << "numbers were not equal" << endl;
	cout << "hString:" << outValue << "\nbString:" << binaryString << endl;

	hexString = outValue;
	binaryString.clear();
	numSys.hexStringToBinString(hexString, binaryString); //myTODO if
	cout << "hex to binary conversion" << endl;
	if (helper.compare_binary_hex(binaryString, outValue))
		cout << "numbers were equal" << endl;
	else
		cout << "numbers were not equal" << endl;
	cout << "hString:" << outValue << "\nbString:" << binaryString << endl;


	return 0;
}

//============================================================================
// Name        : ECE4270Lab2.cpp
// Author      : Yihe Wang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//int *sixBitZero = (int *)malloc(sizeof(int)*6);

void writeBubbleSort();
void writeFibonacci();
string transvertInstruction(string);
int *R_Type_Concatenate(int *, int *, int *, int *);
vector<string> readNumber(vector<string>);
int* getPartialInstruction(string, int);//take one line of code as input, and return one line of machine code
int *storeBinaryInArray(int, int);//take size and number as input, reture an int array to store binary number
string binaryToHex(int *);//take 32 bits binary array as input, get a hexidecimal output
char decimalToHex(int);//take a decimal as input, return a hexidecimal char
void printArray(int *, int);
//

void writeBubbleSort()
{

}

void writeFibonacci()
{

}

vector<string> readNumber(vector<string> result)
{
	vector<string> numberList;
	numberList.push_back("7");
	numberList.push_back("6");
	numberList.push_back("6");
	return numberList;
}

int* getPartialInstruction(string partialInstruction, int size)
{
	int number = stoi(partialInstruction);
	//cout<<number<<endl;
	int *partialInstructionBinary = storeBinaryInArray(number,size);

	//get binary code for partial instruction, ex. rt is 5-bit
	return partialInstructionBinary;
}

int *storeBinaryInArray(int number, int size)
{
	int *binaryArray = (int*)malloc(sizeof(int)*size);
	int a, b;

	for(int i = size - 1; i >= 0; --i){
		a = number % 2;
		b = number / 2;
		number = b;
		binaryArray[i] =  a;
	}
	//return int array stored binary number
	return binaryArray;
}

int *R_Type_Concatenate(int *rs, int *rt, int *rd, int *funct)
{
	int* thirtyTwoBits = (int *)malloc(sizeof(int)*32);
	for(int k = 0; k < 32; ++k){
		thirtyTwoBits[k] = 0;
	}

	int i;
	int j = 0;
	for(i = 6; i < 11; ++i){
		thirtyTwoBits[i] = rs[j];
		++j;
	}//store rs into binary array

	j = 0;
	for(i = 11; i < 16; ++i){
		thirtyTwoBits[i] = rt[j];
		++j;
	}//store rt into binary array

	j = 0;
	for(i = 16; i < 21; ++i){
		thirtyTwoBits[i] = rd[j];
		++j;
	}//store rd into binary array

	j = 0;
	for(i = 26; i < 32; ++i){
		thirtyTwoBits[i] = funct[j];
		++j;
	}//store funct code into binary array

	return thirtyTwoBits;
}

string binaryToHex(int *thirtyTwoBits)
{
	string machineInstruction = "00000000";
	int i;
	for(i = 0; i < 8; ++i){
		int tempNum = 0;
		int j;
		for(j = 0; j < 4; ++j){
			if(j == 0){
				tempNum = thirtyTwoBits[j + 4*i] * 8 + tempNum;
			}
			else if(j == 1){
				tempNum = thirtyTwoBits[j + 4*i] * 4 + tempNum;
			}
			else if(j == 2){
				tempNum = thirtyTwoBits[j + 4*i] * 2 + tempNum;
			}
			else if(j == 3){
				tempNum = thirtyTwoBits[j + 4*i] * 1 + tempNum;
			}
		}//transvert 4 bits into a decimal number
		//cout<<tempNum<<endl;
		machineInstruction[i] = decimalToHex(tempNum);
	}//every 4 bits as a loop

	return machineInstruction;
}

char decimalToHex(int tempNum)
{
	char *hex = (char *)malloc(sizeof(char));
	if(tempNum >= 10){
		switch(tempNum){
			case 10:
				hex[0] = 'A';
				break;
			case 11:
				hex[0] = 'B';
				break;
			case 12:
				hex[0] = 'C';
				break;
			case 13:
				hex[0] = 'D';
				break;
			case 14:
				hex[0] = 'E';
				break;
			case 15:
				hex[0] = 'F';
				break;
		}
	}// number bigger than 9
	else{
		sprintf(hex,"%d",tempNum);
	}//number smaller than 9

	return hex[0];
}

void printArray(int *binaryArray, int size)
{
	int i;
	for(i = 0; i < size - 1; ++i){
		cout<<binaryArray[i];
	}
	cout<<binaryArray[i]<<endl;
}

string transvertInstruction(string oneLine)
{
	//string instruction;// Like ADD, ADDI
	int *rs;
	int *rd;
	int *rt;
	int *funct = (int*)malloc(sizeof(int)*6);
	string machineInstruction;
	int *thirtyTwoBits;
	string tempResult;
	vector<string> result;//store the seperated strings
	stringstream input(oneLine);
	vector<string> numberList;

	while(input>>tempResult){
		result.push_back(tempResult);
	}// get the seperated strings and put into vector result

	cout<<result[0]<<endl;

	if(result[0] == "ADD"){
		cout<<"Instruction ADD start"<<endl;
		numberList = readNumber(result);
		rs = getPartialInstruction(numberList[0], 5);
		rd = getPartialInstruction(numberList[1], 5);
		rt = getPartialInstruction(numberList[2], 5);
		funct = getPartialInstruction("100000", 6);// ADD is 10 0000
		thirtyTwoBits = R_Type_Concatenate(rs, rd, rt, funct);
		printArray(thirtyTwoBits,32);
		machineInstruction = binaryToHex(thirtyTwoBits);
		//get all the number in sequence in one line of code
	}
	else if(result[0] == "ADDU"){
		cout<<"Instruction ADDU"<<endl;
	}
	else if(result[0] == "ADDI"){
		cout<<"Instruction ADDI"<<endl;
	}
	else if(result[0] == "ADDIU"){
		cout<<"Instruction ADDIU"<<endl;
	}
	else if(result[0] == "SUB"){
		cout<<"Instruction SUB"<<endl;
	}
	else if(result[0] == "SUBU"){
		cout<<"Instruction SUBU"<<endl;
	}
	else if(result[0] == "MULT"){
		cout<<"Instruction MULT"<<endl;
	}
	else if(result[0] == "MULTU"){
		cout<<"Instruction MULTU"<<endl;
	}
	else if(result[0] == "DIV"){
		cout<<"Instruction DIV"<<endl;
	}
	else if(result[0] == "DIVU"){
		cout<<"Instruction DIVU"<<endl;
	}
	else if(result[0] == "AND"){
		cout<<"Instruction AND"<<endl;
	}
	else if(result[0] == "ANDI"){
		cout<<"Instruction ANDI"<<endl;
	}
	else if(result[0] == "DIVU"){
		cout<<"Instruction DIVU"<<endl;
	}
	else if(result[0] == "OR"){
		cout<<"Instruction OR"<<endl;
	}
	else if(result[0] == "ORI"){
		cout<<"Instruction ORI"<<endl;
	}
	else if(result[0] == "XOR"){
		cout<<"Instruction XOR"<<endl;
	}
	else if(result[0] == "XORI"){
		cout<<"Instruction XORI"<<endl;
	}
	else if(result[0] == "NOR"){
		cout<<"Instruction NOR"<<endl;
	}
	else if(result[0] == "SLT"){
		cout<<"Instruction SLT"<<endl;
	}
	else if(result[0] == "SLTI"){
		cout<<"Instruction SLTI"<<endl;
	}
	else if(result[0] == "SLL"){
		cout<<"Instruction SLL"<<endl;
	}
	else if(result[0] == "SRL"){
		cout<<"Instruction SRL"<<endl;
	}
	else if(result[0] == "SRA"){
		cout<<"Instruction SRA"<<endl;
	}
	else if(result[0] == "LW"){
		cout<<"Instruction LW"<<endl;
	}
	else if(result[0] == "LB"){
		cout<<"Instruction LB"<<endl;
	}
	else if(result[0] == "LH"){
		cout<<"Instruction LH"<<endl;
	}
	else if(result[0] == "LUI"){
		cout<<"Instruction LUI"<<endl;
	}
	else if(result[0] == "SW"){
		cout<<"Instruction SW"<<endl;
	}
	else if(result[0] == "SB"){
		cout<<"Instruction SB"<<endl;
	}
	else if(result[0] == "SH"){
		cout<<"Instruction SH"<<endl;
	}
	else if(result[0] == "MFHI"){
		cout<<"Instruction MFHI"<<endl;
	}
	else if(result[0] == "MFLO"){
		cout<<"Instruction MFLO"<<endl;
	}
	else if(result[0] == "BEQ"){
		cout<<"Instruction BEQ"<<endl;
	}
	else if(result[0] == "BNE"){
		cout<<"Instruction BNE"<<endl;
	}
	else if(result[0] == "BLEZ"){
		cout<<"Instruction BLEZ"<<endl;
	}
	else if(result[0] == "BLTZ"){
		cout<<"Instruction BLTZ"<<endl;
	}
	else if(result[0] == "BGEZ"){
		cout<<"Instruction BGEZ"<<endl;
	}
	else if(result[0] == "BLTZ"){
		cout<<"Instruction BLTZ"<<endl;
	}
	else if(result[0] == "BGTZ"){
		cout<<"Instruction BGTZ"<<endl;
	}
	else if(result[0] == "J"){
		cout<<"Instruction J"<<endl;
	}
	else if(result[0] == "JR"){
		cout<<"Instruction JR"<<endl;
	}
	else if(result[0] == "JAL"){
		cout<<"Instruction JAL"<<endl;
	}
	else if(result[0] == "JALR"){
		cout<<"Instruction JALR"<<endl;
	}

	return machineInstruction;
}


int main() {
	//writeBubbleSort();
	//writeFibonacci();

	string oneLine = "ADD $7, $6, $6";
	string machineInstruction;
	machineInstruction = transvertInstruction(oneLine);
	cout<<machineInstruction<<endl;
	return 0;
}





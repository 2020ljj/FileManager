#ifndef ERROR_H
#define ERROR_H
#include<iostream>
#include <iomanip>
#include<string>
using namespace std;
using std::setw;
class Error {
private:
	int flag;
public:
	Error(int Flag) {
		flag = Flag;
	}
	void what();
};

void Error::what() {
	if (flag == 1)
		cout << "PermissionError！" << endl;	//权限错误
	else if (flag == 2) {
		cout << "FileNumberOutofRange！" << endl;	//文件数量超范围
	}
	else if (flag == 3) {
		cout << "FileNotFound！" << endl;	//文件不存在
	}
	else if (flag == 4) {
		cout << "UserNotFound！" << endl;	//用户不存在
	}
	else if (flag == 5) {
		cout << "InputError！" << endl;	//输入异常
	}
	else if (flag == 6) {
		cout << "UserNumberOutofRange！" << endl;	//文件数量超范围
	}
	else
		cout << "错误不在预定范围内" << endl;
}




#endif // !ERROR_H

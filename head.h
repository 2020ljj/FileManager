#ifndef  HEAD_H
#define HEAD_H
#include<vector>
#include"Error.h"

class File {
private:
	string fileName;
	//bool ifOpen;								
	bool protectCode[3];						//从0~2，分别为写、读、执行
	int length;
public:
	File() {
		fileName = "unknown";
		//ifOpen = false;
		protectCode[0] = false;
		protectCode[1] = false;
		protectCode[2] = false;
		length = 0;
	}
	File(string name, string Code,int filelength) {
		if (Code.size() != 3)
			throw(Error(5));
		else {
			fileName = name;
			protectCode[0] = Code[0] == '0' ? 0 : 1;
			protectCode[1] = Code[1] == '0' ? 0 : 1;
			protectCode[2] = Code[2] == '0' ? 0 : 1;
			length = filelength;
			//ifOpen = false;
		}

	}
	void FileNameChange(string filename);		//1、文件名修改
	void FileWirte(int characterLength);		//2、文件写入数据：只修改文件内容长度length
	int FileRead();								//3、文件读取：只读取文件文本长度length
	void FileCodeChange(int i);					//4、文件保护码修改
	string GetFileName();						//5、返回文件名	
	string GetCode();							//6、返回文件代码
};

class UFD {							//用户文件目录
private:
	string userName;
	vector<File*> fileDirectory;	//存放文件指针
	int fileNumber;					//文件数量
public:
	UFD() {
		userName = "unkonwn";
		fileNumber = 0;
	}
	UFD(string name) {
		userName = name;
		fileNumber = 0;
	}
	File* fileAdd(string name, string Code, int filelength);	//1、增加一个文件，返回文件指针
	File* fileDelete(string filename);							//2、从用户目录删除一个文件
	void showALLFile();											//3、展示用户拥有的所有文件
	File* SearchFile(string filename);							//4、搜索文件
	string GetUserName();										//5、返回用户名
};

class MDF {						//主文件目录
private:
	vector<UFD*> UFDDirectory;	//存放目录区指针
	int userNumber;
public:
	MDF() {
		userNumber = 0;
	}
	UFD* AddUser(string userName);					//1、新增用户
	UFD* SearchUser(string userName);				//2、查询用户
};
//////****MDF类方法实现****//////
UFD* MDF::AddUser(string userName) {
	if (userNumber > 9)
		throw(Error(6));
	else {
		UFD* newuser = new UFD(userName);
		UFDDirectory.push_back(newuser);
		userNumber++;
		return newuser;
	}
	return NULL;
}
UFD* MDF::SearchUser(string userName) {
	if (userNumber < 1)
		throw(Error(2));			//文件范围越界
	else {
		int i = 100;
		int n = UFDDirectory.size();
		for (i = 0; i < n; i++) {
			if (UFDDirectory[i]->GetUserName() == userName) {
				return UFDDirectory[i];
				break;
			}
		}
	}
	return NULL;
}
//////****UFD类方法实现****//////
File* UFD::fileAdd(string filename, string Code, int filelength) {
	if (fileNumber > 9)
		throw(Error(2));		//文件范围异常
	else {
		File* newfile = new File(filename,Code,filelength);
		fileDirectory.push_back(newfile);
		fileNumber++;
		return newfile;
	}
	return NULL;
}
File* UFD::fileDelete(string filename) {
	if (fileNumber < 1)
		throw(Error(2));			//文件范围越界
	else {
		int i = 100;
		int n = fileDirectory.size();
		
		for (i = 0; i < n; i++) {
			if (fileDirectory[i]->GetFileName() == filename) {
				File* file = fileDirectory[i];
				fileDirectory.erase(fileDirectory.begin()+i);
				fileNumber--;
				return file;
			}
		}
		return NULL;
	}
}
void UFD::showALLFile() {
	cout << "YOUR FILE DIRECTORY:" << fileNumber << endl;
	cout << setw(15) << "FILE NAME" << setw(30) << "PROTECTION CODE" << setw(30) << "LENGTH" << endl;
	for (int i = 0; i < fileDirectory.size(); i++) {
		cout << setw(15) << fileDirectory[i]->GetFileName()
			<< setw(30) << fileDirectory[i]->GetCode() 
			<< setw(30) << fileDirectory[i]->FileRead() << endl;
	}
}
File* UFD::SearchFile(string filename) {
	int i = 100;
	int n = fileDirectory.size();
	for (i = 0; i < n; i++) {
		if (fileDirectory[i]->GetFileName() == filename) {
			return fileDirectory[i];
			break;
		}
	}
	return NULL;
}
string UFD::GetUserName() {
	return userName;
}
//////****File类方法实现****//////
void File::FileNameChange(string filename) {
	fileName = filename;
}
void File::FileWirte(int characterLength) {
	length += characterLength;
}
int File::FileRead() {
	return length;
}
/*bool* File::FileCodeRead() {
	return protectCode;
}*/
void File::FileCodeChange(int i) {
	protectCode[i] = protectCode[i] == true ? false : true;
}
string File::GetFileName() {
	return fileName;
}
string File::GetCode() {
	string strtemp;
	for (int i = 0; i < 3; i++) {
		if (protectCode[i])
			strtemp.push_back('1');
		else
			strtemp.push_back('0');
	}
	return strtemp;
}
#endif // ! HEAD_H

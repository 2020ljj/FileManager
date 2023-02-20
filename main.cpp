#include"head.h";

void ShowRun(vector<File*>afd);			//展示运行队列

int main() {
	string userName = "";
	MDF *mdf = new MDF();
	UFD *ufd = new UFD();
	File* file = new File();
	ufd = mdf->AddUser("YOUJIN");
	string codetemp;
	string command;
	string fileName;
	int openIndex,tempIndex;
	ufd->fileAdd("XUMAIN", "111", 9999);
	ufd->fileAdd("F1", "111", 0);
	ufd->fileAdd("YOUJINYU", "111", 100);
	//ufd->showALLFile();
	vector<File*> AFD;
	try {
		while (command != "BYE") {
			cout << "RUN" << endl;
			cout << "YOUR NAME ?\t";
			cin >> userName;
			ufd = mdf->SearchUser(userName);
			if (ufd == NULL) {
				cout << "YOUR NAME IS NOT IN THE USER NAME TABLE,TRY AGAIN. " << endl;
				continue;
			}
			else
				ufd->showALLFile();
			cout << "COMMAND NAME ?";
			cin >> command;
			while (command != "BYE") {
				if (command == "CREATE") {
					cout << "THE NEW FILE S NAME?\t";
					cin >> fileName;
					cout << "THE NEW FILE’S PROTECTION CODE ?\t";
					cin >> codetemp;
					file = ufd->fileAdd(fileName, codetemp, 0);
					cout << "THE NEW FILE IS CREATED. " << endl;
				}
				else if (command == "DELETE") {
					cout << "FILE NAME TO BE DELETE?\t";
					cin >> fileName;
					file = ufd->SearchFile(fileName);
					if (file == NULL)
						cout << "ERROR MESSAGE:THIS FILE IS UNEXITED !!!" << endl;
					else {
						cout << "ENTER THE CODE? \t";
						cin >> codetemp;
						if (codetemp == file->GetCode()) {
							for (int i = 0; i < AFD.size(); i++) {
								if (AFD[i]->GetFileName() == fileName)
									AFD.erase(AFD.begin() + i);
							}
							ufd->fileDelete(fileName);
						}
						else
							cout << "ERROR MESSAGE:CODE IS FALSE !!!" << endl;
					}
				}
				else if (command == "OPEN") {
					cout << "FILE NAME TO BE OPENED?\t";
					cin >> fileName;
					file = ufd->SearchFile(fileName);
					if (file == NULL)
						cout << "ERROR MESSAGE:THIS FILE IS UNEXITED !!!" << endl;
					else {
						cout << "ENTER THE OPEN MODE? \t";
						cin >> codetemp;
						if (codetemp == file->GetCode()) {
							cout << "THIS FILE IS OPENED,ITS OPEN NUMBER IS\t";
							AFD.push_back(file);
							cout << AFD.size()-1 << endl;
						}
						else
							cout << "ERROR MESSAGE:OPEN NUMBER IS FALSE !!!" << endl;
					}
				}
				else if (command == "CLOSE") {
					ShowRun(AFD);
					cout << "THE OPENED FILE NUMBER TO BE CLOSED? \t";
					cin >> openIndex;
					if (openIndex<0 || openIndex>=AFD.size())
						cout << "ERROR MESSAGE:INPUT ERROR!!!" << endl;
					else {
						AFD.erase(AFD.begin() + openIndex);
					}
				}
				else if (command == "READ") {
					//只可以读取已打开的文件
					ShowRun(AFD);
					cout << "OPEN FILE NUMBER? " << "\t";
					cin >> openIndex;
					if (openIndex<0 || openIndex>=AFD.size())
						cout << "ERROR MESSAGE:INPUT ERROR!!!" << endl;
					else {
						file = AFD[openIndex];
						if (file->GetCode()[1] == '1')			//如果文件可读
							cout << "THIS FILE LENGTH IS\t" << file->FileRead() << endl;
						else
							cout << "ERROR MESSAGE:THIS FILE IS NOT ALLOWED TO READ!!!" << endl;
					}
				}

				else if (command == "WRITE") {
					//只可以写入已打开的文件
					ShowRun(AFD);
					cout << "OPEN FILE NUMBER?\t";
					cin >> openIndex;
					if (openIndex<0 || openIndex>=AFD.size())
						cout << "ERROR MESSAGE:INPUT ERROR!!!" << endl;
					else {
						file = AFD[openIndex];
						if (file->GetCode()[0] == '1') {//如果文件可写
							cout << "HOW MANY CHARACTERS TO BE WRITTEN INTO THAT FILE?\t";
							cin >> tempIndex;
							file->FileWirte(tempIndex);
						}
						else
							cout << "ERROR MESSAGE:THIS FILE IS NOT ALLOWED TO WRITE!!!" << endl;
					}
				}
				else if (command == "SHOWRUN")
					ShowRun(AFD);

				else if(command =="SHOWDIR")
					ufd->showALLFile();
				else  {
					cout << "COMMAND NAME GIVEN IS WRONG! IT SHOULD BE ONE OF FOLLOWING : CREATE, DELETE, OPEN, CLOSE, READ, WRITE, BYE,SHOWRUNG,SHOWDIR .TRY AGAIN" << endl;
				}
				cout << "COMMAND NAME ?\t";
				cin >> command;
			}

		}
		cout << "GOODBYE AND WISH LUCK!" << endl;
	}
	catch (Error& e) {
		e.what();
	}


	delete file;
	delete ufd;
	delete mdf;
	return 0;
}
void ShowRun(vector<File*>afd) {
	cout << "THE RUNNING LIST IS FOLOWING:" << endl;
	int n = afd.size();
	if (0 == n) {
		cout << "THE RUNNING LIST IS EMPTY" << endl;
	}
	else
		for (int i = 0; i < afd.size(); i++) {
			cout << i << ":\t" << afd[i]->GetFileName() << endl;
		}
}
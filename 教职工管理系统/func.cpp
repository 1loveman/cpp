#include"func.h"



func::func(){
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		EmpNum = 0;
		EmpArr = NULL;
		m_isEmpty = true;
	}
	else {
		char ch;
		ifs >> ch;
		if (ifs.eof()) {
			cout << "文件为空" << endl;
			EmpNum = 0;
			EmpArr = NULL;
			m_isEmpty = true;
		}
		else {
			int num = GetEmpNum();
			cout << "文件现有" << num << "名员工" << endl;
			this->EmpNum = num;
			this->EmpArr = new Worker * [this->EmpNum];
			Init_EmpArr();
			m_isEmpty = false;
		}

	}
	ifs.close();

}

func::~func() {
	if (EmpArr) {
		delete[] EmpArr;
		EmpArr = NULL;
	}
}

//打印菜单
void func::Menu() {
	cout << "*******************************" << endl;
	cout << "***** 0、退出当前管理系统 *****" << endl;
	cout << "***** 1、添加职工         *****" << endl;
	cout << "***** 2、显示全部员工信息 *****" << endl;
	cout << "***** 3、删除指定员工     *****" << endl;
	cout << "***** 4、修改指定员工     *****" << endl;
	cout << "***** 5、查找指定员工信息 *****" << endl;
	cout << "***** 6、排序员工         *****" << endl;
	cout << "***** 7、清空所有文档     *****" << endl;
	cout << "*******************************" << endl;
}

//保存文件
void func::Save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->EmpNum;i++) {
		ofs << EmpArr[i]->m_Id<<"\\"
			<< EmpArr[i]->m_Name<<"\\ "
			<< EmpArr[i]->m_DeptId
			<< endl;
	}
	ofs.close();
}

//添加成员
void func::Add() {
	int AddNum;
	cout << "请输入需要添加新成员个数:>";
	cin >> AddNum;
	if (AddNum > 0) {
		Worker** NewSpace = new Worker * [EmpNum + AddNum];
		if (EmpNum) {
			for (int i = 0; i < EmpNum; i++) {
				NewSpace[i] = EmpArr[i];
			}
		}
		for (int i = 0; i < AddNum; i++) {
			int id;
			string name;
			int Select;
			cout << "请输入要添加的职工编号:>";
			cin >> id;
			cout << "请输入要添加职工的姓名:>";
			cin >> name;
			cout << "请选择要添加职工的岗位" << endl;
			cout << "1---普通员工" << endl
				<< "2---经理" << endl
				<< "3---老板" << endl;
			do {
				cout << "请选择编号:>";
				cin >> Select;
				if (Select < 1 || Select>3) {
					cout << "输入有误" << endl;;
				}
			} while (Select < 1 || Select>3);
			
			Worker* worker = NULL;
			switch (Select) {
			case 1:
				worker = new Employee(id, name, Select);
				break;
			case 2:
				worker = new Employee(id, name, Select);
				break;
			case 3:
				worker = new Employee(id, name, Select);
				break;
			default:
				break;
			}
			NewSpace[EmpNum + i] = worker;
		}
		if (EmpArr) {
			delete[] EmpArr;
		}
		this->EmpArr = NewSpace;
		this->EmpNum = EmpNum + AddNum;
		Save();

		cout << "成功添加" << AddNum << "名新员工" << endl;
		this->m_isEmpty = false;
	}
	else {
		cout << "输入有误" << endl;
	}
	system("pause");
	system("cls");
	
}

//退出程序
void func::Exit() {
	cout << "退出成功，欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

//计算雇员数量。
int func::GetEmpNum() {
	int num = 0;
	int id;
	string name;
	int did;
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	while (ifs >> id && ifs >> name && ifs >> did) {
		num++;
	}
	ifs.close();
	return num;
}

//初始化成员
void func::Init_EmpArr() {
	int id;
	string name;
	int did;
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	Worker* worker = NULL;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did) {//ofs>>遇到空格停止
		if (did == 1) {
			worker = new Employee(id, name, did);
		}
		else if (did == 2) {
			worker = new Manager(id, name, did);
		}
		else {
			worker = new Boss(id, name, did);
		}
		this->EmpArr[index] = worker;
		index++;
	}
	ifs.close();
}

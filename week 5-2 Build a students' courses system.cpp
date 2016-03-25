#include<iostream>
#include<vector>
#include<string>
using namespace std;
struct Course_name_score
{
	string course_name;
	string score;
};
struct Student_name_id
{
	string student_name;
	string student_id;
};
class StudentDataHandler 
{
private:
	vector<Student_name_id> studentData_store;
	vector<vector<Course_name_score>> courseData_store;
public:
	int AddStudent(Student_name_id);
	int RemoveStudent(string);
	int SearchStudent(string);

	int AddCourse(Course_name_score, string);
	int RemoveCourse(string,string);
	int ModifyCourse(string,Course_name_score);
};
int StudentDataHandler::AddStudent(Student_name_id addstudentdata)
{
	for (int i = 0; i < studentData_store.size(); i++)
	{
		if (studentData_store[i].student_name == addstudentdata.student_name || studentData_store[i].student_id == addstudentdata.student_id)
			return 0;
	}
	studentData_store.push_back(addstudentdata);
	return 1;
}
int StudentDataHandler::RemoveStudent(string SID_SName)
{
	for (int i = 0; i < studentData_store.size(); i++)
	{
		if (studentData_store[i].student_name == SID_SName || studentData_store[i].student_id == SID_SName)
		{
			courseData_store.erase(courseData_store.begin() + i);
			studentData_store.erase(studentData_store.begin() + i);
			return 1;
		}
	}
	return 0;
}
int StudentDataHandler::SearchStudent(string SID_SName)
{
	if (SID_SName.compare("All") == 0)
	{
		for (int i = 0; i < studentData_store.size(); i++)
		{
			cout << studentData_store[i].student_name << endl;
			cout << studentData_store[i].student_id << endl;
			for (int j = 0; j < courseData_store[i].size(); j++)
				cout << courseData_store[i][j].course_name << ' ' << courseData_store[i][j].score << endl ;
			cout << endl;
		}
		return 1;
	}
	else {
		for (int i = 0; i < studentData_store.size(); i++)
		{
			if (studentData_store[i].student_name == SID_SName || studentData_store[i].student_id == SID_SName)
			{
				cout << studentData_store[i].student_name << endl;
				cout << studentData_store[i].student_id << endl;
				for (int j = 0; j < courseData_store[i].size(); j++)
					cout << courseData_store[i][j].course_name << ' ' << courseData_store[i][j].score << endl ;
				cout << endl;
				return 1;
			}
		}
		return 0;
	}
}
int StudentDataHandler::AddCourse(Course_name_score addcoursedata, string Name_Sid)
{
	courseData_store.resize(studentData_store.size());
	for (int i = 0; i < studentData_store.size(); i++)
	{
		if (studentData_store[i].student_id == Name_Sid || studentData_store[i].student_name == Name_Sid)
		{
			for (int j = 0; j < courseData_store[i].size(); j++)	//曾卡在這,因為設了j<courseData_store.size()造成超出範圍
			{
				if (courseData_store[i].empty() == 0)
				{
					if(courseData_store[i][j].course_name.compare(addcoursedata.course_name) == 0)
						return 0;
				}
			}
			courseData_store[i].push_back(addcoursedata);
			return 1;
		}
	}
	return 0;
}
int StudentDataHandler::RemoveCourse(string SID_SName ,string Remove_Course_Name)
{
	for (int i = 0; i < studentData_store.size(); i++)
	{
		if (studentData_store[i].student_id == SID_SName || studentData_store[i].student_name == SID_SName)
		{
			for (int j = 0; j < courseData_store[i].size(); j++)
			{
				if (courseData_store[i][j].course_name == Remove_Course_Name)
				{
					courseData_store[i].erase(courseData_store[i].begin() + j);
					return 1;
				}
			}
			return 0;
		}
	}
	return 0;
}
int StudentDataHandler::ModifyCourse(string SID_SName , Course_name_score modify_course_name_score)
{
	for (int i = 0; i < studentData_store.size(); i++)
	{
		if (studentData_store[i].student_id == SID_SName || studentData_store[i].student_name == SID_SName)
		{
			for (int j = 0; j < courseData_store[i].size(); j++)
			{
				if (courseData_store[i][j].course_name == modify_course_name_score.course_name)
				{
					courseData_store[i][j].score = modify_course_name_score.score;
					return 1;
				}
			}
			return 0;
		}
	}
	return 0;
}

int main()
{
	StudentDataHandler StudentDatahandler;
	while (1)
	{
		string input;
		getline(cin, input);	//用getline把整行包括空白一起讀入
		if (input.compare("EXIT") == 0)
			return 0;

		//準備利用空白來切字串
		size_t found = -1;
		vector<int> foundnum;	//用foundnum array來存空白所在的位置
		foundnum.push_back(-1);
		while (1)
		{
			found = input.find(' ', found + 1);	//後面的 found + 1 表示從第(found+1)個元素開始找起
			if (found == -1)	//若沒找到str.find()會回傳-1
			{
				foundnum.push_back(input.size());
				break;
			}
			else
				foundnum.push_back(found);
		}

		vector<string> cutarr;
		for (int i = 0; i < foundnum.size() - 1; i++)
		{
			cutarr.push_back(input.substr(foundnum[i] + 1, foundnum[i + 1] - (foundnum[i] + 1)));
		}
		//for (int i = 0; i < cutarr.size(); i++)
		//	cout << cutarr[i] << endl;

		if (cutarr[0].compare("AddStudent") == 0)	//AddStudent的進入
		{
			int count = (cutarr.size() - 1) / 2;	//減去cutarr[0]="AddStudent",計算總共幾組(Name/Id)
			int boolnum = -1;
			for (int i = 0, j = 1; i < count; i++, j = j + 2)
			{
				Student_name_id addstudentdata;
				addstudentdata.student_name = cutarr[j];
				addstudentdata.student_id = cutarr[j + 1];
				boolnum = StudentDatahandler.AddStudent(addstudentdata);
				if (boolnum == 0)
					cout << "Error" << endl;
			}
		}
		else if (cutarr[0].compare("AddCourse") == 0)	//AddCourse的進入
		{

			int count = (cutarr.size()/2)-1 ;			//減去cutarr[0]="AddCourse"和cutarr[1]=studentname/sID,計算總共幾組(Course/score)
			if (count == 0)
			{
				cout << "Error" << endl;
				break;
			}
			int boolnum = -1;
			for (int i = 0, j = 2; i < count; i++, j = j + 2)
			{
				Course_name_score addcoursedata;
				addcoursedata.course_name = cutarr[j];
				addcoursedata.score = cutarr[j + 1];
				boolnum = StudentDatahandler.AddCourse(addcoursedata,cutarr[1]);
				if (boolnum == 0)
					cout << "Error" << endl;
			}
		}
		else if (cutarr[0].compare("Search") == 0)
		{
			int boolnum = -1;
			boolnum = StudentDatahandler.SearchStudent(cutarr[1]);
			if (boolnum == 0)
				cout << "Error" << endl;
		}
		else if (cutarr[0].compare("RemoveStudent") == 0)
		{
			int boolnum = -1;
			boolnum = StudentDatahandler.RemoveStudent(cutarr[1]);
			if (boolnum == 0)
				cout << "Error" << endl;
		}
		else if (cutarr[0].compare("RemoveCourse") == 0)
		{
			int boolnum = -1;
			boolnum = StudentDatahandler.RemoveCourse(cutarr[1], cutarr[2]);
			if (boolnum == 0)
				cout << "Error" << endl;
		}
		else if (cutarr[0].compare("ModifyCourse") == 0)
		{
			int count = (cutarr.size() / 2) - 1;
			for (int i = 0, j = 2; i < count; i++, j = j + 2) 
			{
				Course_name_score modify_course_name_score;
				modify_course_name_score.course_name = cutarr[j];
				modify_course_name_score.score = cutarr[j+1];
				int boolnum = -1;
				boolnum = StudentDatahandler.ModifyCourse(cutarr[1], modify_course_name_score);
				if (boolnum == 0)
					cout << "Error" << endl;
			}
		}
	}
	system("pause");
	return 0;
}
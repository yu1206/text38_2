#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 
#include <io.h>
#include <Windows.h>
#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <direct.h>
using namespace cv;
using namespace std;
extern int readDir(char *dirName, vector<string> &filesName);

int test38_1(int argc, char *argv[])
{
	string inputPath = "I:/双个车牌放在一起/危险品/danger_down";
	string outputsrc = "I:/双个车牌放在一起/危险品/newname";
	

	vector<string> v_img_;
	readDir((char*)inputPath.c_str(), v_img_);
	
	for (int i = 0; i < v_img_.size(); i++)
	{
		

		cout << v_img_[i] << endl;
		

		int npos = v_img_[i].find_last_of('/');
		int npos2 = v_img_[i].find_last_of('.');
		string name1 = v_img_[i].substr(npos + 1, npos2 - npos - 1);
		Mat img = imread(v_img_[i].c_str());
		if (img.data == NULL)
		{

			printf("图像为空!\n");
			cout << v_img_[i].c_str() << endl;
			system("pause");
		}

		char s[12];
		itoa(i, s, 10);
		string string_temp = s;

		string str1 = outputsrc + "/" + string_temp + ".jpg";
		imwrite(str1.c_str(), img);


		int width = img.cols;  int height = img.rows;

		

		fstream finRead;
		string inputPathtxt = inputPath + "/" + name1 + ".txt";
		finRead.open(inputPathtxt, ios::in);
		if (!finRead.is_open())
		{
			cout << "finRead1 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}

		string outputtxt = outputsrc + "/" + string_temp + ".txt";
		fstream finWrite;
		finWrite.open(outputtxt, ios::out);

		if (!finWrite.is_open())
		{
			cout << "finRead2 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}

		

		string line;
		while (getline(finRead, line))
		{
			 int label; float centx, centy,centw,centh;
			 stringstream str_s(line);
			 str_s >> label >> centx >> centy >> centw >> centh;
			
			 int x1, y1, x2, y2;
			 x1 = (centx - centw / 2)*width;
			 y1 = (centy - centh / 2)*height;
			 x2 = (centx + centw / 2)*width;
			 y2 = (centy + centh / 2)*height;
			finWrite << label<< " " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
			
		}
		

		finRead.close();
		finWrite.close();
		


		int jjjjjj = 90;

	}
	return 0;
}

int test38_2(int argc, char *argv[])
{
	string inputPath = "I:/双个车牌放在一起/危险品1/标记危险品";
	string outputsrc = "I:/双个车牌放在一起/危险品/chepai";


	vector<string> v_img_;
	readDir((char*)inputPath.c_str(), v_img_);

	for (int i = 0; i < v_img_.size(); i++)
	{
		
		cout << v_img_[i] << endl;

		int npos = v_img_[i].find_last_of('/');
		int npos2 = v_img_[i].find_last_of('.');
		string name1 = v_img_[i].substr(npos + 1, npos2 - npos - 1);
		Mat img = imread(v_img_[i].c_str());
		if (img.data == NULL)
		{

			printf("图像为空!\n");
			cout << v_img_[i].c_str() << endl;
			system("pause");
		}
		int width = img.cols;  int height = img.rows;
		fstream finRead;
		string inputPathtxt = inputPath + "/" + name1 + ".txt";
		finRead.open(inputPathtxt, ios::in);
		if (!finRead.is_open())
		{
			cout << "finRead1 文件数据打开错误！" << endl;
			system("pause");
			continue;
		}


		string line; int j = 0;
		while (getline(finRead, line))
		{
			
			char s[12];
			itoa(j, s, 10);
			string string_temp = s;

			/*int label; int x1, y1, x2, y2;
			stringstream str_s(line);
			str_s >> label >> x1 >> y1 >> x2 >> y2;*/

			int label; float centx, centy, centw, centh;
			stringstream str_s(line);
			str_s >> label >> centx >> centy >> centw >> centh;

			int x1, y1, x2, y2;
			x1 = (centx - centw / 2)*width;
			y1 = (centy - centh / 2)*height;
			x2 = (centx + centw / 2)*width;
			y2 = (centy + centh / 2)*height;

			if (label == 1)
			{
				int static num = 0;
				num++;
				cout <<"i="<<i<< ",num=" <<num<< endl;

				//system("pause");

				string str1 = outputsrc + "/" + name1+"-"+string_temp + ".jpg";

				Rect rt; rt.x = x1; rt.y = y1; rt.width = x2 - x1 + 1;
				rt.height = y2 - y1 + 1;

				Mat roi = img(rt);

				imwrite(str1.c_str(), roi);
			}

			j++;
		}


		finRead.close();
		



		int jjjjjj = 90;

	}
	return 0;
}

int test38_3(int argc, char *argv[])
{
	string  mappinglabels[78] = { "", "京", "沪", "津", "渝", "冀", "晋", "蒙", "辽", "吉", "黑", "苏", "浙", "皖", "闽", "赣", "鲁", "豫", "鄂", "湘", "粤", "桂",
		"琼", "川", "贵", "云", "藏", "陕", "甘", "青", "宁", "新", "学", "警", "港", "澳", "挂", "使", "领", "民", "深", "危","险","品","0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A",
		"B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

	string  mappinglabels1[75] = { "", "京", "沪", "津", "渝", "冀", "晋", "蒙", "辽", "吉", "黑", "苏", "浙", "皖", "闽", "赣", "鲁", "豫", "鄂", "湘", "粤", "桂",
		"琼", "川", "贵", "云", "藏", "陕", "甘", "青", "宁", "新", "学", "警", "港", "澳", "挂", "使", "领", "民", "深",  "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A",
		"B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
	string inputPath = "I:/双个车牌放在一起/危险品/zifu-2";
	string outputtxt= "I:/双个车牌放在一起/危险品/zifu-2/0.txt";

	fstream finWrite;
	finWrite.open(outputtxt, ios::out);

	if (!finWrite.is_open())
	{
		cout << "finRead2 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	vector<string> v_img_;
	readDir((char*)inputPath.c_str(), v_img_);

	for (int i = 0; i < v_img_.size(); i++)
	{

		cout << v_img_[i] << endl;

		int npos = v_img_[i].find_last_of('/');
		int npos2 = v_img_[i].find_last_of('.');
		string name1 = v_img_[i].substr(npos + 1, npos2 - npos - 1);
		Mat img = imread(v_img_[i].c_str());
		if (img.data == NULL)
		{

			printf("图像为空!\n");
			cout << v_img_[i].c_str() << endl;
			system("pause");
		}

		

		finWrite << v_img_[i] << " " << 41 << " " << 42 << " " <<0 << " " << 0 << " " << 0 << " " 
			<< 0 << " " << 0 << " " << 0  << endl;
		


		



		int jjjjjj = 90;

	}

	finWrite.close();

	return 0;
}

int test38_4(int argc, char *argv[])
{
	string  mappinglabels[78] = { "", "京", "沪", "津", "渝", "冀", "晋", "蒙", "辽", "吉", "黑", "苏", "浙", "皖", "闽", "赣", "鲁", "豫", "鄂", "湘", "粤", "桂",
		"琼", "川", "贵", "云", "藏", "陕", "甘", "青", "宁", "新", "学", "警", "港", "澳", "挂", "使", "领", "民", "深", "危", "险", "品", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A",
		"B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

	string  mappinglabels1[75] = { "", "京", "沪", "津", "渝", "冀", "晋", "蒙", "辽", "吉", "黑", "苏", "浙", "皖", "闽", "赣", "鲁", "豫", "鄂", "湘", "粤", "桂",
		"琼", "川", "贵", "云", "藏", "陕", "甘", "青", "宁", "新", "学", "警", "港", "澳", "挂", "使", "领", "民", "深", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A",
		"B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
	
	string inputPathtxt = "I:/lstm-字符识别-hejijia-new/0_labels_mapping-75.txt";
	string outputtxt = "I:/lstm-字符识别-hejijia-new/1_labels_mapping-78.txt";

	fstream finRead;
	
	finRead.open(inputPathtxt, ios::in);
	if (!finRead.is_open())
	{
		cout << "finRead1 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	fstream finWrite;
	finWrite.open(outputtxt, ios::out);

	if (!finWrite.is_open())
	{
		cout << "finRead2 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	
	string line;
	while (getline(finRead,line))
	{

		string strjpg; int a[8];
		stringstream str_s(line);

		str_s >> strjpg >> a[0] >> a[1] >> a[2] >> a[3] >> a[4] >> a[5] >> a[6] >> a[7];

		for (int i = 0; i < 8;i++)
		{
			if (a[i]>40)
			{
				a[i] = a[i] + 3;
			}
		}

		finWrite << strjpg << " " << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << " " << a[4] << " "
			<< a[5] << " " << a[6] << " " << a[7] << endl;







		int jjjjjj = 90;

	}

	finRead.close();
	finWrite.close();

	return 0;
}


int test38_5(int argc, char *argv[])
{
	string  mappinglabels[78] = { "", "京", "沪", "津", "渝", "冀", "晋", "蒙", "辽", "吉", "黑", "苏", "浙", "皖", "闽", "赣", "鲁", "豫", "鄂", "湘", "粤", "桂",
		"琼", "川", "贵", "云", "藏", "陕", "甘", "青", "宁", "新", "学", "警", "港", "澳", "挂", "使", "领", "民", "深", "危", "险", "品", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A",
		"B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

	string  mappinglabels1[75] = { "", "京", "沪", "津", "渝", "冀", "晋", "蒙", "辽", "吉", "黑", "苏", "浙", "皖", "闽", "赣", "鲁", "豫", "鄂", "湘", "粤", "桂",
		"琼", "川", "贵", "云", "藏", "陕", "甘", "青", "宁", "新", "学", "警", "港", "澳", "挂", "使", "领", "民", "深", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A",
		"B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
	
	
	string inputPath = "I:/双个车牌放在一起/危险品/zifu-3";
	string outputtxt = "I:/双个车牌放在一起/危险品/zifu-3/1.txt";

	fstream finWrite;
	finWrite.open(outputtxt, ios::out);

	if (!finWrite.is_open())
	{
		cout << "finRead2 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	vector<string> v_img_;
	readDir((char*)inputPath.c_str(), v_img_);

	for (int i = 0; i < v_img_.size(); i++)
	{

		cout << v_img_[i] << endl;

		int npos = v_img_[i].find_last_of('/');
		int npos2 = v_img_[i].find_last_of('.');
		string name1 = v_img_[i].substr(npos + 1, npos2 - npos - 1);
		Mat img = imread(v_img_[i].c_str());
		if (img.data == NULL)
		{

			printf("图像为空!\n");
			cout << v_img_[i].c_str() << endl;
			system("pause");
		}



		finWrite << v_img_[i] << " " << 41 << " " << 41 << " " <<41 << " " << 0 << " " << 0 << " "
			<< 0 << " " << 0 << " " << 0 << endl;







		int jjjjjj = 90;

	}

	finWrite.close();

	return 0;
}

int test38_6(int argc, char *argv[])
{
	string  mappinglabels[78] = { "", "京", "沪", "津", "渝", "冀", "晋", "蒙", "辽", "吉", "黑", "苏", "浙", "皖", "闽", "赣", "鲁", "豫", "鄂", "湘", "粤", "桂",
		"琼", "川", "贵", "云", "藏", "陕", "甘", "青", "宁", "新", "学", "警", "港", "澳", "挂", "使", "领", "民", "深", "危", "险", "品", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A",
		"B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

	string  mappinglabels1[75] = { "", "京", "沪", "津", "渝", "冀", "晋", "蒙", "辽", "吉", "黑", "苏", "浙", "皖", "闽", "赣", "鲁", "豫", "鄂", "湘", "粤", "桂",
		"琼", "川", "贵", "云", "藏", "陕", "甘", "青", "宁", "新", "学", "警", "港", "澳", "挂", "使", "领", "民", "深", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A",
		"B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

	string inputPathtxt = "I:/lstm-字符识别-hejijia-new/0_labels_mapping-75.txt";
	string outputtxt = "I:/lstm-字符识别-hejijia-new/3_labels_mapping-76.txt";

	fstream finRead;

	finRead.open(inputPathtxt, ios::in);
	if (!finRead.is_open())
	{
		cout << "finRead1 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	fstream finWrite;
	finWrite.open(outputtxt, ios::out);

	if (!finWrite.is_open())
	{
		cout << "finRead2 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}


	string line;
	while (getline(finRead, line))
	{

		string strjpg; int a[8];
		stringstream str_s(line);

		str_s >> strjpg >> a[0] >> a[1] >> a[2] >> a[3] >> a[4] >> a[5] >> a[6] >> a[7];

		for (int i = 0; i < 8; i++)
		{
			if (a[i]>40)
			{
				a[i] = a[i] + 1;
			}
		}

		finWrite << strjpg << " " << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << " " << a[4] << " "
			<< a[5] << " " << a[6] << " " << a[7] << endl;







		int jjjjjj = 90;

	}

	finRead.close();
	finWrite.close();

	return 0;
}

int test38_7(int argc, char *argv[])
{
	

	string inputPath = "I:/双个车牌放在一起/危险品1/newname";
	string outputsrc = "I:/双个车牌放在一起/危险品1/newname1";
	string outputdraw = "I:/双个车牌放在一起/危险品1/newname1draw";



	vector<string> v_img_;
	readDir((char*)inputPath.c_str(), v_img_);

	for (int i = 0; i < v_img_.size(); i++)
	{


		cout << v_img_[i] << endl;


		int npos = v_img_[i].find_last_of('/');
		int npos2 = v_img_[i].find_last_of('.');
		string name1 = v_img_[i].substr(npos + 1, npos2 - npos - 1);
		Mat img = imread(v_img_[i].c_str());
		if (img.data == NULL)
		{

			printf("图像为空!\n");
			cout << v_img_[i].c_str() << endl;
			system("pause");
		}

		
		Mat imgdraw = img.clone();
		int width = img.cols;  int height = img.rows;

		fstream finRead;
		string inputPathtxt = inputPath + "/" + name1 + ".txt";
		finRead.open(inputPathtxt, ios::in);
		if (!finRead.is_open())
		{
			cout << "finRead1 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}

		string outputtxt = outputsrc + "/" + name1 + ".txt";
		fstream finWrite;
		finWrite.open(outputtxt, ios::out);

		if (!finWrite.is_open())
		{
			cout << "finRead2 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}



		string line;
		int x1a[10], y1a[10], x2a[10], y2a[10];
		int j = 0;
		while (getline(finRead, line))
		{
			int label; int x1, y1, x2, y2;
			stringstream str_s(line);
			str_s >> label >> x1 >> y1 >> x2 >> y2;

			if (label == 3)
			{
				

				x1a[j] = x1; y1a[j] = y1; x2a[j] = x2; y2a[j] = y2;
				j++;
				
			}

			

		}

		int num = j;
		for (int k = 0; k < num;k++)
		{
			if (y1a[k]>height / 2)
			{
				string str1 = name1 + ".txt";
				finWrite << str1 << " " << 3 << " " << x1a[k] << " " << y1a[k] << " " << x2a[k] << " " << y2a[k] << endl;
				
				Point pt1, pt2;
				pt1.x = x1a[k]; pt1.y = y1a[k]; pt2.x = x2a[k]; pt2.y = y2a[k];
				rectangle(imgdraw, pt1, pt2, Scalar(0, 0, 255));
			}

			string str2 = outputdraw+"/"+name1 + ".jpg";
			imwrite(str2.c_str(), imgdraw);

			string str3 = outputsrc + "/" + name1 + ".jpg";
			imwrite(str3.c_str(), img);
		}
		

		
		finRead.close();
		finWrite.close();



		int jjjjjj = 90;

	}
	return 0;
}
int test38(int argc, char *argv[])
{
	// test38_1   将危险品重新命名;test38_2,抠出来危险品训练
	//test38_3, 做成lstm 训练格式  //test38_4, 更改字符标签
	//test38_1(argc, argv);

	//test38_2(argc, argv);

	test38_3(argc, argv);

	//test38_4(argc, argv);

	// 危险品当成一个字
	//test38_5(argc, argv);

	//  数字和英文字符加1
	//test38_6(argc, argv);

	// 危险品 抽出来 用于mtcnn训练 
	//test38_7(argc, argv);

	return 0;
}
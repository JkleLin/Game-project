#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>
using namespace std;
#define line 9
#define column 9
#define Max_destination 4

//0空 1墙 2箱子 3目的地 4人
bool PrintMap(int (*item)[column],int **seat);
bool move(int (*item)[column]);
void Copy_map(int(*map_copy)[column], int(*map_be_copied)[column]);
void win();
int desnum = 0;//当前游戏目的地个数

int main() {
	fstream map;
	int block[line][column] = { 0 };
	int block_copy[line][column] = { 0 };
	int *deseat[Max_destination];//指向目的地位置

	map.open("Maps.txt", ios::in|ios::beg);
	if (!map) {
		cout << "打开地图失败" << endl;
		exit(1);
	}
	for (int i = 0; i < line; i++)
		for (int n = 0; n < column; n++) {
			map >> block[i][n];
			block_copy[i][n] = block[i][n];
			if (block[i][n] == 3) {
				deseat[desnum] = &block[i][n];
				desnum++;
			}
		}
	map.close();
	if (desnum > Max_destination) {
		cout << "地图错误（终点数过多）";
        exit(1);
	}
	//读取地图

	PrintMap(block,deseat);

	while (1) {
		if (move(block)) {
			Copy_map(block, block_copy);
		}
		system("cls");
		if (PrintMap(block, deseat)) {
			win();
			break;
		}
	}
	_getch();
}

bool PrintMap(int (*item)[column],int **seat) {
	int i;
	int get_p_num = 0;//到达了目的地的箱子数
	for (i = 0; i < desnum; i++) {
		switch (*seat[i]) {
		case 0:*seat[i] = 3;
		case 2:get_p_num++;
		}
	}
	if (get_p_num == desnum)
		return true;

	cout << "方向键移动，R键重新开始" << endl;
	for (i = 0; i < line; i++) {
		for (int n = 0; n < column; n++) {
			switch (item[i][n]) {
			case 0: cout << "  "; break;
			case 1: cout << "■"; break;
			case 2: cout << "□"; break;
			case 3: cout << "※"; break;
			case 4: cout << "♀"; break;
			default:exit(1);
			}
		}
		cout << endl;
	}
	return false;
}

void Copy_map(int(*map_copy)[column], int(*map_be_copied)[column]) {
	for (int i = 0; i < line; i++)
		for (int n = 0; n < column; n++)
			map_copy[i][n] = map_be_copied[i][n];
}

bool move(int (*item)[column]) {
	int a;
	int manx;
	int many;
	for (int i = 0; i < line; i++) {
		for (int n = 0; n < column; n++)
			if (item[i][n] == 4) {
				manx = i; many = n; break;
			}
	}

	a = _getch();
	//上72 下80 左75 右77
	switch (a) {
	case 72:
		if (manx - 1 >= 0) {
			switch (item[manx - 1][many]) {
			case 1:break;
			case 2:if (item[manx - 2][many] == 1)
				break;
				   else
					   item[manx - 2][many] = 2;
			default:item[manx - 1][many] = 4;
				   item[manx][many] = 0;
				   break;
			}
		}
		break;
	case 80:
		if (manx + 1 < line) {
			switch (item[manx + 1][many]) {
			case 1:break;
			case 2:if (item[manx + 2][many] == 1)
				break;
				   else
					   item[manx + 2][many] = 2;
			default:item[manx + 1][many] = 4;
				item[manx][many] = 0;
				break;
			}
		}
		break;
	case 75:
		if (many - 1 >= 0) {
			switch (item[manx][many - 1]) {
			case 1:break;
			case 2:if (item[manx][many - 2] == 1)
				break;
				   else
					   item[manx][many - 2] = 2;
			default:item[manx][many - 1] = 4;
				item[manx][many] = 0;
				break;
			}
		}
		break;
	case 77:
		if (many + 1 < column) {
			switch (item[manx][many + 1]) {
			case 1:break;
			case 2:if (item[manx][many + 2] == 1)
				break;
				   else
					   item[manx][many + 2] = 2;
			default:item[manx][many + 1] = 4;
				item[manx][many] = 0;
				break;
			}
		}
		break;
	case 114:
	case 82:return true; break;
	}
	return false;
}

void win() {
	cout << "  \\       _       / " << endl;
	cout << "   \\     / \\     /  " << endl;
	cout << "    \\   /   \\   /   " << endl;
	cout << "     \\_/     \\_/    " << endl;
	cout << "       _______      " << endl;
	cout << "          |         " << endl;
	cout << "          |         " << endl;
	cout << "       ___|___      " << endl;
	cout << "        _           " << endl;
	cout << "       | \\    |     " << endl;
	cout << "       |  \\   |     " << endl;
	cout << "       |   \\  |     " << endl;
	cout << "       |    \\_|     " << endl;
}
/* ------------------------------------------------------------------|
编写一个程序，通过填充空格来解决数独问题。

一个数独的解法需遵循如下规则：

数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
空白格用 '.' 表示。



一个数独。



答案被标成红色。

提示：

给定的数独序列只包含数字 1-9 和字符 '.' 。
你可以假设给定的数独只有唯一解。
给定数独永远是 9x9 形式的。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sudoku-solver
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。|
-------------------------------------------------------------------*/

/*	递归法
*
*	执行用时：4 ms, 在所有 C++ 提交中击败了91.14%的用户
*	内存消耗：6.9 MB, 在所有 C++ 提交中击败了13.90%的用户
*/

#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};

int row[9][9] = { 0 };
int col[9][9] = { 0 };
int box[9][9] = { 0 };
//剩余没填的空的坐标
vector<pair<int, int> > space;

bool dfs(vector<vector<char>>& board, int index) {
	if (index == space.size()) {
		return true;
	}

	int nowrow = space[index].first;
	int nowcol = space[index].second;
	for (char c = '1'; c <= '9'; c++) {
		char num = c - '1';
		//判断此处可填写
		if (!row[nowrow][num] && !col[nowcol][num] && !box[(nowrow / 3) * 3 + nowcol / 3][num]) {
			//填写
			board[nowrow][nowcol] = c;
			//修改填充状态
			row[nowrow][num] = 1;
			col[nowcol][num] = 1;
			box[(nowrow / 3) * 3 + nowcol / 3][num] = 1;
			//如果可以沿着目录一直递归下去，则说明填对了，返回true
			if (dfs(board, index + 1)) {
				return true;
			}
			//不然说明填错了，回溯填充状态
			row[nowrow][num] = 0;
			col[nowcol][num] = 0;
			box[(nowrow / 3) * 3 + nowcol / 3][num] = 0;

		}
	}
	return false;
}

void solveSudoku(vector<vector<char>>& board)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			char num = board[i][j] - '1';
			if (board[i][j] == '.')
			{
				space.emplace_back(i, j);
			}
			else
			{
				row[i][num]++;
				col[j][num]++;
				box[(i / 3) * 3 + j / 3][num]++;
			}
		}
	}
	//从space[0]开始递归
	dfs(board, 0);
}


int main()
{
	vector<vector<char> > board = {
	{'5','3','.',		'.','7','.',		'.','.','.'},
	{'6','.','.',		'1','9','5',		'.','.','.'},
	{'.','9','8',		'.','.','.',		'.','6','.'},

	{'8','.','.',		'.','6','.',		'.','.','3'},
	{'4','.','.',		'8','.','3',		'.','.','1'},
	{'7','.','.',		'.','2','.',		'.','.','6'},

	{'.','6','.',		'.','.','.',		'2','8','.'},
	{'.','.','.',		'4','1','9',		'.','.','5'},
	{'.','.','.',		'.','8','.',		'.','7','9'}	
	};

	//int row[9][9] = { 0 };
	//int col[9][9] = { 0 };;
	//int box[9][9] = { 0 };;

	//for (int i = 0; i < 9; i++)
	//{
	//	for (int j = 0; j < 9; j++)
	//	{
	//		if (board[i][j] == '.')
	//		{
	//			continue;
	//		}
	//		else
	//		{
	//			row[i][board[i][j] - '1']++;
	//			col[j][board[i][j] - '1']++;
	//			box[(i / 3) * 3 + j / 3][board[i][j] - '1']++;
	//		}
	//	}
	//}

}

/**
* @file minesweeper_counting_helper.cpp
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int NROWS    = 10; /**< ���� �迭 �� ����*/
const int NCOLUMNS = 10; /**< ���� �迭 �� ����*/

/**
 * @fn                   void clearBoards(char calculateBoard[][10], char gameBoard[][10])
 * @brief                ���� �ʱ�ȭ �Լ�
 * @param calculateBoard ��� ����
 * @param gameBoard      ���� ����
 */
void clearBoards(char calculateBoard[][10], char gameBoard[][10]) {
    /*���� ��ü �ʱ�ȭ*/
    for (int i = 0; i < NROWS; i++)
        for (int j = 0; j < NCOLUMNS; j++)
            gameBoard[i][j] = calculateBoard[i][j] = '0';

    return;
}

/**
 * @fn          char indexToChar(int index)
 * @brief       0~10 ������ ���� ��, �� ���� ����ȭ
 * @param index ������ ��, �� ��
 */
char indexToChar(int index) {
    /*10 ���� ���� ������ ��� 0~9*/
    if (index < 10)
        /*10���� ���� ������ ����ȭ*/
        return index + '0';
}

/**
 * @fn    int charToIndex(char ch)
 * @biref �÷��̾ �Է��� ��ġ '0'~'9' ������ ���ڸ� ����ȭ
 * @param ch
 * @return
 */
int charToIndex(char ch) {
    /*'0'~'9'�� ���ڸ� ����ȭ*/
    if (ch <= '9')
        return ch - '0';
}

/**
 * @fn              void displayGameBoard(char gameBoard[][10])
 * @brief           ����ã�� ���� ���� ��� �Լ�
 * @param gameBoard ���� ����
 */
void displayGameBoard(char gameBoard[][10]) {
    cout << "   ";
    /*������ �� ���ٿ� �� ��ġ ���*/
    for (int i = 0; i < NCOLUMNS; i++)
        cout << indexToChar(i) << ' ';
    cout << endl << endl;

    /*������ �� ���ʿ� �� ��ġ ���*/
    for (int i = 0; i < NROWS; i++) {
        cout << indexToChar(i) << "  ";

        for (int j = 0; j < NCOLUMNS; j++)
            /*������ ���� ���� ' '(����)�� ä��*/
            cout << gameBoard[i][j] << ' ';

        /*������ �� �����ʿ� �� ��ġ ���*/
        cout << ' ' << indexToChar(i);

        cout << endl;
    }

    cout << endl << "   ";

    /*������ �� �Ʒ��ٿ� �� ��ġ ���*/
    for (int i = 0; i < NCOLUMNS; i++)
        cout << indexToChar(i) << ' ';
    cout << endl;

    return;
}

/**
 * @fn                   void displayBoard(char gameBoard[][10])
 * @brief                ����ã�� ī���� ���� ��� �Լ�
 * @param calculateBoard ��� ����
 */
void displayCountingBoard(char calculateBoard[][10]) {
    /*�ּҰ�, �ִ밪 ���ϱ�*/
    int min = 0;
    int max = 0;
    for (int i = 0; i < NROWS; i++) {
        for (int j = 0; j < NCOLUMNS; j++) {
            /*����(X) ���*/
            if (calculateBoard[i][j] == 'X') {
                continue;
            }
            /*�ִ밪�� ���*/
            if (charToIndex(calculateBoard[i][j]) >= max) {
                max = charToIndex(calculateBoard[i][j]);
            }
        }
    }

    cout << "   ";
    /*������ �� ���ٿ� �� ��ġ ���*/
    for (int i = 0; i < NCOLUMNS; i++)
        cout << indexToChar(i) << ' ';
    cout << endl << endl;

    /*������ �� ���ʿ� �� ��ġ ���*/
    for (int i = 0; i < NROWS; i++) {
        cout << indexToChar(i) << "  ";

        /*������ ���� ���� ' '(����)�� ä��*/
        for (int j = 0; j < NCOLUMNS; j++) {
            if (charToIndex(calculateBoard[i][j]) == max) {
                /*�ִ밪�̸� Font Graphic Red���� ���̶�����*/
                cout << "\033[31m" << calculateBoard[i][j] << "\033[0m" << ' ';
            }
            else {
                cout << calculateBoard[i][j] << ' ';
            }
        }

        /*������ �� �����ʿ� �� ��ġ ���*/
        cout << ' ' << indexToChar(i);

        cout << endl;
    }

    cout << endl << "   ";

    /*������ �� �Ʒ��ٿ� �� ��ġ ���*/
    for (int i = 0; i < NCOLUMNS; i++)
        cout << indexToChar(i) << ' ';
    cout << endl;

    return;
}

/**
 * @fn        bool isValid(int row, int col)
 * @brief     ���� ���ڰ� ������ �� �ִ� ��ġ���� Ȯ���ϴ� �Լ�
 * @param row ������ ��
 * @param col ������ ��
 * @return
 */
bool isValid(int row, int col) {
    /*������ ���� �� ���� �ƴϰ� ������ �ǹ� �� �Ʒ��� �ƴϸ鼭*/
    /*������ �ǿ��� �ǿ��� �� ������ �ƴϰ� ������ �ǿ����� �� �������� �ƴϸ�*/
    /*true ��ȯ*/
    return (row >= 0) && (row < NROWS) && (col >= 0) && (col < NCOLUMNS);
}

/**
 * @fn                vector<pair<int, int>> getNeighbours(int row, int col)
 * @brief             �ش� ���� ������, ��, ��������, ����, ������, ���ʾƷ�, �Ʒ�, �����ʾƷ� ��ǥ�� ��ȯ�ϴ� �Լ�
 * @param row         ������ ��
 * @param col         ������ ��
 * @return neighbours �ش� ���� ������, ��, ��������, ����, ������, ���ʾƷ�, �Ʒ�, �����ʾƷ� ��ǥ�� ����� ����
 */
vector<pair<int, int>> getNeighbours(int row, int col) {
    /*
    N.W   N   N.E
      \   |   /
       \  |  /
    W---Cell----E
        / |  \
       /  |   \
    S.W   S   S.E
    Cell --> Current Cell ( row, col )
    N    --> North        ( row-1, col )
    S    --> South        ( row+1, col )
    E    --> East         ( row, col+1 )
    W    --> West         ( row, col-1 )
    N.E  --> North-East   ( row-1, col+1 )
    N.W  --> North-West   ( row-1, col-1 )
    S.E  --> South-East   ( row+1, col+1)
    S.W  --> South-West   ( row+1, col-1 )
    */

    vector<pair<int, int>> neighbours;

    /*�ش� ���� �Ʒ���, ����*/
    for (int dx = -1; dx <= 1; dx++)
        /*�ش� ���� ���ʿ�, �����ʿ�*/
        for (int dy = -1; dy <= 1; dy++)
            /*�ش� ���� �ƴ� ���*/
            if (dx != 0 || dy != 0)
                /*�ش� ���� ���ڰ� ������ �� �ִ� ��ġ���� Ȯ���ϴ� �Լ�*/
                /*�ش� ���� ���ڰ� ������ �� �ִ� ��ġ�̸�*/
                if (isValid(row + dx, col + dy))
                    /*neighbours ���Ϳ� �ش� ���� ������, ��, ��������, ����, ������, ���ʾƷ�, �Ʒ�, �����ʾƷ� ��ǥ ����*/
                    neighbours.push_back(make_pair(row + dx, col + dy));

    return neighbours;
}

/**
 * @fn                   void increaseAdjacentCount(char calculateBoard[][10], int row, int col)
 * @brief                �ش� ���� ������, ��, ��������, ����, ������, ���ʾƷ�, �Ʒ�, �����ʾƷ� ��ǥ�� ���� ī��Ʈ�� 1�� ���ϴ� �Լ�
 * @param calculateBoard ��� ����
 * @param row            ���� ��
 * @param col            ���� ��
 */
void increaseAdjacentCount(char calculateBoard[][10], int row, int col) {
    /*�ش� ���� ������, ��, ��������, ����, ������, ���ʾƷ�, �Ʒ�, �����ʾƷ� ��ǥ�� ��ȯ�ϴ� �Լ�*/
    vector<pair<int, int>> neighbours = getNeighbours(row, col);

    for (int i = 0; i < neighbours.size(); i++) {
        /*������ ���� ����(X)�� ��� ī��Ʈ�� ������Ű�� ����*/
        if (calculateBoard[neighbours[i].first][neighbours[i].second] == 'X') {
            continue;
        }
        /*������ ���� ī��Ʈ ����*/
        calculateBoard[neighbours[i].first][neighbours[i].second] =
            indexToChar((charToIndex(calculateBoard[neighbours[i].first][neighbours[i].second]) + 1));
    }
}

/**
 * @fn                   void decreaseAdjacentCount(char calculateBoard[][10], int row, int col)
 * @brief                �ش� ���� ������, ��, ��������, ����, ������, ���ʾƷ�, �Ʒ�, �����ʾƷ� ��ǥ�� ���� ī��Ʈ�� 1�� ���� �Լ�
 * @param calculateBoard ��� ����
 * @param row            ������ ��
 * @param col            ������ ��
 */
void decreaseAdjacentCount(char calculateBoard[][10], int row, int col) {
    /*�ش� ���� ������, ��, ��������, ����, ������, ���ʾƷ�, �Ʒ�, �����ʾƷ� ��ǥ�� ��ȯ�ϴ� �Լ�*/
    vector<pair<int, int>> neighbours = getNeighbours(row, col);

    for (int i = 0; i < neighbours.size(); i++) {
        calculateBoard[neighbours[i].first][neighbours[i].second] =
            indexToChar((charToIndex(calculateBoard[neighbours[i].first][neighbours[i].second]) - 1));
        if (calculateBoard[neighbours[i].first][neighbours[i].second] == '/') {
            calculateBoard[neighbours[i].first][neighbours[i].second] = '0';
        }
    }
}

/**
 * @fn    void playMinesweeperHelper()
 * @brief ����ã�� ī���� ���� �����Լ�
 *
 */
void playMinesweeperHelper() {
    char calculateBoard[10][10], gameBoard[10][10];
    
    /*���� Ȯ�� �ο� ����*/
    bool reset = false;

    /*���� �ʱ�ȭ �Լ�*/
    clearBoards(calculateBoard, gameBoard);

    while (!reset)
    {
        cout << "Game Board" << endl;
        /*����ã�� ���� ��� �Լ�*/
        displayGameBoard(gameBoard);

        cout << endl;

        cout << "Counting Board" << endl;
        displayCountingBoard(calculateBoard);

        /*�÷��̾�� ���� ������ �� ��ġ�� �� �Է� �ޱ�*/
        char x, y, z;

        cout << endl;
        cout << "If you want Reset just type (r r r)" << endl;
        cout << "Enter your location, (row, column, number/blocked(x) ex)5 3 5) -> ";
        cin >> x >> y >> z;
        cout << endl;

        int row = charToIndex(x); /*�÷��̾�κ��� �Է� ���� �� ��ġ*/
        int col = charToIndex(y); /*�÷��̾�κ��� �Է� ���� �� ��ġ*/

        /*�÷��̾ �Է��� ���� ������ ���*/
        if (charToIndex(z) >= 0 && charToIndex(z) <= 9) {
            gameBoard[row][col] = z;
            increaseAdjacentCount(calculateBoard, row, col);
        }
        /*�÷��̾ �Է��� ���� ���� ���*/
        else if (z == 'x') {
            gameBoard[row][col] = 'X';
            calculateBoard[row][col] = 'X';
        }
        /*�÷��̾ ������ ���� ���*/
        else if (x == 'r' && y == 'r' && z == 'r') {
            reset = true;
        }
    }
}

int main()
{
    while (true)
    {
        /*����ã�� ī���� ���� �����Լ�*/
        playMinesweeperHelper();
    }

    return 0;
}
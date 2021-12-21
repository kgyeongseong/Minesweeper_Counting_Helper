/**
* @file minesweeper_counting_helper.cpp
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int NROWS    = 10; /**< 보드 배열 행 갯수*/
const int NCOLUMNS = 10; /**< 보드 배열 열 갯수*/

/**
 * @fn                   void clearBoards(char calculateBoard[][10], char gameBoard[][10])
 * @brief                보드 초기화 함수
 * @param calculateBoard 계산 보드
 * @param gameBoard      게임 보드
 */
void clearBoards(char calculateBoard[][10], char gameBoard[][10]) {
    /*보드 전체 초기화*/
    for (int i = 0; i < NROWS; i++)
        for (int j = 0; j < NCOLUMNS; j++)
            gameBoard[i][j] = calculateBoard[i][j] = '0';

    return;
}

/**
 * @fn          char indexToChar(int index)
 * @brief       0~10 까지의 보드 행, 열 수를 문자화
 * @param index 보드의 행, 열 수
 */
char indexToChar(int index) {
    /*10 보다 작은 정수인 경우 0~9*/
    if (index < 10)
        /*10보다 작은 정수를 문자화*/
        return index + '0';
}

/**
 * @fn    int charToIndex(char ch)
 * @biref 플레이어가 입력한 위치 '0'~'9' 까지의 문자를 정수화
 * @param ch
 * @return
 */
int charToIndex(char ch) {
    /*'0'~'9'의 문자를 정수화*/
    if (ch <= '9')
        return ch - '0';
}

/**
 * @fn              void displayGameBoard(char gameBoard[][10])
 * @brief           지뢰찾기 게임 보드 출력 함수
 * @param gameBoard 게임 보드
 */
void displayGameBoard(char gameBoard[][10]) {
    cout << "   ";
    /*보드의 맨 윗줄에 열 위치 출력*/
    for (int i = 0; i < NCOLUMNS; i++)
        cout << indexToChar(i) << ' ';
    cout << endl << endl;

    /*보드의 맨 왼쪽에 행 위치 출력*/
    for (int i = 0; i < NROWS; i++) {
        cout << indexToChar(i) << "  ";

        for (int j = 0; j < NCOLUMNS; j++)
            /*보드의 열의 값과 ' '(공백)을 채움*/
            cout << gameBoard[i][j] << ' ';

        /*보드의 맨 오른쪽에 행 위치 출력*/
        cout << ' ' << indexToChar(i);

        cout << endl;
    }

    cout << endl << "   ";

    /*보드의 맨 아랫줄에 열 위치 출력*/
    for (int i = 0; i < NCOLUMNS; i++)
        cout << indexToChar(i) << ' ';
    cout << endl;

    return;
}

/**
 * @fn                   void displayBoard(char gameBoard[][10])
 * @brief                지뢰찾기 카운팅 보드 출력 함수
 * @param calculateBoard 계산 보드
 */
void displayCountingBoard(char calculateBoard[][10]) {
    /*최소값, 최대값 구하기*/
    int min = 0;
    int max = 0;
    for (int i = 0; i < NROWS; i++) {
        for (int j = 0; j < NCOLUMNS; j++) {
            /*막힌(X) 경우*/
            if (calculateBoard[i][j] == 'X') {
                continue;
            }
            /*최대값인 경우*/
            if (charToIndex(calculateBoard[i][j]) >= max) {
                max = charToIndex(calculateBoard[i][j]);
            }
        }
    }

    cout << "   ";
    /*보드의 맨 윗줄에 열 위치 출력*/
    for (int i = 0; i < NCOLUMNS; i++)
        cout << indexToChar(i) << ' ';
    cout << endl << endl;

    /*보드의 맨 왼쪽에 행 위치 출력*/
    for (int i = 0; i < NROWS; i++) {
        cout << indexToChar(i) << "  ";

        /*보드의 열의 값과 ' '(공백)을 채움*/
        for (int j = 0; j < NCOLUMNS; j++) {
            if (charToIndex(calculateBoard[i][j]) == max) {
                /*최대값이면 Font Graphic Red으로 하이라이팅*/
                cout << "\033[31m" << calculateBoard[i][j] << "\033[0m" << ' ';
            }
            else {
                cout << calculateBoard[i][j] << ' ';
            }
        }

        /*보드의 맨 오른쪽에 행 위치 출력*/
        cout << ' ' << indexToChar(i);

        cout << endl;
    }

    cout << endl << "   ";

    /*보드의 맨 아랫줄에 열 위치 출력*/
    for (int i = 0; i < NCOLUMNS; i++)
        cout << indexToChar(i) << ' ';
    cout << endl;

    return;
}

/**
 * @fn        bool isValid(int row, int col)
 * @brief     셀에 지뢰가 존재할 수 있는 위치인지 확인하는 함수
 * @param row 보드의 행
 * @param col 보드의 열
 * @return
 */
bool isValid(int row, int col) {
    /*보드의 맨위 행 위가 아니고 보드의 맨밑 행 아래가 아니면서*/
    /*보드의 맨왼쪽 맨왼쪽 열 왼쪽이 아니고 보드의 맨오른쪽 열 오른쪽이 아니면*/
    /*true 반환*/
    return (row >= 0) && (row < NROWS) && (col >= 0) && (col < NCOLUMNS);
}

/**
 * @fn                vector<pair<int, int>> getNeighbours(int row, int col)
 * @brief             해당 셀의 왼쪽위, 위, 오른쪽위, 왼쪽, 오른쪽, 왼쪽아래, 아래, 오른쪽아래 좌표를 반환하는 함수
 * @param row         보드의 행
 * @param col         보드의 열
 * @return neighbours 해당 셀의 왼쪽위, 위, 오른쪽위, 왼쪽, 오른쪽, 왼쪽아래, 아래, 오른쪽아래 좌표가 저장된 벡터
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

    /*해당 셀의 아래행, 위행*/
    for (int dx = -1; dx <= 1; dx++)
        /*해당 셀의 왼쪽열, 오른쪽열*/
        for (int dy = -1; dy <= 1; dy++)
            /*해당 셀이 아닌 경우*/
            if (dx != 0 || dy != 0)
                /*해당 셀에 지뢰가 존재할 수 있는 위치인지 확인하는 함수*/
                /*해당 셀이 지뢰가 존재할 수 있는 위치이면*/
                if (isValid(row + dx, col + dy))
                    /*neighbours 벡터에 해당 셀의 왼쪽위, 위, 오른쪽위, 왼쪽, 오른쪽, 왼쪽아래, 아래, 오른쪽아래 좌표 저장*/
                    neighbours.push_back(make_pair(row + dx, col + dy));

    return neighbours;
}

/**
 * @fn                   void increaseAdjacentCount(char calculateBoard[][10], int row, int col)
 * @brief                해당 셀의 왼쪽위, 위, 오른쪽위, 왼쪽, 오른쪽, 왼쪽아래, 아래, 오른쪽아래 좌표에 각각 카운트를 1씩 더하는 함수
 * @param calculateBoard 계산 보드
 * @param row            셀의 행
 * @param col            셀의 열
 */
void increaseAdjacentCount(char calculateBoard[][10], int row, int col) {
    /*해당 셀의 왼쪽위, 위, 오른쪽위, 왼쪽, 오른쪽, 왼쪽아래, 아래, 오른쪽아래 좌표를 반환하는 함수*/
    vector<pair<int, int>> neighbours = getNeighbours(row, col);

    for (int i = 0; i < neighbours.size(); i++) {
        /*인접한 셀이 막힌(X)인 경우 카운트를 증가시키지 않음*/
        if (calculateBoard[neighbours[i].first][neighbours[i].second] == 'X') {
            continue;
        }
        /*인접한 셀의 카운트 증가*/
        calculateBoard[neighbours[i].first][neighbours[i].second] =
            indexToChar((charToIndex(calculateBoard[neighbours[i].first][neighbours[i].second]) + 1));
    }
}

/**
 * @fn                   void decreaseAdjacentCount(char calculateBoard[][10], int row, int col)
 * @brief                해당 셀의 왼쪽위, 위, 오른쪽위, 왼쪽, 오른쪽, 왼쪽아래, 아래, 오른쪽아래 좌표에 각각 카운트를 1씩 빼는 함수
 * @param calculateBoard 계산 보드
 * @param row            보드의 행
 * @param col            보드의 열
 */
void decreaseAdjacentCount(char calculateBoard[][10], int row, int col) {
    /*해당 셀의 왼쪽위, 위, 오른쪽위, 왼쪽, 오른쪽, 왼쪽아래, 아래, 오른쪽아래 좌표를 반환하는 함수*/
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
 * @brief 지뢰찾기 카운팅 헬퍼 메인함수
 *
 */
void playMinesweeperHelper() {
    char calculateBoard[10][10], gameBoard[10][10];
    
    /*리셋 확인 부울 변수*/
    bool reset = false;

    /*보드 초기화 함수*/
    clearBoards(calculateBoard, gameBoard);

    while (!reset)
    {
        cout << "Game Board" << endl;
        /*지뢰찾기 보드 출력 함수*/
        displayGameBoard(gameBoard);

        cout << endl;

        cout << "Counting Board" << endl;
        displayCountingBoard(calculateBoard);

        /*플레이어로 부터 보드의 셀 위치와 값 입력 받기*/
        char x, y, z;

        cout << endl;
        cout << "If you want Reset just type (r r r)" << endl;
        cout << "Enter your location, (row, column, number/blocked(x) ex)5 3 5) -> ";
        cin >> x >> y >> z;
        cout << endl;

        int row = charToIndex(x); /*플레이어로부터 입력 받은 행 위치*/
        int col = charToIndex(y); /*플레이어로부터 입력 받은 열 위치*/

        /*플레이어가 입력한 셀이 숫자인 경우*/
        if (charToIndex(z) >= 0 && charToIndex(z) <= 9) {
            gameBoard[row][col] = z;
            increaseAdjacentCount(calculateBoard, row, col);
        }
        /*플레이어가 입력한 셀이 막힌 경우*/
        else if (z == 'x') {
            gameBoard[row][col] = 'X';
            calculateBoard[row][col] = 'X';
        }
        /*플레이어가 리셋을 원한 경우*/
        else if (x == 'r' && y == 'r' && z == 'r') {
            reset = true;
        }
    }
}

int main()
{
    while (true)
    {
        /*지뢰찾기 카운팅 헬퍼 메인함수*/
        playMinesweeperHelper();
    }

    return 0;
}
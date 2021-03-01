/* � �������� ��������� ����� �������� ������ ������ �� ����� 500
��������, ����� � ������� ��������� ������������ ��������.
���� ������� ������� ���� ����� ����� � ��������� �� 32 �� 127.
�������������, ��� � ������ ������ �������� �� ����� ���� ����. ���������� �����
�� ����������� 1000.
� ������ ������ �������� ��� ������� ���������� ����� �� ��������� ������ �������
�����. */

#include <fstream>

using std::ios_base,
      std::string,
      std::ifstream,
      std::ofstream,
      std::string,
      std::getline;

int main()
{
    ifstream cin ("in.txt");
    ofstream cout ("out.txt");

    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    string temp;
    char lastSymbolOfFirstWord;
    int counter = 0;
    while (!cin.eof())
    {
        getline(cin, temp);
        counter = 0;
        while (temp[counter] == ' ' && counter < temp.size())
        {
            counter++;
        }

        while (temp[counter + 1] != ' ' && counter < temp.size())
        {
            counter ++;
        }

        lastSymbolOfFirstWord = temp[counter];
        counter = temp.size() - 1;

        while (temp[counter] == ' ' && counter >= 0)
        {
            counter --;
        }

        while (temp[counter] != ' ' && counter >= 0)
        {
            temp[counter] = lastSymbolOfFirstWord;
            counter --;
        }

        cout<<temp;
        if (!cin.eof())
        {
            cout<<"\n";
        }
    }

    return 0;
}

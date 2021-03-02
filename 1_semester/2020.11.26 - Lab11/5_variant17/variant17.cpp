/* ¬ непустом текстовом файле записаны строки длиной не более 500
символов, слова в которых разделены единственным пробелом.
 оды каждого символа этих строк лежат в интервале от 32 до 127.
√арантируетс€, что в каждой строке записано не менее двух слов.  оличество строк
не превосходит 1000.
¬ каждой строке заменить все символы последнего слова на последний символ первого
слова. */

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

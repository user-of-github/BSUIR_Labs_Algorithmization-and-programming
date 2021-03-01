#pragma comment(linker, "/STACK:16777216")

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::ios_base;
using std::vector;


vector<unsigned int> graph [200000];
bool visited [200000];

unsigned int answer [200000];
unsigned int answerIndex = 0;

void DFS (const unsigned int &index);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    unsigned int numberOfNodes;
    cin>>numberOfNodes;

    unsigned int node1, node2;

    for (unsigned int counter = 1; counter < numberOfNodes; counter ++)
    {
        cin>>node1>>node2;
        graph[node1 - 1].push_back(node2 - 1);
        graph[node2 - 1].push_back(node1 - 1);
    }

    DFS(0);

    for (unsigned int counter = 0; counter < answerIndex; counter ++)
        cout<<answer[counter]<<(counter != (numberOfNodes * 2 - 2) ? " " : "");

    return 0;
}

void DFS (const unsigned int &index)
{
    visited [index] = true;
    if (answerIndex > 0)
    {
        if (answer[answerIndex - 1] != (index + 1))
        {
            answer[answerIndex] = (index + 1);
            answerIndex ++;
        }
    }
    else
    {
        answer[answerIndex] = (index + 1);
        answerIndex++;
    }

    for (unsigned int counter = 0; counter < graph[index].size(); counter ++)
        if (visited[graph[index][counter]] == false)
        {
            DFS(graph[index][counter]);

            if (answerIndex > 0)
            {
                if (answer[answerIndex - 1] != (index + 1))
                {
                    answer[answerIndex] = (index + 1);
                    answerIndex ++;
                }
            }
            else
            {
                answer[answerIndex] = (index + 1);
                answerIndex++;
            }
        }

    return;
}

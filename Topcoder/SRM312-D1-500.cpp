#include <bits/stdc++.h>
/**
Solution:
1. I want to condensate the whole graph.
Then, the cost of condensated vertex is minimum of all vertexes in it.
2. After that, I need to find such vertexes that if I won't get any of them,
then answer is invalid.
Obviously, those vertexes are roots of resulting forest.
3. To make answer more optimal,
I want to write down all remaining costs of vertexes in uncondensated graph.
After that, I can use greedy approach to make cost minimum
.
Time complexity: O(n ^ 2).
**/
typedef long double ld;
using namespace std;
const int N = 50;
vector<int> g[N];
vector<int> rev[N];
int n;

bool vis[N];
int color[N];
int curColor = -1;
stack<int> l;

int price[N];
vector <int> costsClone;
void kosaraju(int cur, bool todo) {
 	   if (todo) {
           color[cur] = curColor;
           price[curColor] = min(price[curColor], costsClone[cur]);
           for (int i : rev[cur])
               if (color[i] == -1)
                   kosaraju(i, 1);
       } else {
           vis[cur] = 1;
           for (int i : g[cur])
               if (!vis[i])
               	   kosaraju(i, 0);
           l.push(cur);
       }    
}

struct AntarcticaPolice {
  	  double minAverageCost(vector <int> costs, vector <string> roads) {
          costsClone = costs;
      	  n = roads.size();
          for (int i = 0; i < n; i++)
          	  for (int j = 0; j < n; j++)   
                  if (roads[i][j] == 'Y') {
              		  g[i].push_back(j);
              		  rev[j].push_back(i);
              	  }
          for (int i = 0; i < n; i++)
              color[i] = -1, vis[i] = 0, price[i] = 100000;
          
          for (int i = 0; i < n; i++)
              if (!vis[i])
              	  kosaraju(i, 0);
          
          while (!l.empty()) {
              int d = l.top();
              l.pop();
              if (color[d] == -1) {
               	  curColor++;
                  kosaraju(d, 1);
              }
          }
          curColor++;
          
     	  int p = 0;
          int q = 0;
          
          bool roots[curColor];
          for (int i = 0; i < curColor; i++)
              roots[i] = 1;
          for (int i = 0; i < n; i++)
              for (int j : g[i])
              	  if (color[i] != color[j])
                  	  roots[color[j]] = 0;
              
          vector<int> pos;
          for (int i = 0; i < curColor; i++)
              if (roots[i]) {
              	  p += price[i];
                  q++;
              }
          
          bool found[curColor];
          for (int i = 0; i < curColor; i++)
              found[i] = 0;
          
          
          for (int i = 0; i < n; i++)
              if (!roots[color[i]] || price[color[i]] != costsClone[i] || found[color[i]])
                  pos.push_back(costsClone[i]);
              else
              	  found[color[i]] = 1;
          
          sort(pos.begin(), pos.end());
          for (unsigned int i = 0; i < pos.size(); i++)
              if (p > pos[i] * q)
                  p += pos[i], q++;
          
          ld ans = ld(p) / ld(q);
          return ans;
      }
};
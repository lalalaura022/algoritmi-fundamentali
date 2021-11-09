#include <bits/stdc++.h>

using namespace std;

ifstream f("ctc.in");
ofstream g("ctc.out");

class graf
{
    int nr_noduri, nr_muchii, orientat;

    vector<vector<int>> lista_muchii;
    vector<vector<int>>  lista_muchii_transpusa;
    vector<vector<int>> CTC;
    vector<int> havel;

    void DFSx(int nod, vector<int>&v);
    void DFS_TR(int nod,vector<int> &vizitat, int nr);
    void DFS_CTC(int nod, vector<int> &vizitat, stack<int> &st);

public:

    graf();

    graf(int nr_noduri, int nr_muchii, int orientat);

    ~graf() {}

    void BFS(int start);

    void DFS(int start);



    void CTCC();

    void dfs_mic(int x, vector<bool> &vizitat, stack<int>&stiva);
    void TOPO();



    void HH();

};

graf::graf()
{
    nr_noduri = 0;
    nr_muchii = 0;
    orientat = 0;
}

graf::graf(int nr_noduri, int nr_muchii, int orientat)
{
    if(orientat < 2)
    {int i = 0, nod1, nod2;

    lista_muchii.resize(nr_noduri+1);

    this->nr_noduri = nr_noduri;
    this->nr_muchii = nr_muchii;
    this->orientat = orientat;

    while(i < nr_muchii)
    {
        f>>nod1>>nod2;
        if(orientat)
            lista_muchii[nod1].push_back(nod2);
        else
        {
            lista_muchii[nod1].push_back(nod2);
            lista_muchii[nod2].push_back(nod1);
        }
        i++;
    }
    }
    else if(orientat == 2)
    {
        int x;
        havel.clear();
        while(f >> x)
            havel.push_back(x);
    }
    else
    {
        lista_muchii.clear();
        CTC.clear();
        lista_muchii.resize(nr_noduri+1);
        int i, x, y;
        for(i = 1; i <= nr_muchii; i++)
        {
            f>>x>>y;
            lista_muchii[x].push_back(y);
            lista_muchii_transpusa[y].push_back(x);
        }
    }
}

///----------------------------------------------------------------------------------bfs
void graf::BFS(int inceput)
{
    int i = 0, nod_curent;

    queue<int> q;

    vector<int>vizitat;
    vector<int>distanta;

    q.push(inceput);

    do
    {
        vizitat.push_back(0);
        distanta.push_back(-1);
        i++;

    }
    while(i <= nr_noduri);

    vizitat[inceput] = 1;
    distanta[inceput] = 0;

    while(!q.empty())
    {
        nod_curent = q.front();
        q.pop();
        for (auto j = lista_muchii[nod_curent].begin(); j != lista_muchii[nod_curent].end(); j++)
            if(!vizitat[*j])
            {
                vizitat[*j] = 1;
                q.push(*j);
                distanta[*j] = distanta[nod_curent] + 1;
            }
    }
    int marime = distanta.size();
    for(i = 1; i < marime; i++)
        g<<distanta[i]<<" ";
}
///----------------------------------------------------------------------------------DFS

void graf::DFSx(int start, vector<int> &vizitat)
{
    vizitat[start] = 1;
    auto jos = lista_muchii[start].begin();
    auto sus = lista_muchii[start].end();
    auto j = jos;
    while(j != sus)
    {
        if(vizitat[*j] == 0)
            DFSx(*j, vizitat);
        j++;
    }
}

void graf::DFS(int start)
{

    int i = 0, nr_componente_conexe = 0,  marime;

    vector<int> vizitat;
    do
    {
        vizitat.push_back(0);
        i++;

    }
    while(i <= nr_noduri);

    marime = vizitat.size();

    for(i = 1; i < marime; i++)
        if(vizitat[i] == 0)
        {
            DFSx(i,vizitat);
            nr_componente_conexe++;
        }
    g<<nr_componente_conexe;
}
///----------------------------------------------------------------------------------HH

void graf::HH()
{
    int i, ok = 1;
    do{
        sort(havel.begin(), havel.end(),greater<int>());

        if(havel[0] == 0)
            break;

        int x = havel[0];
        havel.erase(havel.begin());

        if(x > havel.size())
            ok = 0;

        for(i = 0; i < x && ok == 1; i++)
        {
            havel[i]--;
            if(havel[i] < 0)
                ok  = 0;
        }

    }while(ok);
    if(ok == 0)
        g<<"NU";
    else
        g<<"DA";
}



///------------------------------------------------------------------------------TOPOLOGICA
void graf::dfs_mic(int x, vector<bool>&vizitat, stack<int> &stiva)
{
   vizitat[x] = 1;
   int marime = lista_muchii[x].size(), i = 0;
   while(i < marime)
   {
       if(vizitat[lista_muchii[x][i]] == 0)
        dfs_mic(lista_muchii[x][i], vizitat, stiva);
       i++;
   }
   stiva.push(x);

}

void graf::TOPO()
{
    stack <int> stiva;
    vector<bool> vizitat;
    int i = 0;

    do{
        vizitat.push_back(0);
        i++;
    }while(i <= nr_noduri + 1);

    for(i = 1; i <= nr_noduri; i++)
        if(vizitat[i] == 0)
            dfs_mic(i, vizitat, stiva);
    while(stiva.empty() == 0)
    {
        g<<stiva.top()<<" ";
        stiva.pop();
    }
}

///------------------------------------------------------------------------CTC

/*void graf::DFS_CTC(int nod, vector<int>&vizitat, stack<int> &st)
{
    int i = 0, urm;
    vizitat[nod] = 1;
    int marime;
    marime = lista_muchii[nod].size();
    for(i = 0; i < marime; i++)
    {
        urm = lista_muchii[nod][i];
        if(!vizitat[urm])
            DFS_CTC(urm, vizitat, st);
    }
    st.push(nod);
}

void graf::DFS_TR(int nod, vector<int> &vizitat, int nr)
{
    int i, urm;
    vizitat[nod] = 2;
    CTC[nr].push_back(nod);
    int marime = lista_muchii_transpusa[nod].size();
    for(i = 0; i < marime; i++)
        {urm = lista_muchii_transpusa[nod][i];

    if(vizitat[urm] == 1)
        DFS_TR(urm, vizitat, nr);
}
}

void graf::CTCC()
{
    int i = 0,nod, nr = 0;
    stack<int> st;
    while(!st.empty())
        st.pop();
    vector<int> vizitat;
    do
    {
        vizitat.push_back(0);
        i++;
    }
    while(i <= nr_noduri);

    for(i = 1; i <= nr_noduri; i++)
        if(vizitat[i] == 0)
            DFS_CTC(i,vizitat, st);
    while(!st.empty())
    {
        int nod = st.top();
        if(vizitat[nod] == 1)
        {
            nr++;
            DFS_TR(nod, vizitat, nr);
        }
        st.pop();
    }
    g<<nr<<"\n";
    for(i = 1; i <= nr; i++)
        for(int j = 0; j < CTC[i].size(); j++)
            g<<CTC[i][j]<<" ";
        g<<"\n";

}
*/

int main()
{
    int n, m, s;
    f>>n>>m;
    //------------------|
    //graf test(n,m,0); |
    //test.DFS(1);      |DFS
    //------------------|
    //------------------|
    //graf test(n,m,1); |
    //test.TOPO();      |TOPO
    //------------------|
    //------------------|
    //graf test(0,0,2); |HH
    //test.HH();        |
    //------------------|
    //graf test(n, m, 3);
    //test.CTCC();
    return 0;
}

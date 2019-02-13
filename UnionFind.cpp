class DisjointSet{
  public:
    vector<int> rank, p;

    DisjointSet(){}
    DisjointSet(int size){
        rank.resize(size, 0);
        p.resize(size, 0);
        for(int i = 0; i < size; i++) makeSet(i);
    }

    void makeSet(int x){
        p[x] = x;
        rank[x] = 0;
    }

    bool same(int x, int y){
        return findSet(x) == findSet(y);
    }
    
    void unite(int x, int y){
        link(findSet(x), findSet(y));
    }

    void link(int x, int y){
        if(rank[x] > rank[y]){
            p[y] = x;
        }else{
            p[x] = y;
            if(rank[x] == rank[y]){
                rank[y]++;
            }
        }
    }

    int findSet(int x){
        if(x != p[x]){
            // path compression
            p[x] = findSet(p[x]);
        }
        return p[x];
    }
};

// https://qiita.com/drken/items/cce6fc5c579051e64fab
struct WeightedUnionFind{
    vector<int> par;
    vector<int> rank;
    vector<int> diff;

    WeightedUnionFind(int n){
        init(n);
    }

    void init(int n){
        par.resize(n); rank.resize(n, 0); diff.resize(n, 0);
        for(int i = 0; i < n; i++)  par[i] = i;
    }

    int root(int x){
        if(par[x] == x){
            return x;
        }else{
            int r = root(par[x]);
            diff[x] += diff[par[x]];
            return par[x] = r;
        }
    }

    // 単ノードの重み取得
    int weight(int x){
        root(x);
        return diff[x];
    }

    int dif(int x, int y){
        return weight(y) - weight(x);
    }

    bool isSame(int x, int y){
        return root(x) == root(y);
    }

    // weight(y) - weight(x) = w となるように merge
    bool merge(int x, int y, int w){
        // x が y の親になることを考えると、更新の起点はdiff[y]で、
        // diff[y] を w + weight(x) - weight(y) にすればよい
        // 感覚としては、新しいdiff[y]を a と置いたときに、
        // a = w - weight(y) - (-weight[x]) とするイメージが強い
        w += weight(x); w -= weight(y);

        x = root(x); y = root(y);
        if(x == y)  return false;
        if(rank[x] < rank[y])   swap(x, y), w = -w;
        if(rank[x] == rank[y])  rank[x]++;
        par[y] = x;
        diff[y] = w;
        return true;
    }
};
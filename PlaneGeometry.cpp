// code by face4
// pointを位置ベクトルとしてみたときの外積を求めたい場面がちょこちょこあるので,
// 何かしら実装した方が良いかもしれない.

#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

// 度->ラジアンの変換
#define DEGtoRAD(X) (X*PI)/180.0
// 円周率
const double PI = 2 * acos(0.0);
// 許容誤差.問題によって変える
const double EPS = 1e-9;

struct point{
    double x, y;
    point(){ x = y = 0.0;}
    point(double _x, double _y) : x(_x), y(_y) {}

    // 不等号のオーバーロード.x座標,y座標で昇順ソート
    bool operator < (const point other) const{
        if(fabs(x - other.x) > EPS)
            return x < other.x;
        else
            return y < other.y;
    }

    // 等号のオーバーロード.
    bool operator == (const point other) const{
        return fabs(x - other.x) < EPS &&
                fabs(y - other.y) < EPS;
    }
};

// 2つのpoint間の距離 std::hypotenuse(斜辺)を利用
double dist(point p1, point p2){
    return hypot(p1.x - p2.x, p1.y - p2.y);
}

// pointの回転(原点中心).degreeは度数
point rotate(point p, double theta){
    double rad = DEGtoRAD(theta);
    return point(p.x * cos(rad) - p.y * sin(rad),
                 p.x * sin(rad) + p.y * cos(rad));
}

/* -------------------------------------------------- */

// 直線 ax+by+c = 0
struct line{
    double a, b, c;
};

// 2つのpointをlineに変換
void pointsToLine(point p1, point p2, line &l){
    // 2つのpointが成すlineがy軸に平行な場合
    if(fabs(p1.x - p2.x) < EPS){
        l.a = 1.0, l.b = 0.0, l.c = -p1.x;
    }else{
        l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
        l.b = 1.0;
        l.c = -(double)(l.a * p1.x) - p1.y;
    }
}

// 2つのlineの平行判定
bool areParallel(line l1, line l2){
    return fabs(l1.a - l2.a) < EPS && fabs(l2.a - l2.b) < EPS;
}

// 2つのlineの一致判定
bool areSame(line l1, line l2){
    return areParallel(l1, l2) && fabs(l1.c - l2.c) < EPS;
}

// 2つのlineの交差判定(未確認)
bool areIntersect(line l1, line l2, point &p){
    if(areParallel(l1, l2)) return false;

    p.x = (l2.b * l1.c - l1.b * l2.c) / 
          (l2.a * l1.b - l1.a * l2.b);

    // l1.bが0(EPS未満)の場合,l1はy軸に平行
    if(fabs(l1.b) < EPS){
        p.y = -(l1.a * p.x + l1.c);
    }else{
        p.y = -(l2.a * p.x + l2.c);
    }

    return true;
}

/* -------------------------------------------------- */

// ベクトル
struct vec{
    double x, y;
    vec(double _x, double _y) : x(_x), y(_y) {}
};

// 2つのpoint a,b をvec a->b に変換
vec toVec(point a, point b){
    return vec(b.x - a.x, b.y - a.y);
}

// vecの定数倍を定義
vec scale(vec v, double s){
    return vec(v.x * s, v.y * s);
}

// pointとvecの和
point translate(point p, vec v){
    return point(p.x + v.x, p.y + v.y);
}

// vecの内積
double dot(vec v1, vec v2){
    return v1.x * v2.x + v1.y * v2.y;
}

// vecの2ノルムの2乗
double norm_sq(vec v){
    return v.x * v.x + v.y * v.y;
}

// point p と point a,bが成す直線との距離
// point cにはpをabに射影したpointが渡される
// c = a + u * ab(未確認)
double distToLine(point p, point a, point b, point &c){
    vec ap = toVec(a, p);
    vec ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    c = translate(a, scale(ab, u));
    return dist(p, c);
}

// point p と point a,bが成す線分との距離
// distToLineに場合分けを加える
// point cにはpoint pに最も近い線分ab上のpointが渡される
double distToLineSegment(point p, point a, point b, point &c){
    vec ap = toVec(a, p);
    vec ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);

    // uが0より小さいならば,point pから直線abに下した垂線
    // は線分abと交わらず,垂線の足はbよりaの方が近い.
    // uが1より大きいならば同様に交わらず,垂線の足はaよりbの方が近い.
    if(u < 0.0){
        c = point(a.x , a.y);
        return dist(p, a);
    }else if(u > 1.0){
        c = point(b.x , b.y);
        return dist(p, b);
    }

    // point pの線分abへの射影が線分ab上に収まる
    return distToLine(p, a, b, c);
}

/* -------------------------------------------------- */

// 3つのpointが成す角(ラジアン).
// cos = (oa,ob)/(|oa|*|ob|)を利用.
double angle(point a, point o, point b){
    vec oa = toVec(o, a);
    vec ob = toVec(o, b);
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

// vecの外積
double cross(vec v1, vec v2){
    return v1.x * v2.y - v1.y * v2.x;
}

// (未確認)
bool ccw(point p, point q, point r){
    return cross(toVec(p, q), toVec(p, r)) > 0;
}

// 3つのpointが単一直線上にあるかどうかの判定
bool collinear(point p, point q, point r){
    return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}

/* -------------------------------------------------- */

// !誤差をきちんと処理できているかどうか未確認!
// point cを中心とした半径rの円にpoint pが含まれるかどうかの判定
// 0 - 内側, 1 - 境界上, 2 - 外側
int insideCircle(point p, point c, double r){
    double dx = p.x - c.x;
    double dy = p.y - c.y;
    double euc = dx*dx + dy*dy;
    double rSq = r*r;
    return rSq - euc > EPS ? 0 : rSq - euc < EPS ? 1 : 2; 
}

/* -------------------------------------------------- */

// 3辺の長さから三角形の面積を求める(ヘロンの公式)
double area(double a, double b, double c){
    double s = (a + b + c) / 2.0;
    return sqrt(s * (s-a) * (s-b) * (s-c));
}

// 3つのpointから成る三角形の内心円の半径を求める
double radiusInCircle(point a, point b, point c){
    double ab = dist(a, b);
    double bc = dist(b, c);
    double ca = dist(c, a);
    
    double A = area(ab, bc, ca);
    double p = ab + bc + ca;
    
    return A / p * 2.0;
}

// ！未確認！
// 三角形の内心を求める.ctrには内心のpointが,rには内心円の半径が入る
// 角Aの二等分線は対辺BCをAB:Acに内分することを利用.内分点をPとすると,
// BP = BC * AB / (AB+AC) = BC * 1 / (1 + AC/AB) = BC * 1 / (1 + ratio).
int inCircle(point p1, point p2, point p3, point &ctr, double &r){
    r = radiusInCircle(p1, p2, p3);

    // 内接円の半径が0ならば、3点は単一直線上にあり三角形を成さない
    if(fabs(r) < EPS)   return 0;
    
    // これから求める角の二等分線
    line l1, l2;

    double ratio = dist(p1, p2) / dist(p1, p3);
    point p = translate(p2, scale(toVec(p2, p3), ratio / (1.0 + ratio)));
    pointsToLine(p1, p, l1);

    ratio = dist(p2, p1) / dist(p2, p3);
    p = translate(p1, scale(toVec(p1, p3), ratio / (1.0 + ratio)));
    pointsToLine(p2, p, l2);
    
    // l1とl2の交点を内心点ctrに代入
    areIntersect(l1, l2, ctr);

    return 1;
}

// 三角形の外心,外接円関係の関数も頑張って書いて.
// あと,余弦定理とか正弦定理とか

/* -------------------------------------------------- */

// polygonに関する関数,頑張って書いてください.

/* -------------------------------------------------- */

// 凸包を求めるのに用いる一連の関数
point pivot(0.0, 0.0);

// Graham's Scanの前準備で必要な,pivotからの偏角でソートするときに必要な比較関数
bool angleCmp(point a, point b){
    // 偏角が同じ(pivot,a,bが単一直線上に乗っている)場合は,pivotからの距離が近い方を優先
    if(collinear(pivot, a, b)){
        return dist(pivot, a) < dist(pivot, b);
    }

    double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
    double d2x = b.x - pivot.x, d2y = b.y - pivot.y;

    return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
}

// 与えられた点群から凸包を求める(Graham's Scan)
vector<point> ConvexHull(vector<point> P){
    int i, j, n = (int)P.size();

    // 点群が3つしかない場合,P[0]をPに加える(輪っかのイメージ)
    if(n <= 3){
        if(!(P[0] == P[n-1]))  P.push_back(P[0]);
        return P;
    }

    // pivotを定める.最下,最右の点
    int P0 = 0;
    for(i = 1; i < n; i++){
        if(P[i].y < P[P0].y || 
           (P[i].y == P[P0].y && P[i].x > P[P0].x)){
               P0 = i;
        }
    }

    // P[0]とpivotとして選ばれたP[P0]をスワップ
    point temp = P[0];
    P[0] = P[P0];
    P[P0] = temp;

    pivot = P[0];
    sort(++P.begin(), P.end(), angleCmp);

    vector<point> S;
    S.push_back(P[n-1]);
    S.push_back(P[0]);
    S.push_back(P[1]);
    
    i = 2;
    while(i < n){
        j = (int)S.size() - 1;

        if(ccw(S[j-1], S[j], P[i]))
            S.push_back(P[i++]);
        else
            S.pop_back();
    }

    return S;
}

int main(){

}
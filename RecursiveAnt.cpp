//gskhirtladze

#include <bits/stdc++.h>

using namespace std;

map < pair < int , int > , int > F;
int n;

int recursive_dive(int stx,int sty,int x,int y,int n,int m) {

    if (x < stx || y < sty || x >= stx+(1<<n) || y >= sty+(1<<n)) return 0;

    if (n == m) {

        bool down = ( x >= stx+(1<<(n-1)) );
        bool right = ( y >= sty+(1<<(n-1)) );

        if (down && right) return 3;
        if (down) return 4;
        if (right) return 2;
        return 1;

    }

    n--;
    int quart = 0;

    quart += recursive_dive(stx,sty,x,y,n,m);
    quart += recursive_dive(stx+(1<<n),sty,x,y,n,m);
    quart += recursive_dive(stx,sty+(1<<n),x,y,n,m);
    quart += recursive_dive(stx+(1<<n),sty+(1<<n),x,y,n,m);

    return quart;

}

int get_quarter(int x,int y,int m) {

    return recursive_dive(0,0,x,y,n,m);

}

pair < int , int > recursive_dive_second(int stx,int sty,int x,int y,int n,int m) {

    if (x < stx || y < sty || x >= stx+(1<<n) || y >= sty+(1<<n)) return {-1,-1};

    if (n == m) return {stx,sty};

    n--;

    pair < int , int > start_point = {-1,-1};

    start_point = max ( start_point , recursive_dive_second(stx,sty,x,y,n,m) );
    start_point = max ( start_point , recursive_dive_second(stx+(1<<n),sty,x,y,n,m) );
    start_point = max ( start_point , recursive_dive_second(stx,sty+(1<<n),x,y,n,m) );
    start_point = max ( start_point , recursive_dive_second(stx+(1<<n),sty+(1<<n),x,y,n,m) );

    return start_point;
}

pair < int , int > get_start_coordinates(int x,int y,int m) {

    return recursive_dive_second(0,0,x,y,n,m);

}

bool check_for_forbidden(int stx,int sty,int enx,int eny) {

    for (int i = stx; i < enx; i++)
        for (int j = sty; j < eny; j++)
            if (!F[ {i,j} ]) return false;

    return true;
}

vector < pair < int , int > > all_points;

bool all_is_clear(int stx,int sty,int enx,int eny) {

    for (auto P : all_points) {

        if (stx <= P.first && P.first < enx)
            if (sty <= P.second && P.second < eny)
                return false;

    }

    return true;

}

bool dfs(int x,int y,int n,int dir,int &nextX,int &nextY) {

    if (F[ {x,y} ]) return false;

    nextX=x;
    nextY=y;

    if (n == 0) {

        if (dir == 1) nextX--;
        if (dir == 4) nextY--;
        if (dir == 2) nextY++;
        if (dir == 3) nextX++;
        return true;

    }

    pair < int , int > start_point = get_start_coordinates(x,y,n);

    int stx = start_point.first,sty = start_point.second;

    if (n >= 1 && all_is_clear(stx,sty,stx+(1<<n),sty+(1<<n))) {

        x-=stx;
        y-=sty;

        x=(1<<n)-x-1;

        if (dir == 1 && x == 0)
            goto next_step;
        if (dir == 2 && y == (1<<n)-1)
            goto next_step;
        if (dir == 3 && x == (1<<n)-1)
            goto next_step;
        if (dir == 4 && y == 0)
            goto next_step;

        x=(1<<n)-x-1;
        y=(1<<n)-y-1;

        if (dir == 1 && x == 0)
            goto next_step;
        if (dir == 2 && y == (1<<n)-1)
            goto next_step;
        if (dir == 3 && x == (1<<n)-1)
            goto next_step;
        if (dir == 4 && y == 0)
            goto next_step;

        y=(1<<n)-y-1;
        swap(x,y);
        x=(1<<n)-x-1;

        if (dir == 1 && x == 0)
            goto next_step;
        if (dir == 2 && y == (1<<n)-1)
            goto next_step;
        if (dir == 3 && x == (1<<n)-1)
            goto next_step;
        if (dir == 4 && y == 0)
            goto next_step;

        x=(1<<n)-x-1;
        y=(1<<n)-y-1;

        next_step :

        nextX=x+stx;
        nextY=y+sty;

        if (dir == 1) nextX--;
        if (dir == 4) nextY--;
        if (dir == 2) nextY++;
        if (dir == 3) nextX++;

        return true;

    }

    vector < int > directions;
    int quart = get_quarter(x,y,n);

    if (quart == 1) {

        if (dir == 1)
            directions = {3,2,1,1};
        if (dir == 2)
            directions = {3,2,1,2};
        if (dir == 3)
            directions = {2,3,4,3};
        if (dir == 4)
            directions = {2,3,4,4};

    }

    if (quart == 2) {

        if (dir == 1)
            directions = {3,4,1,1};
        if (dir == 2)
            directions = {4,3,2,2};
        if (dir == 3)
            directions = {4,3,2,3};
        if (dir == 4)
            directions = {3,4,1,4};

    }

    if (quart == 4) {

        if (dir == 1)
            directions = {2,1,4,1};
        if (dir == 2)
            directions = {1,2,3,2};
        if (dir == 3)
            directions = {1,2,3,3};
        if (dir == 4)
            directions = {2,1,4,4};

    }

    if (quart == 3) {

        if (dir == 1)
            directions = {4,1,2,1};
        if (dir == 2)
            directions = {4,1,2,2};
        if (dir == 3)
            directions = {1,4,3,3};
        if (dir == 4)
            directions = {1,4,3,4};

    }

    bool quarter;
    quarter = true;

    if (n <= 3) {

        pair < int , int > start_point = get_start_coordinates(x,y,n);

        int stx = start_point.first,sty = start_point.second;

        bool forbidden1 = check_for_forbidden(stx,sty,stx+(1<<(n-1)),sty+(1<<(n-1)));
        bool forbidden2 = check_for_forbidden(stx,sty+(1<<(n-1)),stx+(1<<(n-1)),sty+(1<<n));
        bool forbidden3 = check_for_forbidden(stx+(1<<(n-1)),sty+(1<<(n-1)),stx+(1<<n),sty+(1<<n));
        bool forbidden4 = check_for_forbidden(stx+(1<<(n-1)),sty,stx+(1<<n),sty+(1<<(n-1)));

        if (!forbidden1 && !forbidden2 && !forbidden3 && !forbidden4)
            goto normal_solution;

        if (quart == 1) {

            if (forbidden2 && forbidden4 && forbidden3) {

                if (dir == 2 || dir == 3)
                    return false;
                directions = {dir};
                goto normal_solution;

            }

            if (forbidden2 && forbidden4)
                return false;

            if (forbidden2 && forbidden3) {

                if (dir == 1 || dir == 2)
                    return false;
                directions = {3,dir};
                goto normal_solution;

            }

            if (forbidden2) {

                if (dir == 1 || dir == 4)
                    return false;
                directions = {3,2,dir};
                goto normal_solution;

            }

            if (forbidden3 && forbidden4) {

                if (dir == 3 || dir == 4)
                    return false;
                directions = {2,dir};
                goto normal_solution;

            }

            if (forbidden3)
                return false;

            if (dir == 1 || dir == 4)
                return false;
            directions = {2,3,dir};
            goto normal_solution;

        }

        if (quart == 2) {

            if (forbidden1 && forbidden4 && forbidden3) {

                if (dir == 3 || dir == 4)
                    return false;
                directions = {dir};
                goto normal_solution;

            }

            if (forbidden1 && forbidden3)
                return false;

            if (forbidden1 && forbidden4) {

                if (dir == 1 || dir == 4)
                    return false;
                directions = {3,dir};
                goto normal_solution;

            }

            if (forbidden1) {

                if (dir == 1 || dir == 2)
                    return false;
                directions = {3,4,dir};
                goto normal_solution;

            }

            if (forbidden3 && forbidden4) {

                if (dir == 3 || dir == 2)
                    return false;
                directions = {4,dir};
                goto normal_solution;

            }

            if (forbidden4)
                return false;

            if (dir == 1 || dir == 2)
                return false;
            directions = {4,3,dir};
            goto normal_solution;

        }

        if (quart == 3) {

            if (forbidden2 && forbidden4 && forbidden1) {

                if (dir == 1 || dir == 4)
                    return false;
                directions = {dir};
                goto normal_solution;

            }

            if (forbidden2 && forbidden4)
                return false;

            if (forbidden4 && forbidden1) {

                if (dir == 4 || dir == 3)
                    return false;
                directions = {1,dir};
                goto normal_solution;

            }

            if (forbidden4) {

                if (dir == 3 || dir == 2)
                    return false;
                directions = {1,4,dir};
                goto normal_solution;

            }

            if (forbidden1 && forbidden2) {

                if (dir == 1 || dir == 2)
                    return false;
                directions = {4,dir};
                goto normal_solution;

            }

            if (forbidden1)
                return false;

            if (dir == 3 || dir == 2)
                return false;
            directions = {4,1,dir};
            goto normal_solution;

        }

        if (quart == 4) {

            if (forbidden1 && forbidden2 && forbidden3) {

                if (dir == 1 || dir == 2)
                    return false;
                directions = {dir};
                goto normal_solution;

            }

            if (forbidden1 && forbidden3)
                return false;

            if (forbidden3 && forbidden2) {

                if (dir == 2 || dir == 3)
                    return false;
                directions = {1,dir};
                goto normal_solution;

            }

            if (forbidden3) {

                if (dir == 3 || dir == 4)
                    return false;
                directions = {1,2,dir};
                goto normal_solution;

            }

            if (forbidden1 && forbidden2) {

                if (dir == 1 || dir == 4)
                    return false;
                directions = {2,dir};
                goto normal_solution;

            }

            if (forbidden2)
                return false;

            if (dir == 3 || dir == 4)
                return false;
            directions = {2,1,dir};
            goto normal_solution;

        }

    }

    normal_solution :

    for (auto direction : directions) {

        quarter &= dfs(nextX,nextY,n-1,direction,nextX,nextY);
        if (!quarter)
            break;

    }

    return quarter;

}

int main() {

    //freopen("sample.in","r",stdin);

    int num_points;

    cin >> n >> num_points;

    for (int i = 1; i <= num_points; i++) {

        int a,b;
        cin >> a >> b;
        F[ {a,b} ]=1;
        all_points.push_back( {a,b} );

    }

    for (int i = 1; i <= 4; i++) {

        int nextX = 0,nextY = 0;

        if (dfs(0,0,n,i,nextX,nextY)) {

            if (nextX < 0) nextX++;
            if (nextX >= (1<<n)) nextX--;
            if (nextY < 0) nextY++;
            if (nextY >= (1<<n)) nextY--;

            cout << nextX << " " << nextY << endl;

        } else {

            cout << "NIE" << endl;

        }

    }
}

#include <cstdio>
#include <cstring>
using namespace std;

struct Location{
    double lat, lon;
};

char base32[32] = {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'j', 'k', 'm', 'n', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
};

int rbase32[128];
char cres[13];
Location lres;

void init(){
    memset(rbase32, 0, sizeof(rbase32));
    for(int i = 0; i < 32; ++i){
        rbase32[base32[i]] = i;
    }
}

void encode(int prec){
    double lat[2] = {-90, 90}, lon[2] = {-180, 180};
    int length = prec * 5, bits = 0;
    memset(cres, 0, sizeof(cres));
    for(int i = 1; i <= length; ++i){
        if(i % 2 == 1){
            double mid = (lon[0] + lon[1]) / 2;
            if(lres.lon > mid){
                bits = bits * 2 + 1;
                lon[0] = mid;
            }else{
                bits = bits * 2;
                lon[1] = mid;
            }
        }else{
            double mid = (lat[0] + lat[1]) / 2;
            if(lres.lat > mid){
                bits = bits * 2 + 1;
                lat[0] = mid;
            }else{
                bits = bits * 2;
                lat[1] = mid;
            }
        }
        if(i % 5 == 0){
            cres[i / 5 - 1] = base32[bits];
            bits = 0;
        }
    }
}

void decode(){
    bool odd = true;
    double lat[2] = {-90, 90}, lon[2] = {-180, 180};
    int length = strlen(cres);
    for(int i = 0; i < length; ++i){
        int bits = rbase32[cres[i]];
        for(int j = 4; j >= 0; --j){
            int bit = (bits >> j) & 1;
            if(odd){
                double mid = (lon[0] + lon[1]) / 2;
                lon[1 - bit] = mid;
            }else{
                double mid = (lat[0] + lat[1]) / 2;
                lat[1 - bit] = mid;
            }
            odd = !odd;
        }
    }
    lres.lat = (lat[0] + lat[1]) / 2;
    lres.lon = (lon[0] + lon[1]) / 2;
}

int main(){
    init();
    int N, M; scanf("%d%d", &N, &M);
    for(int i = 0; i < N; ++i){
        scanf("%lf%lf", &lres.lat, &lres.lon);
        encode(10);
        printf("%s\n", cres);
    }
    for(int i = 0; i < M; ++i){
        scanf("%s", cres);
        decode();
        printf("%.6lf %.6lf\n", lres.lat, lres.lon);
    }
    return 0;
}

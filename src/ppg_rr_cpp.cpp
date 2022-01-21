#include "ppg_rr_cpp.h"
#include "PolyfitEigen.h"
#include "interp1_f.h"

using namespace Eigen;
//using namespace std;


void ppg_rr(std::vector<double> ppg, std::vector<double> t){
    int N = ppg.size();
    VectorXd t2  = Eigen::Map<VectorXd>(t.data(),t.size());
    t2 = t2 * 0.01;
    //std::cout<<t2<<std::endl;
    std::vector<double> coeffJacobi = polyfit_Eigen(t, ppg, 3,std::vector<double>(), false);
    std::vector<double> testValuesYJacobi = polyval(coeffJacobi, t);
    for (int i = 0;i < ppg.size();i++){
        ppg[i] = ppg[i] - testValuesYJacobi[i];
    }
    double tc[(N-1)*100+1];
    tc[0] = 1;
    for (int i = 1; i< (N-1)*100+1; i++){
        tc[i] = tc[i-1] + 0.01;
    }
    double ppg2[(N-1)*100+1] ;
    interp1_f(&t[0],&ppg[0],tc,ppg2);
    int N2 = (N-1)*100+1;

    //寻找极大值点
    int I = 1;
    double ll = (N2-1) / 30;
    RowVectorXd k = RowVectorXd::Zero(ll);
    for (int i = 16; i <= N2 - 16; i++){
        double max = __DBL_MIN__;
        for (int j = i-15;j <= i+15;j++  ){
            if (ppg2[j] > max){
                max = ppg2[j];
            }
        }
        if (ppg2[i] >= max){
            k[I] = t[j];
            I++;
        }
    }
    //计算RR间期并对应到各时刻
    int n1 = 0;
    for (int i = 1; i<= ll;i++){
        if (k[i] != 0){
            n1++;
        }
    }
    


}
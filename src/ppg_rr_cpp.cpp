#include "ppg_rr_cpp.h"
#include "PolyfitEigen.h"
#include "interp1_f2.h"
#include <algorithm>
#include "spline_any.h"


using namespace Eigen;
//using namespace std;


void ppg_rr(std::vector<double> ppg, std::vector<double> t){
    int N = ppg.size();
    VectorXd t2  = Eigen::Map<VectorXd>(t.data(),t.size());
    t2 = t2 * 0.01;
    //std::cout<<t2<<std::endl;
    std::vector<double> coeffJacobi = polyfit_Eigen(t, ppg, 3,std::vector<double>(), false);
    std::vector<double> testValuesYJacobi = polyval(coeffJacobi, t);
    // std::cout<<"ppg_jx"<<testValuesYJacobi.size()<<std::endl;
    // for (int i = 0;i < N;i++){
    //     std::cout<<testValuesYJacobi[i]<<" ";
    // }
    // std::cout<<std::endl;
    for (int i = 0;i < ppg.size();i++){
        ppg[i] = ppg[i] - testValuesYJacobi[i];
    }
    
    // for (int i = 0;i < testValuesYJacobi.size();i++){
    //     std::cout<<testValuesYJacobi[i]<<" ";
    // }
    // std::cout<<std::endl;

    // double tc[500];
    // tc[0] = 1;
    // for (int i = 1; i< (N-1)*100+1; i++){
    //     tc[i] = tc[i-1] + 0.01;
    // }
    VectorXd tc = t2.transpose();

    double ppg2[N] ;
    //std::cout<<"t_size:"<<t.size()<<"ppg_size:"<<ppg.size()<<"tc_size:"<<tc.size()<<std::endl;
    interp1_f2(&t2[0],&ppg[0],tc.data(),ppg2);
    for (int i = 0;i < N;i++){
        std::cout<<ppg2[i]<<" ";
    }
    std::cout<<std::endl;
    //int N2 = (N-1)*100+1;
    //寻找极大值点
    int I = 0;
    int ll = (N-1) / 30;
    RowVectorXd k = RowVectorXd::Zero(ll);
    for (int i = 15; i <= N - 16; i++){
        // double max = __DBL_MIN__;
        // for (int j = i-15;j <= i+15;j++  ){
        //     if (ppg2[j] > max){
        //         max = ppg2[j];
        //     }
        // }
        if (ppg2[i] >= (*std::max_element(&ppg2[i]-15,&ppg2[i] + 15))){
            k[I] = t2[i]; //k存储极大值所在时间点
            I++;
        }
    }
    for (int i = 0;i < ll;i++){
        std::cout<<k[i]<<" ";
    }
    std::cout<<std::endl;
    //计算RR间期并对应到各时刻
    int n1 = 0;
    for (int i = 0; i< ll;i++){
        if (k(i) != 0){
            n1++;
        }
    }
    std::cout<<"n1"<<n1<<std::endl;
    RowVectorXd rr = RowVectorXd::Zero(n1-1);
    int rr_size = n1-1;
    RowVectorXd tt = RowVectorXd::Zero(n1-1);
    std::cout<<"1"<<std::endl;

    int tt_size = n1-1;
    int J = 0;
    for (int i = 1;i<n1;i++){
        if ((k(i)-k(i-1))<=1.2 && (k(i)-k(i-1))>=0.2){
            rr(J) = k(i)-k(i-1);
            if ((k(i)-int(k(i)))<0.5){
                tt(J) = int(k(i));
            }
            else {
                tt(J) = int(k(i)) + 0.5;
            }
        }
        J++;
        if (J>=2 && tt(J-1) == tt(J-2)) {
            J--;
        }
    }
    int l = 1;
    for (int i = 0;i <rr_size-1;i++){
        if (rr(i) != 0){
            l = i;
        }
    }
    std::cout<<"2"<<std::endl;
    rr_size = l+1;
    tt_size = l+1;
    int nn = tt_size;
    if (tt(tt_size-1) == rr(rr_size-1)){
        rr_size--;
        tt_size--;
    }
    nn = tt_size;
    double m = (t2[N-1]-t2[0]+0.01)*2;
    double mm = (tt(nn-1)-tt(0))/(m-1);

    int num_mm = int((tt(nn-1)-tt(0))/mm)+2;
    double* t_rr = new double [num_mm]();
    t_rr[0] = tt[0];
    

    for (int i = 1;i < num_mm;i++){
        t_rr[i] = tt[0] + i*mm;
    }
    std::cout<<num_mm<<std::endl;

    double rr1[num_mm];
    interp1_f2(tt.data(),rr.data(),t_rr,rr1);
    tk::spline s(std::vector<double>(tt.data(),tt.data()+tt.size()),std::vector<double> (rr.data(),rr.data()+rr.size()));
    for (int i = 0;i < num_mm;i++){
        std::cout<<rr1[i]<<" ";
    }
    std::cout<<std::endl;
    
    int n = num_mm;
    //int t_rr1 = double(t[0])+0.5
    


}
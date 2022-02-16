#include "ppg_rr_cpp.h"
#include "PolyfitEigen.h"
#include "interp1_f2.h"
#include "spline_any.h"


using namespace Eigen;
//using namespace std;


void ppg_rr(std::vector<double> ppg, std::vector<double> t,bool save_file){
    int N = ppg.size();
    VectorXd t2  = Eigen::Map<VectorXd>(t.data(),t.size());
    t2 = t2 * 0.01;

    std::vector<double> coeffJacobi = polyfit_Eigen(t, ppg, 3,std::vector<double>(), false);
    std::vector<double> testValuesYJacobi = polyval(coeffJacobi, t);

    for (int i = 0;i < ppg.size();i++){
        ppg[i] = ppg[i] - testValuesYJacobi[i];
    }

    VectorXd tc = t2.transpose();

    double ppg2[N] ;

    interp1_f2(&t2[0],&ppg[0],tc.data(),ppg2);

    //int N2 = (N-1)*100+1;
    //寻找极大值点
    int I = 0;
    int ll = (N-1) / 30;
    RowVectorXd k = RowVectorXd::Zero(ll);
    for (int i = 15; i < N - 16; i++){
        if (ppg2[i] >= (*std::max_element(&ppg2[i]-15,&ppg2[i] + 16))){
            k[I] = t2[i]; //k存储极大值所在时间点
            I++;
        }
    }
    //计算RR间期并对应到各时刻
    int n1 = 0;
    for (int i = 0; i< ll;i++){
        if (k(i) != 0){
            n1++;
        }
    }

    RowVectorXd rr = RowVectorXd::Zero(n1-1);
    int rr_size = n1-1;
    RowVectorXd tt = RowVectorXd::Zero(n1-1);

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

    rr_size = l+1;
    tt_size = l+1;
    int nn = tt_size;
    if (tt(tt_size-1) == rr(rr_size-1)){
        rr_size--;
        tt_size--;
    }
    //对提取的RR间期信号进行插值重采样，保证每秒两个数据点
    nn = tt_size;
    double m = (t2[N-1]-t2[0]+0.01)*2;
    double mm = (tt(nn-1)-tt(0))/(m-1);

    int num_mm = int((tt(nn-1)-tt(0))/mm+0.001)+1;
    double* t_rr = new double [num_mm]();
    t_rr[0] = tt[0];
    

    for (int i = 1;i < num_mm;i++){
        t_rr[i] = tt[0] + i*mm;
    }
    // for (int i =0;i<tt.size();i++){
    //     std::cout<<tt[i]<<" ";
    // }
    // std::cout<<std::endl;

    double rr1[num_mm];
    //interp1_f2(tt.data(),rr.data(),t_rr,rr1);
    tk::spline s(std::vector<double>(tt.data(),tt.data()+tt_size),std::vector<double> (rr.data(),rr.data()+rr_size),tk::spline::cspline);

    for (int i = 0;i < num_mm;i++){
        rr1[i] = s(t_rr[i]);
    }
    int num_trr1 = (int(t2(N-1)) - int(t2(0)) - 0.5) / 0.5 + 1 ;
    double t_rr1[num_trr1];
    //t_rr1[0] = t2[0];
    for (int i = 0; i < num_trr1;i++){
        t_rr1[i] = int(t2[0]) + (i+1) * 0.5;
    }

/********* DEBUG ***********/
    if (save_file){
        std::ofstream outfile("../checkMiddleValue.txt", std::ios::trunc);
        outfile<<"k:  ";
        for (int i = 0; i <k.size();i++){
            outfile<<k[i]<<" ";
        }
        outfile<<"\n";

        outfile<<"tt:  ";
        for (int i = 0; i <rr_size;i++){
            outfile<<tt[i]<<" ";
        }
        outfile<<"\n";

        outfile<<"rr:  ";
        for (int i = 0; i <rr_size;i++){
            outfile<<rr[i]<<" ";
        }
        outfile<<"\n";

        outfile<<"mm:  "<<mm<<"\n";
        outfile<<"num_mm:  "<<num_mm<<"\n";

        outfile<<"t_rr1:  ";
        for (int i = 0; i < num_trr1;i++){
            outfile<<t_rr1[i]<<" ";
        }
        outfile<<"\n";

        outfile<<"rr1:  ";
        for (int i = 0; i<num_mm;i++){
            outfile<<rr1[i]<<" ";
        }
        outfile<<"\n";

        std::cout<<"MiddleValues have saved to ../checkMiddleValue.txt"<<std::endl;
        outfile.close();
    }

}
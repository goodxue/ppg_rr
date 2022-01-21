function [t_rr1,rr1]=ppg_rr(ppg,t)
    %读取设备测量的PPG信号并提取RR间期
    N=length(ppg);
    t=t.*0.01;
    %figure();plot(t,ppg);title('PPG信号');xlabel('t(s)');ylabel('ppg');
    %基线漂移-多项式拟合去趋势
    p=polyfit(t,ppg,3);
    ppg_jx=polyval(p,t);
    ppg=ppg-ppg_jx;
    %对ppg信号进行插值处理
    tc=t(1):0.01:t(N);
    ppg=interp1(t,ppg,tc,'spline');
    N=length(tc);
    t=tc;
    %寻找极大值点
    
    
    i=1;ll=floor((N-1)/30);
    k=zeros(1,ll);
    for j=16:N-16
        if ppg(j)>=max(ppg(j-15:j+15))
            k(i)=t(j);%k存储极大值所在时间点
            i=i+1;
        end
    end
    %计算RR间期并对应到各时刻
    n1=0;
    for j=1:length(k)
        if k(j)~=0
            n1=n1+1;
        end
    end
    rr=zeros(1,n1-1);
    tt=zeros(1,n1-1);
    i=1;
    for j=2:n1
        if (k(j)-k(j-1))<=1.2 && (k(j)-k(j-1))>=0.2
           rr(i)=k(j)-k(j-1);
           if (k(j)-floor(k(j)))<0.5
               tt(i)=floor(k(j));
           else
               tt(i)=floor(k(j))+0.5;
           end
           i=i+1;
           if i>=3 && tt(i-1)==tt(i-2)
               i=i-1;
           end
        end
    end
    l=1;
    for j=1:n1-1
        if rr(j)~=0
            l=j;
        end
    end
    rr(l+1:n1-1)=[];
    tt(l+1:n1-1)=[];
    nn=length(tt);
    if tt(nn)==tt(nn)
        tt(nn)=[];
        rr(nn)=[];
    end
    %对提取的RR间期信号进行插值重采样，保证每秒两个数据点
    nn=length(tt);
    m=(t(N)-t(1)+0.01)*2;
    mm=(tt(nn)-tt(1))/(m-1);
    t_rr=tt(1):mm:tt(nn);
    rr1=interp1(tt,rr,t_rr,'spline');
    n=length(t_rr);
    t_rr1=floor(t(1))+0.5:0.5:floor(t(N));
    end
    
    
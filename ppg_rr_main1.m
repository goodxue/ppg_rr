clear all;clc;close all;
%t=xlsread('1.csv',1,'A501:A1000');
%ppg=xlsread('1.csv',1,'B501:B1000');
data = csvread('1.csv',500,0,[500,0,999,1]);
t = data(:,1);
ppg = data(:,2);
[t_rr,rr]=ppg_rr(ppg,t);


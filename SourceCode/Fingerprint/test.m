clc;close all;clear;
image=imread('1-2.bmp');
imshow(image);
thin1=tuxiangyuchuli('1-2.bmp');
% figure;
txy1=point(thin1);
% [w1,txy1]=guanghua(thin1,txy1);
% hold on;
% plot(100,100,'r.');
% plot(100,100,'ro');
% hold off;
% hold on;
% 
%  plot(100,100,'r+');
% 
% for i=10:100
%     plot(i,i,'ro');
% end

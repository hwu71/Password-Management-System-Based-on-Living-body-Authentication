clc;clear
shuru1 = imread('1.bmp');
shuchu1 = preprocess(shuru1);
figure, imshow(shuchu1);
%shuru2 = imread('d:\1\1\2.bmp');
%shuchu2 = preprocess(shuru2);
shuchu2 = bwmorph(shuchu1, 'thin', inf);
figure, imshow(shuchu2);
%pipei = shibie(shuchu1, shuchu2)
%6,17,26,28
%feature_test = point(shuchu2);
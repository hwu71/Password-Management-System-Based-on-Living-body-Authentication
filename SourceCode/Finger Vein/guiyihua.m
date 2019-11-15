function shuchu = guiyihua(shuru)
%preprocess中调用，均值滤波，进行两次区域提取，一次以卡槽为边界，灰度归一化，二次以手指为边界，尺寸归一化
shuru = rgb2gray(shuru);
%figure, imshow(shuru);
shuru = im2double(shuru);

shuru = shuru(80:380, 150:450);

%均值滤波
%h=fspecial('average');
%shuru1 = filter2(h, shuru)
shuru1 = junzhilvbo(shuru,1);
%figure, imshow(shuru1);

%边缘检测，sobel算子，横向检查
[BW2, tv] = edge(shuru1, 'sobel', 'horizontal');
%figure, imshow(BW2);
%生成闭运算算子，圆盘形，半径2
se1 = strel('disk', 3);
%闭运算
%BW2 = imclose(BW2, se);
%Dilate = [0 0 1 0 0;0 1 1 1 0;1 1 1 1 1 ;0 1 1 1 0;0 0 1 0 0];
BW2 = imdilate(BW2, se1);
se2 = strel('disk', 2);
BW2 = imerode(BW2, se2);
%figure, imshow(BW2);
%骨骼化
%BW2 = bwmorph(BW2, 'thin', Inf);
%figure, imshow(BW2);

%调用滤波m文件
BW2 = lvboo(BW2, 290, 10, 150);
%figure, imshow(BW2);

%调用边界m文件
[min1 max1] = bianjie(BW2);
k = shuru(min1:max1, :);
%figure, imshow(k);
[m,n] = size(k);

%灰度归一化,双线性插值法
p = max(max(k(:,:))) - min(min(k(:,:)));
y = double(1/double(p));
k(:,:) = double((double(y) * double((k(:,:) - min(min(k(:,:)))))));
%figure, imshow(k);

%二次裁剪
[min2 max2]=ercicaijian(k, m, n, se1, se2);
k = k(min2:max2, :);
%figure, imshow(k);
[m,n] = size(k);

%尺寸灰度归一化
%尺寸归一化所用滤波器
s = [double(96/n) 0 0; 0 double(64/m) 0; 0 0 1];
%生成滤波器
tform = maketform('affine', double(s));
k = imtransform(k, tform, 'XData', [1 96], 'YData', [1 64], 'FillValue', 0);
[m,n] = size(k);
%figure, imshow(k);

shuchu = k;
%imshow(shuchu);

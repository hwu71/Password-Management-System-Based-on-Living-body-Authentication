function [min1, max1] = ercicaijian(shuru, m, n, se1, se2)
%guiyihua中调用，二次裁剪，为了截取手指区域
%变二值图像，为了二次裁剪
BW2 = shuru;
%figure, imshow(BW2);
for i = 1:m
    for j = 1:n
        if BW2(i, j) > 0.94%阈值取大点，边界会不精确，可以靠膨胀弥补
            BW2(i, j) = 1;
            
        else
            BW2(i, j) = 0;
        end
    end
end
%黑白变换
BW2 = im2bw(BW2);
%figure, imshow(BW2);
%二次边界裁剪
[BW2, tv] = edge(BW2, 'sobel', 'horizontal');
BW2 = imdilate(BW2, se1);
%BW2 = imerode(BW2, se2);
BW2 = ~BW2;
%figure, imshow(BW2);
BW3 = BW2;
temp_size = 0;
temp_num = 0;
[g, num]=bwlabel(BW2, 8);
for i = 1:num
    [r, c] = find(bwlabel(BW3, 8) == i);
    if temp_size < (max(r) - min(r))*(max(c) - min(c))
        temp_size = (max(r) - min(r))*(max(c) - min(c));
        if temp_num ~= 0
            [r, c] = find(bwlabel(BW3, 8) == temp_num);
            BW2(r, c) = 0;
        else
        end
        temp_num = i;
    else
        BW2(r, c) = 0;
    end
    
end
BW2 = ~BW2;
[g, num]=bwlabel(BW2, 8);
BW3 = BW2;
%figure, imshow(BW2);
for i = 1: num
    [r, c] = find(bwlabel(BW3, 8) == i);
    if (max(r) + min(r))/2 <= m*3/4 && (max(r) + min(r))/2 >= m*1/4
        BW2(r, c) = 0;
    end
end
se3 = strel('disk', 20);
%BW2 = imdilate(BW2, se1);
%BW2 = imerode(BW2, se2);
%figure, imshow(BW2);
[BW2, tv] = edge(BW2, 'sobel', 'horizontal');
BW2 = imdilate(BW2, se3);
[min1 max1] = bianjie(BW2);
max1 = max1 + 20;
min1 = min1 - 20;
%figure, imshow(BW2);

%特征点提取，找出所有的断点和交叉点

%本函数对图像中每个点的8邻域位置进行坐标定义
function j=p(img,x,y,i)
%  1  2  3
%  8  i  4
%  7  6  5
switch(i)
    case {1,9}
        j=img(x-1,y-1);
    case 2
        j=img(x-1,y);
    case 3
        j=img(x-1,y+1);
    case 4
        j=img(x,y+1);
    case 5
        j=img(x+1,y+1);
    case 6
        j=img(x+1,y);
    case 7
        j=img(x+1,y-1);
    case 8
        j=img(x,y-1);
end

        

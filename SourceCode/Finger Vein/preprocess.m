function shuchu = preprocess(shuru)
shuru = guiyihua(shuru);
%figure, imshow(shuru);
%impixelinfo
shuru = fangxiangfenge6(shuru,10);
%figure, imshow(shuru);
shuru = lvbo(shuru,50);
shuru = medfilt2(shuru);
%figure, imshow(shuru);
shuru = tianchong(shuru, 3);
shuru = lvbo(shuru,200);
%shuru = gugehua(shuru);

%shuchu = fenge(shuru, 4, inf);

shuchu = shuru;

%imwrite(shuchu,'d:\1\write2\33.bmp');
%h=imread('d:\1\1_5zhang.bmp');

ni=3.0;



    sum=0;
    
    
    shuru=imread('d:\1\26\1.bmp');
    img(:,:,1)=guiyihua(shuru);
    figure,imshow(img(:,:,1));
    sum=sum+double(img(:,:,1));
    
    shuru=imread('d:\1\26\2.bmp');
    img(:,:,2)=guiyihua(shuru);
    figure,imshow(img(:,:,2));
    sum=sum+double(img(:,:,2));

    shuru=imread('d:\1\26\3.bmp');
    img(:,:,3)=guiyihua(shuru);
    figure,imshow(img(:,:,3));
    sum=sum+double(img(:,:,3));

    m(:,:,1)=sum/ni;
    
    junzhi=m(:,:,1);
%    chulihou1=leichuli(junzhi);
figure,imshow(junzhi);
    
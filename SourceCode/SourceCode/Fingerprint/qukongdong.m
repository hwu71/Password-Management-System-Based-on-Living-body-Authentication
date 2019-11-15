function shuchu= qukongdong(shuru, area)
%preprocess调用，填充静脉上的缺口
k = shuru;
kk = k;
% figure,imshow(k);
[g, num] = bwlabel(k, 4);
for i = 1:2
    for j = 1:num
        [r, c] = find(bwlabel(kk) == j);
        area_temp = bwarea(find(bwlabel(kk) == j));
        if area_temp < area
            k(r, c) = 0;
        end
    end
end
shuchu = k;
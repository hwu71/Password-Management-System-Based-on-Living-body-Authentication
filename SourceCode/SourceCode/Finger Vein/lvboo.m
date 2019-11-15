function hh = lvboo(h1, a, b, d)
%归一化中调用，提取边界时，滤掉不符合要求的边界
for j = 1:30
    [g, num]=bwlabel(h1, 8);
    for i = 1:num
        [r, c] = find(bwlabel(h1) == i);
        if max(r) > a | min(r) < b | (max(c) - min(c)) < d  %
            h1(r,c) = 0;
            %(max(c) - min(c))
        end
    end
    %num
    if num == 2
        break;
    end
end


hh = h1;
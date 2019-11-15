function [c] = junzhilvbo(j,k)%j为图像，k为扩大边界值
%guiyihua中调用，均值滤波
[m,n] = size(j);
b = zeros(m+2*k, n+2*k);
b(k+1 : m+k, k+1 : n+k) = double(j(:,:));
c = zeros(m, n);
for i = k+1 : m+k
    for j = k+1 : n+k
        b(i, j) = sum(sum(b(i-k : i+k, j-k : j+k)))/((2*k + 1).^2);
    end
end
c(:, :) = b(k+1 : m+k, k+1 : n+k);
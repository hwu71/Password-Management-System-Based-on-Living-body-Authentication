function shuchu = shibie(a, b)
%a:正常，b:细化之后   64*96
%c = a.*b;
num_pipei = 0;
num_size = 0;
for m = 1:64
    for n = 1:96
        if b(m, n) == 1
            num_size = num_size + 1;
            if a(m, n) == 1
                num_pipei = num_pipei + 1;
            else
            end
        else
        end
    end
end

shuchu = num_pipei/num_size;


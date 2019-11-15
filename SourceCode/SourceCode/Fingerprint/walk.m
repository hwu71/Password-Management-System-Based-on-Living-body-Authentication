%判断离端点num距离内是否有另一端点
function [error,a,b]=walk(thin,x0,y0,num)
error=0;
thin(y0,x0)=0;
% fprintf()
% t1=0;
a=x0;
b=y0;
for n=1:num
    if error==1
        break
    else
        %判断该点八邻域点和该点的和 来找出想要的点
        for x=x0-1:x0+1
            if error==1
                break;
            else
                for y=y0-1:y0+1
                    t1=(sum(sum(thin(y0-1:y0+1,x0-1:x0+1))));
%                    t1=(p(thin,y0,x0,2)~=p(thin,y0,x0,1)) +(p(thin,y0,x0,3)~=p(thin,y0,x0,2)) + (p(thin,y0,x0,4)~=p(thin,y0,x0,3)) +...
%                     +(p(thin,y0,x0,5)~=p(thin,y0,x0,4)) + (p(thin,y0,x0,6)~=p(thin,y0,x0,5)) + (p(thin,y0,x0,7)~=p(thin,y0,x0,6)) +...
%                     +(p(thin,y0,x0,8)~=p(thin,y0,x0,7)) + (p(thin,y0,x0,1)~=p(thin,y0,x0,8));
                    %=0代表一个断点（独立的点） 大于2代表不是端点
%                fprintf('x0 %d, y0 %d ,t1 %d\n',x0,y0,t1);
%                     if(t1>2)
                    if(t1==2)
                        error=1;
                        a=x0;
                        b=y0;
%                         fprintf('%d %d exit1\n',a,b);
                        break;
                    else
                        % x,y还是y，x
                        if (thin(y,x)==1&&(x-x0)^2+(y-y0)^2~=0)
                            if(t1==3)
                                error=1;
                                a=x0;
                                b=y0;
%                                 fprintf('%d %d exit2\n',a,b);
                                break;
                            else
                                thin(y,x)=0;
%                                 fprintf('1\n');
                                x0=x;
                                y0=y;
                                a=x0;
                                b=y0;
                                plot(x0,y0,'r.');
                            end
                        end
                    end
                end
            end
        end
    end
end

              
                        
        

c,n,*l=r={};$<.map{_1=~/d (.+)|(\d+) (.+)/;k=$1;l=k<?/?l[..-2]:(c[k]={n=>0};l+[k])if k;c[n]+=$2.to_i if$2;c=r.dig *l};f=->h{v=h.delete(n)||0;s,*r=h.each.map{f[_2]}.transpose;s||=[];[v+s.sum,r+s]};p f[r].flatten.filter{_1<1e5}.sum
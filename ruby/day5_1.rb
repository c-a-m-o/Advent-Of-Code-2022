l=$<.take_while{_1[1]}.map{_1.chars.each_slice(4).map{|l|l[1]}}.transpose.map{_1-[" "]};$<.map{q,f,t=_1.split.map(&:to_i)-[0];l[t-1]=l[f-1].slice!(...q).reverse+l[t-1]};p l.map{_1[0]}.join
p$<.count{|l|a,b,c,d=l.split(/-|,/).map &:to_i;[a..b,c..d].permutation.any?{_1===_2.min}}

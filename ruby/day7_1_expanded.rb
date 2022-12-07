path = []
curr = root = {}
n=$,
$<.map {|line|
  line =~ /\$ cd (.+)|(\d+) (.+)/
  # print line, [$1, $2, $3]
  # puts "#{path} | #{root} | #{line}"
  if $1
    if $1<?/
      path=path[..-2]
    else
      path=path + [$1]
      curr[$1]={n=>0}
    end
  end
  
  if $2
    curr[n]+=$2.to_i
  end
  curr = root.dig(*path)
}
def f(h)
  val = (h.delete(nil)||0)
  tmp = h.each.map{f _2}
  sizes, *results = tmp.transpose||[]


  if sizes
    [val + sizes.sum, results+sizes]
  else
    [val, results]
  end
end

p f(root).flatten.filter{_1<1e5}.sum
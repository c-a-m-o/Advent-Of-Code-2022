p$<.each_slice(3).sum{x,*_=_1.map(&:codepoints).reduce:&;x-(x<97?38:96)}
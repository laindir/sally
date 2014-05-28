function expand(s, t,n,r) {
	if(s in rev) {
		return sprintf("%c", int(rev[s]));
	} else if(s in def) {
		n = split(def[s], t);
		for(i = 1; i <= n; i++) {
			r = r expand(t[i]);
		}
		return r;
	} else {
		return sprintf("%c%c", int(rev["lit"]), int(s));
	}
}

BEGIN {
	split("lit + xor and or invert = < swap dup drop over 1- . ,", words);
	for(i in words) {
		n++;
		rev[words[i]] = i;
	}
}

/^: [^ ]+ .* ;$/ {
	w = $2;
	$1 = "";
	$2 = "";
	$NF = "";
	def[w] = $0;
	next;
}

{
	for(i = 1; i <= NF; i++) {
		printf expand($i);
	}
}

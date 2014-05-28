function expand(s, t,n,i) {
	if(s in rev) {
		printf("%c", int(rev[s]));
	} else if(s in def) {
		n = split(def[s], t);
		for(i = 1; i <= n; i++) {
			expand(t[i]);
		}
	} else {
		printf("%c%c", int(rev["lit"]), int(s));
	}
}

BEGIN {
	split("lit + xor and or invert = < swap dup drop over 1- >r r> lshift rshift . ,", words);
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
		expand($i);
	}
}

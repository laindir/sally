function hi(n) {
	return int(n / 256);
}

function lo(n) {
	return int(n % 256);
}

function expand(s, t,n,i) {
	if(s in rev) {
		printf("%c", int(rev[s]));
		if(compile) bound++;
	} else if(s in def) {
		printf("%c%c%c%c%c", int(rev["lit"]), int(lo(def[s])), int(rev["lit"]), int(hi(def[s])), int(rev["call"]));
		if(compile) bound += 5;
	} else {
		printf("%c%c", int(rev["lit"]), int(s));
		if(compile) bound += 2;
	}
}

BEGIN {
	split("lit + xor and or invert = < swap dup drop over 1- >r r> lshift rshift call ret . ,", words);
	for(i in words) {
		rev[words[i]] = i;
	}
}

/^: [^ ]+ .* ;$/ {
	w = $2;
	$1 = "";
	$2 = "";
	$NF = "";
	$0 = $0;
	def[w] = bound;
	compile = 1;
}

{
	if(compile) printf("%c", 0);
	for(i = 1; i <= NF; i++) {
		expand($i);
	}
	if(compile) printf("%c", 0);
	compile = 0;
}

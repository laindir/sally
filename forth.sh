stdbuf -o0 mawk -f compiler.awk "$@" | ./interpreter

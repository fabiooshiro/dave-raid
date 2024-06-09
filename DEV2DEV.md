# Dev 2 Dev

How to run:

```sh
rivemu -workspace -exec riv-jit-c main.c
```

How to compile:
```sh
alias rivemu-exec='rivemu -quiet -no-window -sdk -workspace -exec'
rivemu-exec gcc main.c -o main '$(riv-opt-flags -Ospeed)'
rivemu-exec riv-strip main
rivemu-exec riv-mksqfs main sprites.png main.sqfs
rivemu main.sqfs
```

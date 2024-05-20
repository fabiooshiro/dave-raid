# Dev 2 Dev

```sh
alias rivemu-exec='rivemu -quiet -no-window -sdk -workspace -exec'
rivemu-exec gcc main.c -o main '$(riv-opt-flags -Ospeed)'
rivemu-exec riv-strip main
rivemu-exec riv-mksqfs main sprites.png main.sqfs
rivemu main.sqfs
```

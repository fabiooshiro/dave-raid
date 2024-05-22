rm -rf main.sqfs

wget -O rivemu https://github.com/rives-io/riv/releases/latest/download/rivemu-linux-amd64
chmod +x rivemu

mkdir -p $HOME/.riv
mv rivemu $HOME/.riv/
echo 'export PATH=$HOME/.riv:$PATH' >> $HOME/.bashrc
export PATH=$HOME/.riv:$PATH

wget -O rivos-sdk.ext2 https://github.com/rives-io/riv/releases/latest/download/rivos-sdk.ext2
rivemu -no-window -sdk=rivos-sdk.ext2 -exec gcc --version

rivemu -quiet -no-window -sdk -workspace -exec gcc main.c -o 0_main -lriv
rivemu -quiet -no-window -sdk -workspace -exec riv-strip 0_main
rivemu -quiet -no-window -sdk -workspace -exec riv-mksqfs 0_main ship.png main.sqfs

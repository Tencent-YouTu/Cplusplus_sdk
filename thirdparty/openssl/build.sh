# ffmpeg
echo "extract "
tar xzvf openssl-1.0.1k.tar.gz 

echo "clean"
BASEDIR=`pwd`

cd openssl-1.0.1k

echo "install to $BASEDIR"
./config --prefix="$BASEDIR"
make -j5
make install
echo "make ok clean"
cd ..
rm -fr openssl-1.0.1k

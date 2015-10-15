# ffmpeg
echo "extract "
tar xvf curl-7.40.0.tar 

echo "clean"
BASEDIR=`pwd`

cd curl-7.40.0 

echo "install to $BASEDIR"
./configure --prefix="$BASEDIR" --disable-shared --enable-static --without-libidn --without-librtmp --without-gnutls --without-nss --without-libssh2 --without-zlib --without-winidn --disable-rtsp --disable-ldap --disable-ldaps --disable-ipv6 --with-ssl=../../openssl 
make -j5
make install
echo "make ok clean"
cd ..
rm -fr curl-7.40.0 

#!/bin/bash
function install( )
{
   
    if [ ! -d "$1/include" ]; then
        cd $1 
#      echo "begin install: $1,Press Y to continue!"
#      read options
#        if [ $options"x" != Y"x" ];then
#          echo "skip install $1"
#       else
           sh build.sh
           echo "install done"
#       fi
          
        cd .. 
        
    else
        echo "already install: $1"
    fi
}
 
   

   

echo "are you sure to install thirdpary [Y/N]"
read options
echo $options
if [ $options"x" != "Yx" ]; then
    echo "you choose No"
    exit
fi

#------------------------------------------------------
list_dir="openssl curl"

for dir in $list_dir
do
   if [ -d $dir ];
   then
     echo "find thirdparty lib:"$dir
     install $dir
   fi
done 



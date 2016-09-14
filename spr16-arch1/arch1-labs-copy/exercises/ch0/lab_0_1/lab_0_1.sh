echo clear terminal screen
clear
sleep 3

echo display working directory
pwd
sleep 3

echo list contents of directory
ls
sleep 3

echo create directory called "lab01" and "labA"
mkdir lab01
sleep 2
mkdir labA
sleep 3

echo list directory again
ls
sleep 3

echo remove labA
rmdir labA
sleep 3

echo list directory again
ls
sleep 3

echo copy lab0_1.sh to lab01 directory
cp lab0_1.sh lab01
sleep 3

echo change to the lab01 directory
cd lab01
sleep 3

echo display directory
pwd
sleep 3

echo list the contents of directory
ls
sleep 3

echo delete lab0_1.sh from lab01
rm lab0_1.sh
sleep 3

echo display directory
pwd
sleep 3

echo list contents of directory
ls
sleep 3

echo delete lab01 directory
cd ..
rmdir lab01
sleep 3

echo list Scripts directory
cd ..
cd scripts
ls
sleep 3
